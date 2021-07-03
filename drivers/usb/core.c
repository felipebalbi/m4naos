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
#include <stdlib.h>
#include <m4naos/device.h>
#include <m4naos/driver.h>
#include <m4naos/io.h>
#include <m4naos/usb.h>

static struct usb_hw *udc = NULL;

int register_usb(struct usb_hw *hw)
{
	if (hw)
		return -EINVAL;

	udc = hw;

	return 0;
}

static int usb_core_init(void)
{
}
subsys_init(usb_core_init);
