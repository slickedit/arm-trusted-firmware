/*
 * Copyright (c) 2014, ARM Limited and Contributors. All rights reserved.
 * Copyright (c) 2014, Hisilicon Ltd.
 * Copyright (c) 2014, Linaro Ltd.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

#include <arch.h>
#include "../lcb_def.h"

/*******************************************************************************
 * Platform binary types for linking
 ******************************************************************************/
#define PLATFORM_LINKER_FORMAT          "elf64-littleaarch64"
#define PLATFORM_LINKER_ARCH            aarch64

/*******************************************************************************
 * Generic platform constants
 ******************************************************************************/

/* Size of cacheable stacks */
#define PLATFORM_STACK_SIZE		0x800

#define FIRMWARE_WELCOME_STR		"Booting Trusted Firmware\n"

#define BL1_MEM_NAME			"bl1_mem"

#define BL1_IMAGE_NAME			"bl1.bin"

/* Trusted Boot Firmware BL2 */
#define BL2_IMAGE_NAME			"bl2.bin"

/* EL3 Runtime Firmware BL3-1 */
#define BL31_IMAGE_NAME			"bl31.bin"

/* SCP Firmware BL3-0 */
#define BL30_IMAGE_NAME			"bl30.bin"

/* Secure Payload BL3-2 (Trusted OS) */
#define BL32_IMAGE_NAME			"bl32.bin"

/* Non-Trusted Firmware BL3-3 */
#define BL33_IMAGE_NAME			"bl33.bin" /* e.g. UEFI */

/* Firmware Image Package */
#define FIP_IMAGE_NAME			"fip.bin"

#define PLATFORM_CACHE_LINE_SIZE	64
#define PLATFORM_CLUSTER_COUNT		2
#define PLATFORM_CORE_COUNT             6
#define PLATFORM_NUM_AFFS		(PLATFORM_CLUSTER_COUNT + \
					 PLATFORM_CORE_COUNT)
#define MAX_IO_DEVICES			3
#define MAX_IO_HANDLES			4

/*******************************************************************************
 * Platform memory map related constants
 ******************************************************************************/

/*******************************************************************************
 * BL1 is stored in XG2RAM0_HIRQ that is 784KB large. Could we use 8MB size?
 * The first part is BL1_RAM, and the second part is TZRAM. The name isn't good
 * enough. We need to update it later.
 ******************************************************************************/
#define MMC_BASE			0x00000000
#define MMC_SIZE			0x80000000
#define MMC_BL1_BASE			MMC_BASE
#define MMC_BL1_SIZE			0x00200000
#define MMC_BL2_BASE			(MMC_BASE + MMC_BL1_SIZE)

#define ONCHIPROM_PARAM_BASE		(XG2RAM0_BASE + 0x1000)
#define BL1_XG2RAM0_OFFSET		0x2000

#define DDR_BASE			0x00000000

#define MMC_DESC_BASE			(DDR_BASE + 0x0080000)
#define MMC_DESC_SIZE			0x00020000
#define MMC_DATA_BASE			(MMC_DESC_BASE + MMC_DESC_SIZE)
#define MMC_DATA_SIZE			0x00800000

/*******************************************************************************
 * BL1 specific defines.
 * BL1 RW data is relocated from ROM to RAM at runtime so we need 2 base
 * addresses.
 ******************************************************************************/
#define BL1_RO_BASE			(XG2RAM0_BASE + BL1_XG2RAM0_OFFSET)
#define BL1_RO_LIMIT			(BL1_RO_BASE + 0x16000)
#define BL1_RW_BASE			(BL1_RO_LIMIT)
#define BL1_RW_SIZE			0x00100000
#define BL1_RW_LIMIT			(BL1_RW_BASE + BL1_RW_SIZE)

/*******************************************************************************
 * BL2 specific defines.
 ******************************************************************************/
/* Set it in DDR first. If necessary, we can set them into SRAM again. */
#define BL2_BASE			(BL1_RW_BASE + 0x80000)
#define BL2_LIMIT			(BL2_BASE + BL1_RW_SIZE - 0x40000)

/*******************************************************************************
 * BL3-1 specific defines.
 ******************************************************************************/
#define BL31_BASE			(DDR_BASE + 0x40000)
#define BL31_LIMIT			BL32_BASE
#define BL32_BASE			DRAM_SEC_BASE
#define BL32_LIMIT			(DRAM_SEC_BASE + DRAM_SEC_SIZE)

/*******************************************************************************
 * Load address of BL3-3 in the LCB port
 ******************************************************************************/
#define NS_IMAGE_OFFSET			(DRAM_BASE + 0x00400000)  /* 4MB */

/*******************************************************************************
 * Platform specific page table and MMU setup constants
 ******************************************************************************/
#define ADDR_SPACE_SIZE			(1ull << 32)

#if IMAGE_BL31
# define MAX_XLAT_TABLES		2
#endif

#if IMAGE_BL1 || IMAGE_BL2 || IMAGE_BL32
# define MAX_XLAT_TABLES		3
#endif

#define MAX_MMAP_REGIONS		16

/*******************************************************************************
 * Declarations and constants to access the mailboxes safely. Each mailbox is
 * aligned on the biggest cache line size in the platform. This is known only
 * to the platform as it might have a combination of integrated and external
 * caches. Such alignment ensures that two maiboxes do not sit on the same cache
 * line at any cache level. They could belong to different cpus/clusters &
 * get written while being protected by different locks causing corruption of
 * a valid mailbox address.
 ******************************************************************************/
#define CACHE_WRITEBACK_SHIFT   6
#define CACHE_WRITEBACK_GRANULE (1 << CACHE_WRITEBACK_SHIFT)

#endif /* __PLATFORM_DEF_H__ */
