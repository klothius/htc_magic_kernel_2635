/*
* Simple IO scheduler
* Based on Noop, Deadline and V(R) IO schedulers.
*
* Copyright (C) 2010 Miguel Boton <mboton@gmail.com>
*
*
* This algorithm does not do any kind of sorting, as it is aimed for
* aleatory access devices, but it does some basic merging. We try to
* keep minimum overhead to achieve low latency.
*
* Asynchronous and synchronous requests are not treated separately, but
* we relay on deadlines to ensure fairness.
*
*/
#include <linux/blkdev.h>
#include <linux/elevator.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

enum {
ASYNC,
SYNC,
};

/* Tunables */
static const int sync_expire = HZ / 2; /* max time before a sync is submitted. */
static const int async_expire = 5 * HZ; /* ditto for async, these limits are SOFT! */
static const int fifo_batch = 2; /* # of sequential requests treated as one
by the above parameters. For throughput. */

/* Elevator data */
struct sio_data {
/* Request queues */
struct list_head fifo_list[2];

/* Attributes */
unsigned int batched;

/* Settings */
int fifo_expire[2];
int fifo_batch;
};

static void
sio_merged_requests(struct request_queue *q, struct request *rq,
struct request *next)
{
/*
* If next expires before rq, assign its expire time to rq
* and move into next position (next will be deleted) in fifo.
*/
if (!list_empty(&rq->queuelist) && !list_empty(&next->queuelist)) {
if (time_before(rq_fifo_time(next), rq_fifo_time(rq))) {
list_move(&rq->queuelist, &next->queuelist);
rq_set_fifo_time(rq, rq_fifo_time(next));
}
}

/* Delete next request */
rq_fifo_clear(next);
}

static void
sio_add_request(struct request_queue *q, struct request *rq)
{
struct sio_data *sd = q->elevator->elevator_data;
const int sync = rq_is_sync(rq);

/*
* Add request to the proper fifo list and set its
* expire time.
*/
rq_set_fifo_time(rq, jiffies + sd->fifo_expire[sync]);
list_add_tail(&rq->queuelist, &sd->fifo_list[sync]);
}

static int
sio_queue_empty(struct request_queue *q)
{
struct sio_data *sd = q->elevator->elevator_data;

/* Check if fifo lists are empty */
return list_empty(&sd->fifo_list[SYNC]) &&
list_empty(&sd->fifo_list[ASYNC]);
}

static struct request *
sio_expired_request(struct sio_data *sd, int sync)
{
struct request *rq;

if (list_empty(&sd->fifo_list[sync]))
return NULL;

/* Retrieve request */
rq = rq_entry_fifo(sd->fifo_list[sync].next);

/* Request has expired */
if (time_after(jiffies, rq_fifo_time(rq)))
return rq;

return NULL;
}

static struct request *
sio_choose_expired_request(struct sio_data *sd)
{
struct request *sync = sio_expired_request(sd, SYNC);
struct request *async = sio_expired_request(sd, ASYNC);

/*
* Check expired requests. Asynchronous requests have
* priority over synchronous.
*/
if (sync && async)
return async;
if (sync)
return sync;

return async;

}

static struct request *
sio_choose_request(struct sio_data *sd)
{
/*
* Retrieve request from available fifo list.
* Synchronous requests have priority over asynchronous.
*/
if (!list_empty(&sd->fifo_list[SYNC]))
return rq_entry_fifo(sd->fifo_list[SYNC].next);

if (!list_empty(&sd->fifo_list[ASYNC]))
return rq_entry_fifo(sd->fifo_list[ASYNC].next);

return NULL;
}

static inline void
sio_dispatch_request(struct sio_data *sd, struct request *rq)
{
/*
* Remove the request from the fifo list
* and dispatch it.
*/
rq_fifo_clear(rq);
elv_dispatch_add_tail(rq->q, rq);

sd->batched++;
}

static int
sio_dispatch_requests(struct request_queue *q, int force)
{
struct sio_data *sd = q->elevator->elevator_data;
struct request *rq = NULL;

/*
* Retrieve any expired request after a batch of
* sequential requests.
*/
if (sd->batched > sd->fifo_batch) {
sd->batched = 0;
rq = sio_choose_expired_request(sd);
}

/* Retrieve request */
if (!rq) {
rq = sio_choose_request(sd);
if (!rq)
return 0;
}

/* Dispatch request */
sio_dispatch_request(sd, rq);

return 1;
}

static struct request *
sio_former_request(struct request_queue *q, struct request *rq)
{
struct sio_data *sd = q->elevator->elevator_data;
const int sync = rq_is_sync(rq);

if (rq->queuelist.prev == &sd->fifo_list[sync])
return NULL;

/* Return former request */
return list_entry(rq->queuelist.prev, struct request, queuelist);
}

