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
#include <m4naos/irq.h>
#include <m4naos/rcc.h>
#include <m4naos/usb.h>

struct dwc2 {
	struct device *dev;
	void __iomem *base;

	struct usb_hw usb;

	int clk_base;
	int clk_bit;
	int irq;
};

static irqreturn_t dwc_interrupt(int irq, void *_dwc)
{
	return IRQ_HANDLED;
}

static int dwc2_probe(struct device *dev)
{
	const struct resource *res;
	struct dwc2 *dwc;
	int ret;

	dwc = malloc(sizeof(*dwc));
	if (!dwc) {
		ret = -ENOMEM;
		goto err0;
	}

	dwc->dev = dev;
	dev_set_drvdata(dev, dwc);

	res = device_get_resource(dev, RESOURCE_TYPE_IO_MEM, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err1;
	}

	dwc->base = ioremap(res->start);
	if (!dwc->base) {
		ret = -ENOMEM;
		goto err1;
	}

	res = device_get_resource(dev, RESOURCE_TYPE_CLK, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err1;
	}

	dwc->clk_base = res->start;
	dwc->clk_bit = BIT(res->flags);
	clk_enable(dwc->clk_base, dwc->clk_bit);

	res = device_get_resource(dev, RESOURCE_TYPE_IRQ, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err2;
	}

	dwc->irq = res->start;

	ret = request_irq(dwc->irq, dwc_interrupt, res->flags, dwc);
	if (ret)
		goto err2;

	ret = register_usb(&dwc->usb);
	if (ret)
		goto err3;

	return 0;

err3:
	release_irq(dwc->irq, dwc);

err2:
	clk_disable(dwc->clk_base, dwc->clk_bit);

err1:
	free(dwc);

err0:
	return ret;
}

static struct driver dwc2_driver = {
	.name		= "dwc2",
	.probe		= dwc2_probe,
};

static int dwc2_init(void)
{
	return register_driver(&dwc2_driver);
}
module_init(dwc2_init);
