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
#include <m4naos/kernel.h>
#include <m4naos/string.h>

void *memset(void *s, int c, size_t n)
{
	char *cs = s;

	while (n--)
		*cs++ = c;
	return s;
}

void *memcpy(void *dst, const void *src, size_t n)
{
	char *tmp = dst;
	const char *s = src;

	while (n--)
		*tmp++ = *s++;

	return dst;
}

int putchar(int c)
{
	return c;
}

int puts(const char *str)
{
	while (*str) {
		putchar(*str++);
		if (*str == '\n')
			putchar('\r');
	}

	return 0;
}
