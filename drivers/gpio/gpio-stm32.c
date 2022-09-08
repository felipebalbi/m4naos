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
#include <m4naos/irq.h>
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

struct gpio_stm32 {
	struct gpio_chip chip;
	struct device *dev;

	void __iomem *base;
	void __iomem *exti;
	u32 state;
};

static int gpio_stm32_request(struct gpio_chip *chip, int pin)
{
	return 0;
}

static void gpio_stm32_release(struct gpio_chip *chip, int pin)
{
}

static int gpio_stm32_set_direction(struct gpio_chip *chip, int pin, int dir)
{
	return 0;
}

static int gpio_stm32_set_bias(struct gpio_chip *chip, int ping, int bias)
{
	return 0;
}

static int gpio_stm32_set_speed(struct gpio_chip *chip, int pin, int speed)
{
	return 0;
}

static int gpio_stm32_set_value(struct gpio_chip *chip, int pin, int value)
{
	struct gpio_stm32 *gpio = container(chip, struct gpio_stm32, chip);

	if (!chip)
		return -ENODEV;

	if (pin < 0 || pin > chip->ngpio)
		return -EINVAL;

	if (value)
		writel(gpio->base, GPIO_BSRR, BIT(pin));
	else
		writel(gpio->base, GPIO_BSRR, BIT(pin + 16));

	return 0;
}

static int gpio_stm32_get_value(struct gpio_chip *chip, int pin)
{
	return 0;
}

static const struct gpio_ops gpio_stm32_ops = {
	.request	= gpio_stm32_request,
	.release	= gpio_stm32_release,
	.set_direction	= gpio_stm32_set_direction,
	.set_bias	= gpio_stm32_set_bias,
	.set_speed	= gpio_stm32_set_speed,
	.set_value	= gpio_stm32_set_value,
	.get_value	= gpio_stm32_get_value,
};

static void gpio_configure_pinmux(struct gpio_stm32 *gpio)
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
		reg = readl(gpio->base, GPIO_MODER);
		reg &= ~(3 << (pin << 1));
		reg |= (pinconf->mode << (pin << 1));
		writel(gpio->base, GPIO_MODER, reg);

		/* configure pin type */
		reg = readl(gpio->base, GPIO_OTYPER);
		if (pinconf->type)
			reg |= BIT(pin);
		else
			reg &= ~BIT(pin);
		writel(gpio->base, GPIO_OTYPER, reg);

		/* configure pin speed */
		reg = readl(gpio->base, GPIO_OSPEEDR);
		reg &= ~(3 << (pin << 1));
		reg |= (pinconf->speed << (pin << 1));
		writel(gpio->base, GPIO_OSPEEDR, reg);

		/* configure pin pull-up/down */
		reg = readl(gpio->base, GPIO_PUPDR);
		reg &= ~(3 << (pin << 1));
		reg |= (pinconf->pull_up_down << (pin << 1));
		writel(gpio->base, GPIO_PUPDR, reg);

		/* configure pin function */
		if (pin > 7) {
			reg = readl(gpio->base, GPIO_AFRH);
			reg &= ~(0x0f << ((pin - 8) << 2));
			reg |= (pinconf->function << ((pin - 8) << 2));
			writel(gpio->base, GPIO_AFRH, reg);
		} else {
			reg = readl(gpio->base, GPIO_AFRL);
			reg &= ~(0x0f << (pin << 2));
			reg |= (pinconf->function << (pin << 2));
			writel(gpio->base, GPIO_AFRL, reg);
		}
	}
}

static irqreturn_t gpio_stm32_interrupt(int irq, void *_gpio)
{
	struct gpio_stm32 *gpio = _gpio;
	u32 reg;

	writel(gpio->base, GPIO_BSRR, gpio->state);
	gpio->state ^= BIT(1) | BIT(17);

	/* Clearing all events */
	reg = readl(gpio->exti, 0x14);
	writel(gpio->exti, 0x14, reg);

	return IRQ_HANDLED;
}

static int gpio_stm32_probe(struct device *dev)
{
	const struct resource *res;
	struct gpio_stm32 *gpio;
	int irq_requested = false;
	int ret;
	u32 reg;

	gpio = malloc(sizeof(*gpio));
	if (!gpio) {
		ret = -ENOMEM;
		goto err0;
	}

	gpio->dev = dev;
	gpio->chip.ops = &gpio_stm32_ops;
	gpio->chip.ngpio = 16;
	dev_set_drvdata(dev, gpio);

	res = device_get_resource(dev, RESOURCE_TYPE_IO_MEM, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err0;
	}

	gpio->base = ioremap(res->start);
	if (!gpio->base) {
		ret = -ENOMEM;
		goto err1;
	}

	res = device_get_resource(dev, RESOURCE_TYPE_CLK, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err1;
	}

	clk_enable(res->start, BIT(res->flags));

	/* setup pinmux */
	gpio_configure_pinmux(gpio);

	res = device_get_resource(dev, RESOURCE_TYPE_IRQ, 0);
	if (res) {
		ret = request_irq(res->start, gpio_stm32_interrupt, res->flags,
				gpio);
		if (ret)
			goto err2;

		irq_requested = true;
		gpio->state = BIT(1);

		gpio->exti = ioremap(APB2_EXTI);
		if (!gpio->exti) {
			ret = -ENOMEM;
			goto err3;
		}

		/* Falling trigger */
		switch (res->flags) {
		case IRQ_TRIGGER_TYPE_EDGE_FALLING:
			reg = readl(gpio->exti, 0x0c);
			reg |= BIT(0);
			writel(gpio->exti, 0x0c, reg);
			break;
		default:
			/* nothing */
			break;
		}

		/* Interrupt Mask */
		reg = readl(gpio->exti, 0x00);
		reg |= BIT(0);
		writel(gpio->exti, 0x00, reg);
	}

	ret = gpio_register(&gpio->chip);
	if (ret)
		goto err3;

	return 0;

err3:
	if (irq_requested)
		release_irq(6, gpio);

err2:
	clk_disable(dev->clk->offset, BIT(dev->clk->bit));

err1:
	free(gpio);

err0:
	return ret;
}

static struct driver gpio_stm32_driver = {
	.name		= "gpio",
	.probe		= gpio_stm32_probe,
};

module_driver_register(gpio_stm32_driver);
