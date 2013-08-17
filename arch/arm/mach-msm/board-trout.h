/* linux/arch/arm/mach-msm/board-trout.h
** Author: Brian Swetland <swetland@google.com>
*/
#ifndef __ARCH_ARM_MACH_MSM_BOARD_TROUT_H
#define __ARCH_ARM_MACH_MSM_BOARD_TROUT_H

#include <mach/board.h>

#define MSM_SMI_BASE		0x00000000
#define MSM_SMI_SIZE		0x00800000

//#define MSM_EBI_BASE		0x10000000
//#define MSM_EBI_SIZE		0x06e00000

#define MSM_PMEM_GPU0_BASE	0x00000000
#define MSM_PMEM_GPU0_SIZE	0x00700000

#if defined(CONFIG_MSM_AMSS_SUPPORT_256MB_EBI1)
/* AMSS supports unified 128/256MB EBI1 */
#define MSM_EBI_BASE                            0x19200000
#define MSM_EBI_SMI64_128MB_SIZE        0x06600000
#define MSM_EBI_SMI32_256MB_SIZE        0x0C600000

#define SMI64_MSM_FB_BASE                       0x00700000
#define SMI64_MSM_FB_SIZE                       0x0009B000

#define SMI64_MSM_RAM_CONSOLE_BASE      0x007A0000
#define SMI64_MSM_RAM_CONSOLE_SIZE      128 * SZ_1K

#define SMI64_MSM_PMEM_MDP_BASE         0x02000000
#define SMI64_MSM_PMEM_MDP_SIZE         0x00800000

#define SMI64_MSM_PMEM_ADSP_BASE    0x02800000
#define SMI64_MSM_PMEM_ADSP_SIZE        0x00800000

#define SMI64_MSM_PMEM_CAMERA_BASE      0x03000000
#define SMI64_MSM_PMEM_CAMERA_SIZE      0x01000000

#define SMI64_MSM_PMEM_GPU1_BASE        0x1F800000
#define SMI64_MSM_PMEM_GPU1_SIZE        0x800000

#define SMI32_MSM_FB_BASE                       0x00700000
#define SMI32_MSM_FB_SIZE                       0x0009B000

#define SMI32_MSM_RAM_CONSOLE_BASE      0x007A0000
#define SMI32_MSM_RAM_CONSOLE_SIZE      128 * SZ_1K

#define SMI32_MSM_PMEM_GPU1_BASE        0x25800000
#define SMI32_MSM_PMEM_GPU1_SIZE        0x00800000

#define SMI32_MSM_PMEM_MDP_BASE         0x26000000
#define SMI32_MSM_PMEM_MDP_SIZE         0x00800000

#define SMI32_MSM_PMEM_ADSP_BASE        0x26800000
#define SMI32_MSM_PMEM_ADSP_SIZE        0x00800000

#define SMI32_MSM_PMEM_CAMERA_BASE      0x27000000
#define SMI32_MSM_PMEM_CAMERA_SIZE      0x01000000

#else

#if defined(CONFIG_MSM_AMSS_RADIO2708_MEMMAP) 
 
/* New radio 2708 Memory Map */ 
 
#define MSM_EBI_BASE            0x10000000 
#define MSM_EBI_SIZE            0x07100000 
 
#define SMI64_MSM_PMEM_MDP_BASE 0x15900000 
#define SMI64_MSM_PMEM_MDP_SIZE 0x00800000 
 
#define SMI64_MSM_PMEM_ADSP_BASE 0x16100000 
#define SMI64_MSM_PMEM_ADSP_SIZE 0x00800000 
 
#define SMI64_MSM_PMEM_CAMERA_BASE      0x15400000 
#define SMI64_MSM_PMEM_CAMERA_SIZE      0x00500000 
 
#define SMI64_MSM_FB_BASE               0x00700000 
#define SMI64_MSM_FB_SIZE               0x00100000 
 
#define SMI64_MSM_RAM_CONSOLE_BASE  0x169E0000 
#define SMI64_MSM_RAM_CONSOLE_SIZE  128 * SZ_1K 
 
#define SMI64_MSM_PMEM_GPU1_SIZE        0x00800000 
#define SMI64_MSM_PMEM_GPU1_BASE     (0x169E0000 + (128 * SZ_1K)) 
 
#define SMI64_MSM_LINUX_BASE        0x02000000 
#define SMI64_MSM_LINUX_SIZE        0x02000000 
 
#define SMI64_MSM_LINUX2_BASE       MSM_EBI_BASE 
#define SMI64_MSM_LINUX2_SIZE       0x05400000 
 
#else /* Not CONFIG_MSM_AMSS_RADIO2708_MEMMAP */ 