static struct request *
sio_latter_request(struct request_queue *q, struct request *rq)
{
struct sio_data *sd = q->elevator->elevator_data;
const int sync = rq_is_sync(rq);

if (rq->queuelist.next == &sd->fifo_list[sync])
return NULL;

/* Return latter request */
return list_entry(rq->queuelist.next, struct request, queuelist);
}

static void *
sio_init_queue(struct request_queue *q)
{
struct sio_data *sd;

/* Allocate structure */
sd = kmalloc_node(sizeof(*sd), GFP_KERNEL, q->node);
if (!sd)
return NULL;

/* Initialize fifo lists */
INIT_LIST_HEAD(&sd->fifo_list[SYNC]);
INIT_LIST_HEAD(&sd->fifo_list[ASYNC]);

/* Initialize data */
sd->batched = 0;
sd->fifo_expire[SYNC] = sync_expire;
sd->fifo_expire[ASYNC] = async_expire;
sd->fifo_batch = fifo_batch;

return sd;
}

static void
sio_exit_queue(struct elevator_queue *e)
{
struct sio_data *sd = e->elevator_data;

BUG_ON(!list_empty(&sd->fifo_list[SYNC]));
BUG_ON(!list_empty(&sd->fifo_list[ASYNC]));

/* Free structure */
kfree(sd);
}

/*
* sysfs code
*/

static ssize_t
sio_var_show(int var, char *page)
{
return sprintf(page, "%d\n", var);
}

static ssize_t
sio_var_store(int *var, const char *page, size_t count)
{
char *p = (char *) page;

*var = simple_strtol(p, &p, 10);
return count;
}

#define SHOW_FUNCTION(__FUNC, __VAR, __CONV) \
static ssize_t __FUNC(struct elevator_queue *e, char *page) \
{ \
struct sio_data *sd = e->elevator_data; \
int __data = __VAR; \
if (__CONV) \
__data = jiffies_to_msecs(__data); \
return sio_var_show(__data, (page)); \
}
SHOW_FUNCTION(sio_sync_expire_show, sd->fifo_expire[SYNC], 1);
SHOW_FUNCTION(sio_async_expire_show, sd->fifo_expire[ASYNC], 1);
SHOW_FUNCTION(sio_fifo_batch_show, sd->fifo_batch, 0);
#undef SHOW_FUNCTION

#define STORE_FUNCTION(__FUNC, __PTR, MIN, MAX, __CONV) \
static ssize_t __FUNC(struct elevator_queue *e, const char *page, size_t count) \
{ \
struct sio_data *sd = e->elevator_data; \
int __data; \
int ret = sio_var_store(&__data, (page), count); \
if (__data < (MIN)) \
__data = (MIN); \
else if (__data > (MAX)) \
__data = (MAX); \
if (__CONV) \
*(__PTR) = msecs_to_jiffies(__data); \
else \
*(__PTR) = __data; \
return ret; \
}
STORE_FUNCTION(sio_sync_expire_store, &sd->fifo_expire[SYNC], 0, INT_MAX, 1);
STORE_FUNCTION(sio_async_expire_store, &sd->fifo_expire[ASYNC], 0, INT_MAX, 1);
STORE_FUNCTION(sio_fifo_batch_store, &sd->fifo_batch, 0, INT_MAX, 0);
#undef STORE_FUNCTION

#define DD_ATTR(name) \
__ATTR(name, S_IRUGO|S_IWUSR, sio_##name##_show, \
sio_##name##_store)

static struct elv_fs_entry sio_attrs[] = {
DD_ATTR(sync_expire),
DD_ATTR(async_expire),
DD_ATTR(fifo_batch),
__ATTR_NULL
};

static struct elevator_type iosched_sio = {
.ops = {
.elevator_merge_req_fn = sio_merged_requests,
.elevator_dispatch_fn = sio_dispatch_requests,
.elevator_add_req_fn = sio_add_request,
.elevator_queue_empty_fn = sio_queue_empty,
.elevator_former_req_fn = sio_former_request,
.elevator_latter_req_fn = sio_latter_request,
.elevator_init_fn = sio_init_queue,
.elevator_exit_fn = sio_exit_queue,
},

.elevator_attrs = sio_attrs,
.elevator_name = "sio",
.elevator_owner = THIS_MODULE,
};

static int __init sio_init(void)
{
/* Register elevator */
elv_register(&iosched_sio);

return 0;
}

static void __exit sio_exit(void)
{
/* Unregister elevator */
elv_unregister(&iosched_sio);
}

module_init(sio_init);
module_exit(sio_exit);

MODULE_AUTHOR("Miguel Boton");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple IO scheduler");
