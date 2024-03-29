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

#include <errno.h>
#include <stdio.h>
#include <m4naos/hardware.h>
#include <m4naos/io.h>
#include <m4naos/kernel.h>
#include <m4naos/sched.h>
#include <m4naos/sys-tick.h>

#define SYST_CSR		0x00
#define SYST_RVR		0x04
#define SYST_CVR		0x08
#define SYST_CALIB		0x0c

#define SYST_CSR_ENABLE		(1 << 0)
#define SYST_CSR_TICKINT	(1 << 1)
#define SYST_CSR_CLKSOURCE	(1 << 2)
#define SYST_CSR_COUNTFLAG	(1 << 16)

#define SYST_RVR_RELOAD(n)	((n) & 0x00ffffff)

#define SYST_CVR_CURRENT(n)	((n) & 0x00ffffff)

#define SYST_CALIB_TENMS(n)	((n) & 0x00ffffff)
#define SYST_CALIB_SKEW		(1 << 30)
#define SYST_CALIB_NOREF	(1 << 31)

#define NSECS_IN_MSEC		(NSECS_IN_SEC / 1000)

u32 jiffies = 0;

void sys_tick_handler(void)
{
	jiffies++;
	__schedule();
}

static int timer_init(void)
{
	void __iomem *base;
	void __iomem *scb;
	u32 reload;
	u32 csr;
	int ret;

	base = ioremap(SYST_BASE);
	if (!base) {
		ret = -ENOMEM;
		goto err0;
	}

	scb = ioremap(SCB_BASE);
	if (!scb) {
		ret = -ENOMEM;
		goto err0;
	}

	/*
	 * We want a tick every 1ms, so let's calculate how many
	 * periods of a 168MHz clock it takes to aproximate 1ms.
	 */
	reload = 168000000 / 1000;

	writel(base, SYST_RVR, reload - 1);

	/* writing anything to clear current value */
	writel(base, SYST_CVR, 0);

	/*
	 * We know we're just starting out and timer is disabled. So just enable
	 * it and get it over with.
	 */
	csr = SYST_CSR_CLKSOURCE;
	writel(base, SYST_CSR, csr);
	csr |= SYST_CSR_TICKINT;
	writel(base, SYST_CSR, csr);
	csr |= SYST_CSR_ENABLE;
	writel(base, SYST_CSR, csr);

	writel(scb, SCB_SHPR3, 0x00ff0000);

	return 0;

err0:
	return ret;
}
postcore_init(timer_init);