/* AMSS supports only 128MB EBI1. */
#define MSM_EBI_BASE            0x10000000
#define MSM_EBI_SIZE            0x06E00000

#define SMI64_MSM_FB_BASE               0x03800000
#define SMI64_MSM_FB_SIZE               0x00100000

#define SMI64_MSM_PMEM_MDP_BASE         0x02000000
#define SMI64_MSM_PMEM_MDP_SIZE         0x00800000

#define SMI64_MSM_PMEM_ADSP_BASE        0x02800000
#define SMI64_MSM_PMEM_ADSP_SIZE        0x00800000

#define SMI64_MSM_PMEM_CAMERA_BASE      0x03000000
#define SMI64_MSM_PMEM_CAMERA_SIZE      0x00800000

#define SMI64_MSM_PMEM_GPU1_SIZE        0x00800000
#define SMI64_MSM_PMEM_GPU1_BASE  	0x16500000

#define SMI64_MSM_LINUX_BASE            MSM_EBI_BASE
#define SMI64_MSM_LINUX_SIZE            0x06500000

#define SMI64_MSM_LINUX2_BASE       	0x16D00000
#define SMI64_MSM_LINUX2_SIZE       	0x00100000

#define SMI64_MSM_RAM_CONSOLE_BASE  	0x007A0000
#define SMI64_MSM_RAM_CONSOLE_SIZE      128 * SZ_1K

#endif /*End if defined CONFIG_MSM_AMSS_RADIO2708_MEMMAP */ 
 
#define SMI32_MSM_LINUX_BASE    MSM_EBI_BASE 
#define SMI32_MSM_LINUX_SIZE    0x5400000 

#define SMI32_MSM_PMEM_MDP_BASE         (SMI32_MSM_LINUX_BASE + SMI32_MSM_LINUX_SIZE)
#define SMI32_MSM_PMEM_MDP_SIZE         0x800000

#define SMI32_MSM_PMEM_ADSP_BASE        (SMI32_MSM_PMEM_MDP_BASE + SMI32_MSM_PMEM_MDP_SIZE)
#define SMI32_MSM_PMEM_ADSP_SIZE        0x800000

#define SMI32_MSM_FB_BASE                       (SMI32_MSM_PMEM_ADSP_BASE + SMI32_MSM_PMEM_ADSP_SIZE)
#define SMI32_MSM_FB_SIZE                       0x9b000

#define SMI32_MSM_RAM_CONSOLE_BASE      (MSM_EBI_BASE + 0x6d00000)
#define SMI32_MSM_RAM_CONSOLE_SIZE      128 * SZ_1K

#define SMI32_MSM_PMEM_GPU1_SIZE        0x800000
#define SMI32_MSM_PMEM_GPU1_BASE        (SMI32_MSM_RAM_CONSOLE_BASE - SMI32_MSM_PMEM_GPU1_SIZE)

#define SMI32_MSM_PMEM_CAMERA_BASE      0
#define SMI32_MSM_PMEM_CAMERA_SIZE      0

#endif

/*

#define MSM_PMEM_MDP_BASE	0x02000000
#define MSM_PMEM_MDP_SIZE	0x00800000

#define MSM_PMEM_ADSP_BASE      0x02800000
#define MSM_PMEM_ADSP_SIZE	0x00800000

#define MSM_PMEM_CAMERA_BASE	0x03000000
#define MSM_PMEM_CAMERA_SIZE	0x00800000

#define MSM_FB_BASE		0x03800000
#define MSM_FB_SIZE		0x00100000

#define MSM_LINUX_BASE		MSM_EBI_BASE
#define MSM_LINUX_SIZE		0x06500000

#define MSM_PMEM_GPU1_SIZE	0x800000
#define MSM_PMEM_GPU1_BASE	MSM_RAM_CONSOLE_BASE - MSM_PMEM_GPU1_SIZE

#define MSM_RAM_CONSOLE_BASE	MSM_EBI_BASE + 0x6d00000
#define MSM_RAM_CONSOLE_SIZE	128 * SZ_1K

#if (MSM_FB_BASE + MSM_FB_SIZE) >= (MSM_PMEM_GPU1_BASE)
#error invalid memory map
#endif

*/
#define DECLARE_MSM_IOMAP
#include <mach/msm_iomap.h>

#define TROUT_4_BALL_UP_0     1
#define TROUT_4_BALL_LEFT_0   18
#define TROUT_4_BALL_DOWN_0   57
#define TROUT_4_BALL_RIGHT_0  91

