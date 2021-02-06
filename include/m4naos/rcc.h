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

#ifndef __M4NAOS_RCC_H
#define __M4NAOS_RCC_H

#include <m4naos/hardware.h>

#define RCC_CR		0x00
#define RCC_PLLCFGR	0x04
#define RCC_CFGR	0x08
#define RCC_CIR		0x0c
#define RCC_AHB1RSTR	0x10
#define RCC_AHB2RSTR	0x14
#define RCC_AHB3RSTR	0x18
#define RCC_APB1RSTR	0x20
#define RCC_APB2RSTR	0x24
#define RCC_AHB1ENR	0x30
#define RCC_AHB2ENR	0x34
#define RCC_APB1ENR	0x40
#define RCC_APB2ENR	0x44
#define RCC_AHB1LPENR	0x50
#define RCC_AHB2LPENR	0x54
#define RCC_AHB3LPENR	0x58
#define RCC_APB1LPENR	0x60
#define RCC_APB2LPENR	0x64
#define RCC_BDCR	0x70
#define RCC_CSR		0x74
#define RCC_SSCGR	0x80
#define RCC_PLLI2SCFGR	0x84
#define RCC_PLLSAICFGR	0x88
#define RCC_DCKCFGR	0x8c

int clk_enable(u32 offset, u32 mask);
void clk_disable(u32 offset, u32 mask);

#endif /* __M4NAOS_RCC_H */
