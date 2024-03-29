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

#ifndef __M4NAOS_VERSION_H
#define __M4NAOS_VERSION_H

#define M4NAOS_VERSION	((M4NAOS_VERSION_MAJOR << 8)	|\
			 (M4NAOS_VERSION_MINOR << 4)	|\
			 (M4NAOS_VERSION_PATCH << 0))

#define M4NAOS_VERSION_STR M4NAOS_VERSION_MAJOR_STR "."	\
			M4NAOS_VERSION_MINOR_STR "."	\
			M4NAOS_VERSION_PATCH_STR "-"	\
			M4NAOS_VERSION_GIT_STR

#endif /* __M4NAOS_VERSION_H */

