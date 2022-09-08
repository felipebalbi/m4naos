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
#include <m4naos/driver.h>
#include <m4naos/device.h>
#include <m4naos/hardware.h>
#include <m4naos/rcc.h>
#include <m4naos/io.h>

#define FLASH_ACR		0x00
#define FLASH_KEYR		0x04
#define FLASH_OPTKEYR		0x08
#define FLASH_SR		0x0c
#define FLASH_CR		0x10
#define FLASH_OPTCR		0x14

#define FLASH_ACR_LATENCY(n)	((n) & 7)
#define FLASH_ACR_PRFTEN	BIT(8)
#define FLASH_ACR_ICEN		BIT(9)
#define FLASH_ACR_DCEN		BIT(10)
#define FLASH_ACR_ICRST		BIT(11)
#define FLASH_ACR_DCRST		BIT(12)

static int flash_probe(struct device *dev)
{
	const struct resource *res;
	void __iomem *base;
	int ret;

	res = device_get_resource(dev, RESOURCE_TYPE_IO_MEM, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err0;
	}

	base = ioremap(res->start);
	if (!base) {
		ret = -ENOMEM;
		goto err0;
	}

	/* Enable Icache and Dcache, waitstate = 5 */
	writel(base, FLASH_ACR, FLASH_ACR_DCEN | FLASH_ACR_ICEN
			| FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY(5));

	return 0;

err0:
	return ret;
}

static struct driver flash_driver = {
	.name		= "flash",
	.probe		= flash_probe,
};

early_driver_register(flash_driver);
