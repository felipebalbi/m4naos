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

#define HSE_FREQ		8000000 /* Hz */
#define VCO_FREQ		2000000 /* Hz */
#define PLL_FREQ		168000000 /* Hz */

#define RCC_CR_HSION		BIT(0)
#define RCC_CR_HSIRDY		BIT(1)
/* HSITRIM and HSICAL left out */
#define RCC_CR_HSEON		BIT(16)
#define RCC_CR_HSERDY		BIT(17)
#define RCC_CR_HSEBYP		BIT(18)
#define RCC_CR_CSSON		BIT(19)
#define RCC_CR_PLLON		BIT(24)
#define RCC_CR_PLLRDY		BIT(25)
#define RCC_CR_PLL2SON		BIT(26)
#define RCC_CR_PLL2SRDY		BIT(27)

#define RCC_PLLCFGR_MASK	0xf0bc8000
#define RCC_PLLCFGR_PLLM(n)	((n) & 0x3f)
#define RCC_PLLCFGR_PLLN(n)	(((n) & 0x1ff) << 6)
#define RCC_PLLCFGR_PLLP(n)	(((n) & 0x03) << 16)
#define RCC_PLLCFGR_PLLSRC	BIT(22) /* 0 = HSI, 1 = HSE */
#define RCC_PLLCFGR_PLLQ(n)	(((n) & 0x0f) << 24)

#define RCC_CFGR_SW(n)		((n) & 0x03)
#define RCC_CFGR_SWS(n)		(((n) & (0x03 << 2)) >> 2)
#define RCC_CFGR_HPRE(n)	(((n) & 0x0f) << 4)
#define RCC_CFGR_PPRE1(n)	(((n) & 0x07) << 10)
#define RCC_CFGR_PPRE2(n)	(((n) & 0x07) << 13)
#define RCC_CFGR_RTCPRE(n)	(((n) & 0x3f) << 16)
#define RCC_CFGR_MCO1(n)	(((n) & 0x03) << 21)
#define RCC_CFGR_I2SSRC		BIT(23)
#define RCC_CFGR_MCO1PRE(n)	(((n) & 0x07) << 26)
#define RCC_CFGR_MCO2PRE(n)	(((n) & 0x07) << 29)
#define RCC_CFGR_MCO2(n)	(((n) & 0x03) << 30)

#define RCC_CFGR_HPRE_NODIV	0x00
#define RCC_CFGR_HPRE_DIV2	0x08
#define RCC_CFGR_HPRE_DIV4	0x09
#define RCC_CFGR_HPRE_DIV8	0x0a
#define RCC_CFGR_HPRE_DIV16	0x0b
#define RCC_CFGR_HPRE_DIV64	0x0c
#define RCC_CFGR_HPRE_DIV128	0x0d
#define RCC_CFGR_HPRE_DIV256	0x0e
#define RCC_CFGR_HPRE_DIV512	0x0f
#define RCC_CFGR_HPRE_MASK	(RCC_CFGR_HPRE(RCC_CFGR_HPRE_DIV512))

#define RCC_CFGR_PPRE_NODIV	0x00
#define RCC_CFGR_PPRE_DIV2	0x04
#define RCC_CFGR_PPRE_DIV4	0x05
#define RCC_CFGR_PPRE_DIV8	0x06
#define RCC_CFGR_PPRE_DIV16	0x07
#define RCC_CFGR_PPRE1_MASK	(RCC_CFGR_PPRE1(RCC_CFGR_PPRE_DIV16))
#define RCC_CFGR_PPRE2_MASK	(RCC_CFGR_PPRE2(RCC_CFGR_PPRE_DIV16))

#define RCC_CFGR_SW_HSI		0x00
#define RCC_CFGR_SW_HSE		0x01
#define RCC_CFGR_SW_PLL		0x02

#define RCC_CFGR_SW_MASK	(RCC_CFGR_SW(3))

struct rcc {
	const struct device *dev;
	void __iomem *base;
};

static struct rcc *the_rcc;

static void system_clock_init(struct rcc *rcc)
{
	u32 reg;

	/* Make sure PLLs are disabled */
	reg = readl(rcc->base, RCC_CR);
	reg &= ~(RCC_CR_PLLON | RCC_CR_PLL2SON);
	writel(rcc->base, RCC_CR, reg);

	/* Enable HSE */
	reg |= RCC_CR_HSEON;
	writel(rcc->base, RCC_CR, reg);

	/* Poll for HSERDY */
	while (!(reg & RCC_CR_HSERDY))
		reg = readl(rcc->base, RCC_CR);

	reg = readl(rcc->base, RCC_PLLCFGR);
	reg &= RCC_PLLCFGR_MASK;
	reg |= RCC_PLLCFGR_PLLM(4) | RCC_PLLCFGR_PLLN(336) |
		RCC_PLLCFGR_PLLP(1) | RCC_PLLCFGR_PLLQ(14) |
		RCC_PLLCFGR_PLLSRC;
	writel(rcc->base, RCC_PLLCFGR, reg);

	/* enable PLL */
	reg = readl(rcc->base, RCC_CR);
	reg |= RCC_CR_PLLON;
	writel(rcc->base, RCC_CR, reg);

	/* Poll for PLLRDY */
	while (!(reg & RCC_CR_PLLRDY))
		reg = readl(rcc->base, RCC_CR);

	/* setup prescalers */
	reg &= ~(RCC_CFGR_HPRE_MASK | RCC_CFGR_PPRE1_MASK |
			RCC_CFGR_PPRE2_MASK);
	reg |= RCC_CFGR_PPRE1(RCC_CFGR_PPRE_DIV4) |
		RCC_CFGR_PPRE2(RCC_CFGR_PPRE_DIV2);
	writel(rcc->base, RCC_CFGR, reg);

	/* set sysclk source to PLL */
	reg = readl(rcc->base, RCC_CFGR);
	reg &= ~RCC_CFGR_SW_MASK;
	reg |= RCC_CFGR_SW(RCC_CFGR_SW_PLL);
	writel(rcc->base, RCC_CFGR, reg);

	while (RCC_CFGR_SWS(reg) != 2)
		reg = readl(rcc->base, RCC_CFGR);

	reg = readl(rcc->base, RCC_CR);
	reg &= ~RCC_CR_HSION;
	writel(rcc->base, RCC_CR, reg);
}

int clk_enable(u32 offset, u32 mask)
{
	u32 reg;

	reg = readl(the_rcc->base, offset);
	reg |= mask;
	writel(the_rcc->base, offset, reg);

	return 0;
}

void clk_disable(u32 offset, u32 mask)
{
	u32 reg;

	reg = readl(the_rcc->base, offset);
	reg &= ~mask;
	writel(the_rcc->base, offset, reg);
}

static int rcc_probe(struct device *dev)
{
	const struct resource *res;
	struct rcc *rcc;
	int ret;

	rcc = malloc(sizeof(*rcc));
	if (!rcc) {
		ret = -ENOMEM;
		goto err0;
	}

	rcc->dev = dev;
	dev_set_drvdata(dev, rcc);

	res = device_get_resource(dev, RESOURCE_TYPE_IO_MEM, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err1;
	}

	rcc->base = ioremap(res->start);
	if (!rcc->base) {
		ret = -ENOMEM;
		goto err1;
	}

	system_clock_init(rcc);
	the_rcc = rcc;

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

core_driver_register(rcc_driver);
