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

#include <sys/stat.h>
#include <errno.h>

#include <m4naos/kernel.h>
#include <m4naos/uart.h>

static inline char *__get_stack_ptr(void)
{
	register char *result;

	asm ("mrs %0, msp\n" : "=r" (result) );

	return result;
}

caddr_t __used _sbrk(int incr)
{
	extern char _end;
	static char *heap_end = &_end;
	char *prev_heap_end = heap_end;

	if (heap_end + incr > __get_stack_ptr()) {
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	/* TODO: should we make sure heap won't touch the stack? */

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

int __used _close(int fd __unused)
{
	return -1;
}

int __used _fstat(int fd __unused, struct stat *st)
{
	st->st_mode = S_IFCHR;

	return 0;
}

int __used _isatty(int fd __unused)
{
	return 1;
}

int __used _lseek(int fd __unused, int ptr __unused, int dir __unused)
{
	return 0;
}

int __used _read(int fd __unused, char *ptr __unused, int len __unused)
{
	return 0;
}

int __used _write(int file __unused, char *str, int len)
{
	int i;

	for (i = 0; i < len; i++)
		uart_putch(*str++);

	return len;
}

void __used _exit(int status __unused)
{
	for (;;);
}

int __used _kill(int pid __unused, int sig __unused)
{
	errno = EINVAL;

	return -1;
}

int __used _getpid(void)
{
	return 1;
}
