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

#include <stdio.h>
#include <string.h>
#include <m4naos/hardware.h>
#include <m4naos/kernel.h>
#include <m4naos/list.h>
#include <m4naos/device.h>
#include <m4naos/driver.h>

static LIST_HEAD(drivers_list);
static struct device **devices_table;
static int num_devices;

const struct resource *device_get_resource(struct device *dev,
		enum resource_type type, int num)
{
	const struct resource *res;
	int n = 0;
	int i;

	for (i = 0; i < dev->num_resources; i++) {
		res = dev->resources[i];

		if (res->type == type) {
			if (n == num)
				return res;
			n++;
		}
	}

	return NULL;
}

int register_driver(struct driver *drv)
{
	list_add_tail(&drv->list, &drivers_list);
	return 0;
}

int register_devices(struct device **devices, int n)
{
	devices_table = devices;
	num_devices = n;
	return 0;
}

int driver_match(struct device *dev, struct driver *drv)
{
	return !!strstr(dev->name, drv->name);
}

int driver_probe(struct device *dev, struct driver *drv)
{
	return drv->probe(dev);
}

int drivers_start(void)
{
	struct driver *drv;
	int ret;

	list_for_each_entry(drv, &drivers_list, list) {
		int i;

		for (i = 0; i < num_devices; i++) {
			struct device *dev = devices_table[i];

			if (!dev->status)
				continue;

			if (!driver_match(dev, drv))
				continue;

			ret = driver_probe(dev, drv);
			if (ret < 0)
				continue;
		}
	}

	return 0;
}