#define TROUT_5_BALL_UP_0     94
#define TROUT_5_BALL_LEFT_0   18
#define TROUT_5_BALL_DOWN_0   90
#define TROUT_5_BALL_RIGHT_0  19

#define TROUT_POWER_KEY     20

#define TROUT_4_TP_LS_EN    19
#define TROUT_5_TP_LS_EN    1

#define TROUT_CPLD_BASE   0xFA000000
#define TROUT_CPLD_START  0x98000000
#define TROUT_CPLD_SIZE   SZ_4K

#define TROUT_GPIO_CABLE_IN1		(83)
#define TROUT_GPIO_CABLE_IN2		(49)

#define TROUT_GPIO_START (128)

#define TROUT_GPIO_INT_MASK0_REG            (0x0c)
#define TROUT_GPIO_INT_STAT0_REG            (0x0e)
#define TROUT_GPIO_INT_MASK1_REG            (0x14)
#define TROUT_GPIO_INT_STAT1_REG            (0x10)

#define TROUT_GPIO_HAPTIC_PWM               (28)
#define TROUT_GPIO_PS_HOLD                  (25)

#define TROUT_GPIO_MISC2_BASE               (TROUT_GPIO_START + 0x00)
#define TROUT_GPIO_MISC3_BASE               (TROUT_GPIO_START + 0x08)
#define TROUT_GPIO_MISC4_BASE               (TROUT_GPIO_START + 0x10)
#define TROUT_GPIO_MISC5_BASE               (TROUT_GPIO_START + 0x18)
#define TROUT_GPIO_INT2_BASE                (TROUT_GPIO_START + 0x20)
#define TROUT_GPIO_MISC1_BASE               (TROUT_GPIO_START + 0x28)
#define TROUT_GPIO_VIRTUAL_BASE             (TROUT_GPIO_START + 0x30)
#define TROUT_GPIO_INT5_BASE                (TROUT_GPIO_START + 0x48)

#define TROUT_GPIO_CHARGER_EN               (TROUT_GPIO_MISC2_BASE + 0)
#define TROUT_GPIO_ISET                     (TROUT_GPIO_MISC2_BASE + 1)
#define TROUT_GPIO_H2W_DAT_DIR              (TROUT_GPIO_MISC2_BASE + 2)
#define TROUT_GPIO_H2W_CLK_DIR              (TROUT_GPIO_MISC2_BASE + 3)
#define TROUT_GPIO_H2W_DAT_GPO              (TROUT_GPIO_MISC2_BASE + 4)
#define TROUT_GPIO_H2W_CLK_GPO              (TROUT_GPIO_MISC2_BASE + 5)
#define TROUT_GPIO_H2W_SEL0                 (TROUT_GPIO_MISC2_BASE + 6)
#define TROUT_GPIO_H2W_SEL1                 (TROUT_GPIO_MISC2_BASE + 7)

#define TROUT_GPIO_SPOTLIGHT_EN             (TROUT_GPIO_MISC3_BASE + 0)
#define TROUT_GPIO_FLASH_EN                 (TROUT_GPIO_MISC3_BASE + 1)
#define TROUT_GPIO_I2C_PULL                 (TROUT_GPIO_MISC3_BASE + 2)
#define TROUT_GPIO_TP_I2C_PULL              (TROUT_GPIO_MISC3_BASE + 3)
#define TROUT_GPIO_TP_EN                    (TROUT_GPIO_MISC3_BASE + 4)
#define TROUT_GPIO_JOG_EN                   (TROUT_GPIO_MISC3_BASE + 5)
#define TROUT_GPIO_UI_LED_EN                (TROUT_GPIO_MISC3_BASE + 6)
#define TROUT_GPIO_QTKEY_LED_EN             (TROUT_GPIO_MISC3_BASE + 7)

#define TROUT_GPIO_VCM_PWDN                 (TROUT_GPIO_MISC4_BASE + 0)
#define TROUT_GPIO_USB_H2W_SW               (TROUT_GPIO_MISC4_BASE + 1)
#define TROUT_GPIO_COMPASS_RST_N            (TROUT_GPIO_MISC4_BASE + 2)
#define TROUT_GPIO_HAPTIC_EN_UP             (TROUT_GPIO_MISC4_BASE + 3)
#define TROUT_GPIO_HAPTIC_EN_MAIN           (TROUT_GPIO_MISC4_BASE + 4)
#define TROUT_GPIO_USB_PHY_RST_N            (TROUT_GPIO_MISC4_BASE + 5)
#define TROUT_GPIO_WIFI_PA_RESETX           (TROUT_GPIO_MISC4_BASE + 6)
#define TROUT_GPIO_WIFI_EN                  (TROUT_GPIO_MISC4_BASE + 7)

