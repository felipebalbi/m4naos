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

#ifndef __RESET_H
#define __RESET_H

#define VTABLE_STACK_POINTER	0
#define VTABLE_RESET		1
#define VTABLE_NMI		2
#define VTABLE_HARDFAULT	3
#define VTABLE_MMU_FAULT	4
#define VTABLE_BUS_FAULT	5
#define VTABLE_USAGE_FAULT	6
/* Reserved 7 - 10 */
#define VTABLE_SVC		11
#define VTABLE_DBGMON		12
/* Reserved 12 - 13 */
#define VTABLE_PENDSV		14
#define VTABLE_SYSTICK		15
#define VTABLE_IRQ0		(16+0)
#define VTABLE_IRQ1		(16+1)
#define VTABLE_IRQ2		(16+2)
#define VTABLE_IRQ3		(16+3)
#define VTABLE_IRQ4		(16+4)
#define VTABLE_IRQ5		(16+5)
#define VTABLE_IRQ6		(16+6)
#define VTABLE_IRQ7		(16+7)
#define VTABLE_IRQ8		(16+8)
#define VTABLE_IRQ9		(16+9)
#define VTABLE_IRQ10		(16+10)
#define VTABLE_IRQ11		(16+11)
#define VTABLE_IRQ12		(16+12)
#define VTABLE_IRQ13		(16+13)
#define VTABLE_IRQ14		(16+14)
#define VTABLE_IRQ15		(16+15)
#define VTABLE_IRQ16		(16+16)
#define VTABLE_IRQ17		(16+17)
#define VTABLE_IRQ18		(16+18)
#define VTABLE_IRQ19		(16+19)
#define VTABLE_IRQ20		(16+20)
#define VTABLE_IRQ21		(16+21)
#define VTABLE_IRQ22		(16+22)
#define VTABLE_IRQ23		(16+23)
#define VTABLE_IRQ24		(16+24)
#define VTABLE_IRQ25		(16+25)
#define VTABLE_IRQ26		(16+26)
#define VTABLE_IRQ27		(16+27)
#define VTABLE_IRQ28		(16+28)
#define VTABLE_IRQ29		(16+29)
#define VTABLE_IRQ30		(16+30)
#define VTABLE_IRQ31		(16+31)
#define VTABLE_IRQ32		(16+32)
#define VTABLE_IRQ33		(16+33)
#define VTABLE_IRQ34		(16+34)
#define VTABLE_IRQ35		(16+35)
#define VTABLE_IRQ36		(16+36)
#define VTABLE_IRQ37		(16+37)
#define VTABLE_IRQ38		(16+38)
#define VTABLE_IRQ39		(16+39)
#define VTABLE_IRQ40		(16+40)
#define VTABLE_IRQ41		(16+41)
#define VTABLE_IRQ42		(16+42)
#define VTABLE_IRQ43		(16+43)
#define VTABLE_IRQ44		(16+44)
#define VTABLE_IRQ45		(16+45)
#define VTABLE_IRQ46		(16+46)
#define VTABLE_IRQ47		(16+47)
#define VTABLE_IRQ48		(16+48)
#define VTABLE_IRQ49		(16+49)
#define VTABLE_IRQ50		(16+50)
#define VTABLE_IRQ51		(16+51)
#define VTABLE_IRQ52		(16+52)
#define VTABLE_IRQ53		(16+53)
#define VTABLE_IRQ54		(16+54)
#define VTABLE_IRQ55		(16+55)
#define VTABLE_IRQ56		(16+56)
#define VTABLE_IRQ57		(16+57)
#define VTABLE_IRQ58		(16+58)
#define VTABLE_IRQ59		(16+59)
#define VTABLE_IRQ60		(16+60)
#define VTABLE_IRQ61		(16+61)
#define VTABLE_IRQ62		(16+62)
#define VTABLE_IRQ63		(16+63)
#define VTABLE_IRQ64		(16+64)
#define VTABLE_IRQ65		(16+65)
#define VTABLE_IRQ66		(16+66)
#define VTABLE_IRQ67		(16+67)
#define VTABLE_IRQ68		(16+68)
#define VTABLE_IRQ69		(16+69)
#define VTABLE_IRQ70		(16+70)
#define VTABLE_IRQ71		(16+71)
#define VTABLE_IRQ72		(16+72)
#define VTABLE_IRQ73		(16+73)
#define VTABLE_IRQ74		(16+74)
#define VTABLE_IRQ75		(16+75)
#define VTABLE_IRQ76		(16+76)
#define VTABLE_IRQ77		(16+77)
#define VTABLE_IRQ78		(16+78)
#define VTABLE_IRQ79		(16+79)
#define VTABLE_IRQ80		(16+80)
#define VTABLE_IRQ81		(16+81)

#endif /* __RESET_H */
