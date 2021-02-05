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

#ifndef __M4NAOS_LOCK_H
#define __M4NAOS_LOCK_H

void __lock(void);
void __unlock(void);
void __save_irq_flags(u32 *flags);
void __restore_irq_flags(u32 *flags);

static inline void lock(void)
{
	__lock();
}

static inline void unlock(void)
{
	__unlock();
}

static inline void lock_irqsave(u32 *flags)
{
	__save_irq_flags(flags);
	__lock();
}

static inline void unlock_irqrestore(u32 *flags)
{
	__unlock();
	__restore_irq_flags(flags);
}

#endif /* __M4NAOS_LOCK_H */
