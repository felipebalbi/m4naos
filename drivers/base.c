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
#include <m4naos/list.h>
#include <m4naos/device.h>
#include <m4naos/driver.h>

static LIST_HEAD(drivers_list);
static LIST_HEAD(devices_list);

int register_device(struct device *dev)
{
	list_add_tail(&dev->list, &devices_list);
	return 0;
}

int register_driver(struct driver *drv)
{
	list_add_tail(&drv->list, &drivers_list);
	return 0;
}

int driver_match(struct device *dev, struct driver *drv)
{
	(void) dev;
	(void) drv;
	return 0;
}

int driver_probe(struct device *dev, struct driver *drv)
{
	(void) dev;
	(void) drv;
	return 0;
}
