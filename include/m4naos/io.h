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

#ifndef __M4NAOS_IO_H
#define __M4NAOS_IO_H

#include <m4naos/kernel.h>
#include <m4naos/hardware.h>

static inline void __iomem *ioremap(phys_addr_t offset)
{
	return (void __iomem *)(unsigned long) offset;
}

static inline void writeb_relaxed(u32 base,
		u32 offset, u8 value)
{
	*((volatile u8 *) (base + offset)) = value;
}

static inline u8 readb_relaxed(u32 base,
		u32 offset)
{
	return *((volatile u8 *) (base + offset));
}

static inline void writew_relaxed(u32 base,
		u32 offset, u16 value)
{
	*((volatile u16 *) (base + offset)) = value;
}

static inline u16 readw_relaxed(u32 base,
		u32 offset)
{
	return *((volatile u16 *) (base + offset));
}

static inline void writel_relaxed(u32 base,
		u32 offset, u32 value)
{
	*((volatile u32 *) (base + offset)) = value;
}

static inline u32 readl_relaxed(u32 base,
		u32 offset)
{
	return *((volatile u32 *) (base + offset));
}

#define writeb(b, o, v)	({ __dsb(); writeb_relaxed((b), (o), (v)); })
#define readb(b, o)	({ u8 __v = readb_relaxed((b), (o)); __dsb(); __v; })
#define writew(b, o, v)	({ __dsb(); writew_relaxed((b), (o), (v)); })
#define readw(b, o)	({ u16 __v = readw_relaxed((b), (o)); __dsb(); __v; })
#define writel(b, o, v)	({ __dsb(); writel_relaxed((b), (o), (v)); })
#define readl(b, o)	({ u32 __v = readl_relaxed((b), (o)); __dsb(); __v; })

#define BIT(n)		(1 << (n))

#endif /* __M4NAOS_IO_H */
