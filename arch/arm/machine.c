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

#include <m4naos/hardware.h>
#include <m4naos/io.h>
#include <m4naos/kernel.h>
#include <m4naos/rcc.h>

static void fpu_init(void)
{
	u32 reg;

	reg = readl(FPU_BASE, FPU_CPACR);
	reg |= FPU_CPACR_CP10(3) | FPU_CPACR_CP11(3);
	writel(FPU_BASE, FPU_CPACR, reg);
}

void machine_init(void)
{
	fpu_init();
	system_timer_init();
}
