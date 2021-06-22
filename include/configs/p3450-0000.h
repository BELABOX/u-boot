/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2018-2021 NVIDIA Corporation.
 */

#ifndef _P3450_0000_H
#define _P3450_0000_H

#include <linux/sizes.h>

#include "tegra210-common.h"

/* High-level configuration options */
#define CONFIG_TEGRA_BOARD_STRING	"NVIDIA P3450-0000"

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTA

/* Both SD and EMMC since this supports both SKU0 and SKU2 Nano */
#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 1) \
	func(MMC, mmc, 0) \
	func(USB, usb, 0) \
	func(NVME, nvme, 0) \
	func(PXE, pxe, na) \
	func(DHCP, dhcp, na)

/* Environment at end of QSPI on the Nano devkit, in the VER partition */
#define CONFIG_ENV_SPI_MAX_HZ		48000000
#define CONFIG_ENV_SPI_MODE		SPI_MODE_0
#define CONFIG_SPI_FLASH_SIZE		(4 << 20)

#define CONFIG_PREBOOT

#define BOARD_EXTRA_ENV_SETTINGS \
	"preboot=if test -e mmc 1:1 /u-boot-preboot.scr; then " \
		"load mmc 1:1 ${scriptaddr} /u-boot-preboot.scr; " \
		"source ${scriptaddr}; " \
	"fi\0"

/* General networking support */
#include "tegra-common-usb-gadget.h"
#include "tegra-common-post.h"

/* Crystal is 38.4MHz. clk_m runs at half that rate */
#define COUNTER_FREQUENCY	19200000

/*
 * Environment in eMMC only on the Nano commercial SKU,
 * at the end of 2nd "boot sector"
 */
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_SYS_MMC_ENV_PART		2
#endif /* _P3450_0000_H */
