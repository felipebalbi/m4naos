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

#ifndef __M4NAOS_DEVICE_H
#define __M4NAOS_DEVICE_H

#include <m4naos/clk.h>
#include <m4naos/kernel.h>
#include <m4naos/list.h>
#include <m4naos/reset.h>

enum resource_type {
	RESOURCE_TYPE_IO_MEM,
	RESOURCE_TYPE_CLK,
	RESOURCE_TYPE_RESET,
	RESOURCE_TYPE_IRQ,
};

struct resource {
	enum resource_type type;
	int		start;
	int		flags;
};

struct device {
	const struct resource **resources;
	int		num_resources;

	struct reset	*reset;
	struct clk	*clk;
	char		name[16];
	u32		base;
	int		status;
	void		*drvdata;
	const void	*platform_data;
};

static inline void dev_set_drvdata(struct device *dev, void *data)
{
	dev->drvdata = data;
}

static inline void *dev_get_drvdata(struct device *dev)
{
	return dev->drvdata;
}

int register_devices(struct device **devices, int n);

void machine_init_devices(void);

#endif /* __M4NAOS_DEVICE_H */
