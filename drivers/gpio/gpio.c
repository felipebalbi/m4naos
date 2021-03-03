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
#include <m4naos/gpio.h>
#include <m4naos/io.h>
#include <m4naos/kernel.h>
#include <m4naos/rcc.h>

#define GPIO_MODER		0x00
#define GPIO_OTYPER		0x04
#define GPIO_OSPEEDR		0x08
#define GPIO_PUPDR		0x0c
#define GPIO_IDR		0x10
#define GPIO_ODR		0x14
#define GPIO_BSRR		0x18
#define GPIO_LCKR		0x1c
#define GPIO_AFRL		0x20
#define GPIO_AFRH		0x24

struct gpio {
	struct device *dev;

	void __iomem *base;
};

static void gpio_configure_pinmux(struct gpio *gpio)
{
	const struct gpio_platform_data *pdata = gpio->dev->platform_data;
	int i;

	if (!pdata)
		return;

	for (i = 0; i < pdata->num_pins; i++) {
		const struct gpio_pinconf *pinconf = pdata->pinconf[i];
		int pin = pinconf->pin;
		u32 reg;

		if (pin > 15)
			continue;

		/* configure pin mode */
		reg = readl((u32) gpio->base, GPIO_MODER);
		reg &= ~(3 << (pin << 1));
		reg |= (pinconf->mode << (pin << 1));
		writel((u32) gpio->base, GPIO_MODER, reg);

		/* configure pin type */
		reg = readl((u32) gpio->base, GPIO_OTYPER);
		if (pinconf->type)
			reg |= BIT(pin);
		else
			reg &= ~BIT(pin);
		writel((u32) gpio->base, GPIO_OTYPER, reg);

		/* configure pin speed */
		reg = readl((u32) gpio->base, GPIO_OSPEEDR);
		reg &= ~(3 << (pin << 1));
		reg |= (pinconf->speed << (pin << 1));
		writel((u32) gpio->base, GPIO_OSPEEDR, reg);

		/* configure pin pull-up/down */
		reg = readl((u32) gpio->base, GPIO_PUPDR);
		reg &= ~(3 << (pin << 1));
		reg |= (pinconf->pull_up_down << (pin << 1));
		writel((u32) gpio->base, GPIO_PUPDR, reg);

		/* configure pin function */
		if (pin > 7) {
			reg = readl((u32) gpio->base, GPIO_AFRH);
			reg &= ~(0x0f << ((pin - 8) << 2));
			reg |= (pinconf->function << ((pin - 8) << 2));
			writel((u32) gpio->base, GPIO_AFRH, reg);
		} else {
			reg = readl((u32) gpio->base, GPIO_AFRL);
			reg &= ~(0x0f << (pin << 2));
			reg |= (pinconf->function << (pin << 2));
			writel((u32) gpio->base, GPIO_AFRL, reg);
		}
	}
}

static int gpio_probe(struct device *dev)
{
	struct gpio *gpio;
	int ret;

	gpio = malloc(sizeof(*gpio));
	if (!gpio) {
		ret = -ENOMEM;
		goto err0;
	}

	gpio->dev = dev;
	dev_set_drvdata(dev, gpio);

	gpio->base = ioremap(dev->base);
	if (!gpio->base) {
		ret = -ENOMEM;
		goto err1;
	}

	clk_enable(dev->clk->offset, BIT(dev->clk->bit));

	/* setup pinmux */
	gpio_configure_pinmux(gpio);

	return 0;

err1:
	free(gpio);

err0:
	return ret;
}

static struct driver gpio_driver = {
	.name		= "gpio",
	.probe		= gpio_probe,
};

static int gpio_init(void)
{
	return register_driver(&gpio_driver);
}
subsys_init(gpio_init);
