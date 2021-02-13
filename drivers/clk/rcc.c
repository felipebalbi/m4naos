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
#include <m4naos/rcc.h>
#include <m4naos/io.h>

int clk_enable(u32 offset, u32 mask)
{
	u32 reg;

	reg = readl(AHB1_RCC, offset);
	reg |= mask;
	writel(AHB1_RCC, offset, reg);

	return 0;
}

void clk_disable(u32 offset, u32 mask)
{
	u32 reg;

	reg = readl(AHB1_RCC, offset);
	reg &= ~mask;
	writel(AHB1_RCC, offset, reg);
}

static int rcc_init(void)
{
	printf("postcore: %s\n", __func__);

	return 0;
}
postcore_init(rcc_init);
