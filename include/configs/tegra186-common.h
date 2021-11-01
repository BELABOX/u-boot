/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright 2013-2021, NVIDIA CORPORATION.
 */

#ifndef _TEGRA186_COMMON_H_
#define _TEGRA186_COMMON_H_

#include "tegra-common.h"

/*
 * NS16550 Configuration
 */
#define V_NS16550_CLK		408000000	/* 408MHz (pllp_out0) */

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */

/* Generic Interrupt Controller */
#define CONFIG_GICV2

/*
 * Memory layout for where various images get loaded by boot scripts:
 *
 * scriptaddr can be pretty much anywhere that doesn't conflict with something
 *   else. Put it above BOOTMAPSZ to eliminate conflicts.
 *
 * pxefile_addr_r can be pretty much anywhere that doesn't conflict with
 *   something else. Put it above BOOTMAPSZ to eliminate conflicts.
 *
 * kernel_addr_r must be within the first 128M of RAM in order for the
 *   kernel's CONFIG_AUTO_ZRELADDR option to work. Since the kernel will
 *   decompress itself to 0x8000 after the start of RAM, kernel_addr_r
 *   should not overlap that area, or the kernel will have to copy itself
 *   somewhere else before decompression. Similarly, the address of any other
 *   data passed to the kernel shouldn't overlap the start of RAM. Pushing
 *   this up to 16M allows for a sizable kernel to be decompressed below the
 *   compressed load address.
 *
 * fdt_addr_r simply shouldn't overlap anything else. Choosing 32M allows for
 *   the compressed kernel to be up to 16M too.
 *
 * fdtoverlay_addr_r is used for DTB overlays from extlinux.conf. It's placed
 *   just above pxefile_addr_r.
 *
 * ramdisk_addr_r simply shouldn't overlap anything else. Choosing 33M allows
 *   for the FDT/DTB to be up to 1M, which is hopefully plenty.
 */
#define CONFIG_LOADADDR 0x80080000
#define MEM_LAYOUT_ENV_SETTINGS \
	"scriptaddr=0x90000000\0" \
	"pxefile_addr_r=0x90100000\0" \
	"fdtoverlay_addr_r=0x90200000\0" \
	"kernel_addr_r=" __stringify(CONFIG_LOADADDR) "\0" \
	"fdt_addr_r=0x82000000\0" \
	"ramdisk_addr_r=0x82100000\0" \
	"fdt_copy_node_paths=" \
		"/chosen/plugin-manager:" \
		"/chosen/reset:" \
		"/memory@80000000\0" \
	"fdt_copy_prop_paths=" \
		"/bpmp/carveout-start:" \
		"/bpmp/carveout-size:" \
		"/chosen/nvidia,bluetooth-mac:" \
		"/chosen/nvidia,ether-mac:" \
		"/chosen/nvidia,wifi-mac:" \
		"/chosen/ecid:" \
		"/chosen/linux,initrd-start:" \
		"/chosen/linux,initrd-end:" \
		"/reserved-memory/fb0_carveout/reg:" \
		"/reserved-memory/fb1_carveout/reg:" \
		"/reserved-memory/fb2_carveout/reg:" \
		"/reserved-memory/ramoops_carveout/alignment:" \
		"/reserved-memory/ramoops_carveout/alloc-ranges:" \
		"/reserved-memory/ramoops_carveout/size:" \
		"/reserved-memory/vpr-carveout/alignment:" \
		"/reserved-memory/vpr-carveout/alloc-ranges:" \
		"/reserved-memory/vpr-carveout/size:" \
		"/serial-number:" \
		"/trusty/status\0"

#define ROOTFS_AB_SELECT \
	"check_rootfs_ab="                                              \
	"for args in ${cbootargs}; do "                                 \
		"rootfs_b=rootfs.slot_suffix=_b; "                      \
		"if test ${args} = ${rootfs_b}; then "                  \
			"setenv devplist 2; "                           \
		"fi; "                                                  \
	"done\0"                                                        \
	"scan_dev_for_boot_part="                                       \
		"part list ${devtype} ${devnum} -bootable devplist; "   \
		"env exists devplist || setenv devplist 1; "            \
		"run check_rootfs_ab; "                                 \
		"for distro_bootpart in ${devplist}; do "               \
			"if fstype ${devtype} "                         \
					"${devnum}:${distro_bootpart} " \
					"bootfstype; then "             \
					"run scan_dev_for_boot; "       \
			"fi; "                                          \
		"done; "                                                \
		"setenv devplist\0"
#endif
