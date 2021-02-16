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

#include <m4naos/hardware.h>
#include <m4naos/io.h>
#include <m4naos/kernel.h>
#include <m4naos/rcc.h>
#include <m4naos/list.h>

#define USART_BRR	0x08
#define USART_CR1	0x0c
#define USART_CR2	0x10

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
#define RCC_CFGR_SWS(n)		(((n) & 0x03) << 2)
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

static void system_clock_init(void)
{
	u32 reg;

	/* Make sure PLLs are disabled */
	reg = readl(AHB1_RCC, RCC_CR);
	reg &= ~(RCC_CR_PLLON | RCC_CR_PLL2SON);
	writel(AHB1_RCC, RCC_CR, reg);

	/* Enable HSE */
	reg |= RCC_CR_HSEON;
	writel(AHB1_RCC, RCC_CR, reg);

	/* Poll for HSERDY */
	while (!(reg & RCC_CR_HSERDY))
		reg = readl(AHB1_RCC, RCC_CR);

	reg = readl(AHB1_RCC, RCC_PLLCFGR);
	reg &= ~RCC_PLLCFGR_MASK;
	reg |= RCC_PLLCFGR_PLLM(8) | RCC_PLLCFGR_PLLN(336) |
		RCC_PLLCFGR_PLLP(2) | RCC_PLLCFGR_PLLQ(7) |
		RCC_PLLCFGR_PLLSRC;
	writel(AHB1_RCC, RCC_PLLCFGR, reg);

	/* setup prescalers */
	reg = readl(AHB1_RCC, RCC_CFGR);
	reg &= ~(RCC_CFGR_HPRE_MASK | RCC_CFGR_PPRE1_MASK |
			RCC_CFGR_PPRE2_MASK);
	reg |= RCC_CFGR_PPRE1(RCC_CFGR_PPRE_DIV4) |
		RCC_CFGR_PPRE2(RCC_CFGR_PPRE_DIV2);
	writel(AHB1_RCC, RCC_CFGR, reg);

	/* enable PLL */
	reg = readl(AHB1_RCC, RCC_CR);
	reg |= RCC_CR_PLLON;
	writel(AHB1_RCC, RCC_CR, reg);

	/* Poll for PLLRDY */
	while (!(reg & RCC_CR_PLLRDY))
		reg = readl(AHB1_RCC, RCC_CR);

	/* set sysclk source to PLL */
	reg = readl(AHB1_RCC, RCC_CFGR);
	reg &= ~RCC_CFGR_SW_MASK;
	reg |= RCC_CFGR_SW(RCC_CFGR_SW_PLL);
	writel(AHB1_RCC, RCC_CFGR, reg);

	while (!(RCC_CFGR_SWS(reg) != RCC_CFGR_SWS(RCC_CFGR_SW_PLL)))
		reg = readl(AHB1_RCC, RCC_CFGR);
}

static void system_fpu_init(void)
{
	u32 reg;

	reg = readl(FPU_BASE, FPU_CPACR);
	reg |= FPU_CPACR_CP10(3) | FPU_CPACR_CP11(3);
	writel(FPU_BASE, FPU_CPACR, reg);
}

static void system_uart_init(void)
{
	u32 reg;

	clk_enable(RCC_AHB1ENR, BIT(0));
	clk_enable(RCC_APB2ENR, BIT(4));

	reg = readl(AHB1_GPIOA, 0x00);
	reg |= (2 << 18);
	writel(AHB1_GPIOA, 0x00, reg);

	reg = readl(AHB1_GPIOA, 0x24);
	reg |= (7 << 4);
	writel(AHB1_GPIOA, 0x24, reg);

	reg = readl(APB2_USART1, USART_CR1);
	reg |= 	BIT(13); /* UE */
	reg &= ~BIT(12); /* M */
	writel(APB2_USART1, USART_CR1, reg);

	reg = readl(APB2_USART1, USART_CR2);
	reg &= ~(3 << 12); /* 1 stop bit */
	writel(APB2_USART1, USART_CR2, reg);

	/*
	 * According to Table 137, page 982 on STM32F405 reference manual, the
	 * following results in a baud rate of 2Mbps with an error of 0%.
	 */
	reg = 0x10; /* 1.0 */
	writel(APB2_USART1, USART_BRR, reg);

	reg = readl(APB2_USART1, USART_CR1);
	reg |= 	BIT(15) | BIT(3); /* OVER8 | TE */
	writel(APB2_USART1, USART_CR1, reg);
}

void machine_init(void)
{
	system_clock_init();
	system_fpu_init();
	system_timer_init();
	system_uart_init();

	kernel_init();
}
