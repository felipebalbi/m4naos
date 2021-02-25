/* SPDX-License-Identifier: GPL-3.0-or-later */

/*
 * This file is part of M4naos
 *
 * M4naos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * M4naos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with M4naos.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <m4naos/hardware.h>
#include <m4naos/kernel.h>
#include <m4naos/io.h>

#define PWR_CR	0x00
#define PWR_CSR	0x04

#define PWR_CR_LPSDSR		(1 << 0)
#define PWR_CR_PDDS		(1 << 1)
#define PWR_CR_CWDUF		(1 << 2)
#define PWR_CR_CSBF		(1 << 3)
#define PWR_CR_PVDE		(1 << 4)
#define PWR_CR_PLS(n)		(((n) & 7) << 5)
#define PWR_CR_PSL_MASK		PWR_CR_PLS(7)
#define PWR_CR_DBP		(1 << 8)
#define PWR_CR_ULP		(1 << 9)
#define PWR_CR_FWV		(1 << 10)
#define PWR_CR_VOS(n)		(((n) & 3) << 11)
#define PWR_CR_VOS_1V8		PWR_CR_VOS(1)
#define PWR_CR_VOS_1V5		PWR_CR_VOS(2)
#define PWR_CR_VOS_1V2		PWR_CR_VOS(3)
#define PWR_CR_VOS_MASK		PWR_CR_VOS_1V2
#define PWR_CR_DS_EE_KOFF	(1 << 14)

#define PWR_CSR_WUF		(1 << 0)
#define PWR_CSR_SBF		(1 << 1)
#define PWR_CSR_PVDO		(1 << 2)
#define PWR_CSR_VREFINTRDYF	(1 << 3)
#define PWR_CSR_VOSF		(1 << 4)
#define PWR_CSR_REGLPF		(1 << 5)
#define PWR_CSR_EWUP1		(1 << 8)
#define PWR_CSR_EWUP2		(1 << 9)
#define PWR_CSR_EWUP3		(1 << 10)

static inline void pwr_writel(u32 offset, u32 value)
{
	writel(APB1_PWR, offset, value);
}

static inline u32 pwr_readl(u32 offset)
{
	return readl(APB1_PWR, offset);
}

void system_volt_scale_init(void)
{
	u32 reg;

	/* Select 1.8V */
	reg = pwr_readl(PWR_CR);
	reg &= ~PWR_CR_VOS_MASK;
	reg |= PWR_CR_VOS_1V8;
	pwr_writel(PWR_CR, reg);
}

static int pwr_init(void)
{
	return 0;
}
core_init(pwr_init);
