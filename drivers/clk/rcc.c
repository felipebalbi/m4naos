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

struct rcc {
	const struct device *dev;
	void __iomem *base;
};

struct rcc *the_rcc;

int clk_enable(u32 offset, u32 mask)
{
	u32 reg;

	reg = readl(AHB1_RCC, offset);
	reg |= mask;
	writel(AHB1_RCC, offset, reg);

	return 0;
}

void clk_disable(u32 offset, u32 mask)
{
	u32 reg;

	reg = readl(AHB1_RCC, offset);
	reg &= ~mask;
	writel(AHB1_RCC, offset, reg);
}

static int rcc_probe(struct device *dev)
{
	struct rcc *rcc;
	int ret;

	rcc = malloc(sizeof(*rcc));
	if (!rcc) {
		ret = -ENOMEM;
		goto err0;
	}

	rcc->dev = dev;
	dev_set_drvdata(dev, rcc);

	rcc->base = ioremap(dev->base);
	if (!rcc->base) {
		ret = -ENOMEM;
		goto err1;
	}

	the_rcc = rcc;

	printf("core: %s: rcc %p base %p\n",
			__func__, rcc, rcc->base);

	return 0;

err1:
	free(rcc);

err0:
	return ret;
}

static struct driver rcc_driver = {
	.name		= "rcc",
	.probe		= rcc_probe,
};

static int rcc_init(void)
{
	return register_driver(&rcc_driver);
}
core_init(rcc_init);