#define TROUT_GPIO_BT_32K_EN                (TROUT_GPIO_MISC5_BASE + 0)
#define TROUT_GPIO_MAC_32K_EN               (TROUT_GPIO_MISC5_BASE + 1)
#define TROUT_GPIO_MDDI_32K_EN              (TROUT_GPIO_MISC5_BASE + 2)
#define TROUT_GPIO_COMPASS_32K_EN           (TROUT_GPIO_MISC5_BASE + 3)

#define TROUT_GPIO_NAVI_ACT_N               (TROUT_GPIO_INT2_BASE + 0)
#define TROUT_GPIO_COMPASS_IRQ              (TROUT_GPIO_INT2_BASE + 1)
#define TROUT_GPIO_SLIDING_DET              (TROUT_GPIO_INT2_BASE + 2)
#define TROUT_GPIO_AUD_HSMIC_DET_N          (TROUT_GPIO_INT2_BASE + 3)
#define TROUT_GPIO_SD_DOOR_N                (TROUT_GPIO_INT2_BASE + 4)
#define TROUT_GPIO_CAM_BTN_STEP1_N          (TROUT_GPIO_INT2_BASE + 5)
#define TROUT_GPIO_CAM_BTN_STEP2_N          (TROUT_GPIO_INT2_BASE + 6)
#define TROUT_GPIO_TP_ATT_N                 (TROUT_GPIO_INT2_BASE + 7)
#define TROUT_GPIO_BANK0_FIRST_INT_SOURCE   (TROUT_GPIO_NAVI_ACT_N)
#define TROUT_GPIO_BANK0_LAST_INT_SOURCE    (TROUT_GPIO_TP_ATT_N)

#define TROUT_GPIO_H2W_DAT_GPI              (TROUT_GPIO_MISC1_BASE + 0)
#define TROUT_GPIO_H2W_CLK_GPI              (TROUT_GPIO_MISC1_BASE + 1)
#define TROUT_GPIO_CPLD128_VER_0            (TROUT_GPIO_MISC1_BASE + 4)
#define TROUT_GPIO_CPLD128_VER_1            (TROUT_GPIO_MISC1_BASE + 5)
#define TROUT_GPIO_CPLD128_VER_2            (TROUT_GPIO_MISC1_BASE + 6)
#define TROUT_GPIO_CPLD128_VER_3            (TROUT_GPIO_MISC1_BASE + 7)

#define TROUT_GPIO_SDMC_CD_N                (TROUT_GPIO_VIRTUAL_BASE + 0)
#define TROUT_GPIO_END                      (TROUT_GPIO_SDMC_CD_N)
#define TROUT_GPIO_BANK1_FIRST_INT_SOURCE   (TROUT_GPIO_SDMC_CD_N)
#define TROUT_GPIO_BANK1_LAST_INT_SOURCE    (TROUT_GPIO_SDMC_CD_N)

#define TROUT_GPIO_VIRTUAL_TO_REAL_OFFSET \
	(TROUT_GPIO_INT5_BASE - TROUT_GPIO_VIRTUAL_BASE)

#define TROUT_INT_START (NR_MSM_IRQS + NR_GPIO_IRQS)
#define TROUT_INT_BANK0_COUNT (8)
#define TROUT_INT_BANK1_START (TROUT_INT_START + TROUT_INT_BANK0_COUNT)
#define TROUT_INT_BANK1_COUNT (1)
#define TROUT_INT_END (TROUT_INT_START + TROUT_INT_BANK0_COUNT + \
			TROUT_INT_BANK1_COUNT - 1)
#define TROUT_GPIO_TO_INT(n) (((n) <= TROUT_GPIO_BANK0_LAST_INT_SOURCE) ? \
	(TROUT_INT_START - TROUT_GPIO_BANK0_FIRST_INT_SOURCE + (n)) : \
	(TROUT_INT_BANK1_START - TROUT_GPIO_BANK1_FIRST_INT_SOURCE + (n)))

#define TROUT_INT_TO_BANK(n) ((n - TROUT_INT_START) / TROUT_INT_BANK0_COUNT)
#define TROUT_INT_TO_MASK(n) (1U << ((n - TROUT_INT_START) & 7))
#define TROUT_BANK_TO_MASK_REG(bank) \
	(bank ? TROUT_GPIO_INT_MASK1_REG : TROUT_GPIO_INT_MASK0_REG)
#define TROUT_BANK_TO_STAT_REG(bank) \
	(bank ? TROUT_GPIO_INT_STAT1_REG : TROUT_GPIO_INT_STAT0_REG)

int trout_get_smi_size(void);

#endif /* GUARD */
