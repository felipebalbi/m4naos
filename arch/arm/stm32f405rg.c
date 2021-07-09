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

#include <m4naos/gpio.h>
#include <m4naos/clk.h>
#include <m4naos/device.h>
#include <m4naos/hardware.h>
#include <m4naos/irq.h>
#include <m4naos/kernel.h>
#include <m4naos/reset.h>

/* APB1 */
static const struct resource timer2_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 0,
};

static const struct resource timer2_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 0,
};

static const struct resource timer2_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM2,
	.flags	= 0,
};

static const struct resource *timer2_resources[] = {
	&timer2_addr,
	&timer2_clk,
	&timer2_reset,
};

static struct device timer2_device __ccm = {
	.name	= "timer2",
	.status	= false,
	.resources = timer2_resources,
	.num_resources = ARRAY_SIZE(timer2_resources),
	.platform_data = NULL,
};

static const struct resource timer3_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 1,
};

static const struct resource timer3_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 1,
};

static const struct resource timer3_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM3,
	.flags	= 0,
};

static const struct resource *timer3_resources[] = {
	&timer3_addr,
	&timer3_clk,
	&timer3_reset,
};

static struct device timer3_device __ccm = {
	.name	= "timer3",
	.status	= false,
	.resources = timer3_resources,
	.num_resources = ARRAY_SIZE(timer3_resources),
	.platform_data = NULL,
};

static const struct resource timer4_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 2,
};

static const struct resource timer4_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 2,
};

static const struct resource timer4_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM4,
	.flags	= 0,
};

static const struct resource *timer4_resources[] = {
	&timer4_addr,
	&timer4_clk,
	&timer4_reset,
};

static struct device timer4_device __ccm = {
	.name	= "timer4",
	.status	= false,
	.resources = timer4_resources,
	.num_resources = ARRAY_SIZE(timer4_resources),
	.platform_data = NULL,
};

static const struct resource timer5_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 3,
};

static const struct resource timer5_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 3,
};

static const struct resource timer5_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM5,
	.flags	= 0,
};

static const struct resource *timer5_resources[] = {
	&timer5_addr,
	&timer5_clk,
	&timer5_reset,
};

static struct device timer5_device __ccm = {
	.name	= "timer5",
	.status	= false,
	.resources = timer5_resources,
	.num_resources = ARRAY_SIZE(timer5_resources),
	.platform_data = NULL,
};

static const struct resource timer6_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 4,
};

static const struct resource timer6_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 4,
};

static const struct resource timer6_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM5,
	.flags	= 0,
};

static const struct resource *timer6_resources[] = {
	&timer6_addr,
	&timer6_clk,
	&timer6_reset,
};

static struct device timer6_device __ccm = {
	.name	= "timer6",
	.status	= false,
	.resources = timer6_resources,
	.num_resources = ARRAY_SIZE(timer6_resources),
	.platform_data = NULL,
};

static const struct resource timer7_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 5,
};

static const struct resource timer7_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 5,
};

static const struct resource timer7_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM7,
	.flags	= 0,
};

static const struct resource *timer7_resources[] = {
	&timer7_addr,
	&timer7_clk,
	&timer7_reset,
};

static struct device timer7_device __ccm = {
	.name	= "timer7",
	.status	= false,
	.resources = timer7_resources,
	.num_resources = ARRAY_SIZE(timer7_resources),
	.platform_data = NULL,
};

static const struct resource timer12_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 6,
};

static const struct resource timer12_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 6,
};

static const struct resource timer12_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM12,
	.flags	= 0,
};

static const struct resource *timer12_resources[] = {
	&timer12_addr,
	&timer12_clk,
	&timer12_reset,
};

static struct device timer12_device __ccm = {
	.name	= "timer12",
	.status	= false,
	.resources = timer12_resources,
	.num_resources = ARRAY_SIZE(timer12_resources),
	.platform_data = NULL,
};

static const struct resource timer13_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 7,
};

static const struct resource timer13_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 7,
};

static const struct resource timer13_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM13,
	.flags	= 0,
};

static const struct resource *timer13_resources[] = {
	&timer13_addr,
	&timer13_clk,
	&timer13_reset,
};

static struct device timer13_device __ccm = {
	.name	= "timer13",
	.status	= false,
	.resources = timer13_resources,
	.num_resources = ARRAY_SIZE(timer13_resources),
	.platform_data = NULL,
};

static const struct resource timer14_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 8,
};

static const struct resource timer14_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 8,
};

static const struct resource timer14_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_TIM14,
	.flags	= 0,
};

static const struct resource *timer14_resources[] = {
	&timer14_addr,
	&timer14_clk,
	&timer14_reset,
};

static struct device timer14_device __ccm = {
	.name	= "timer14",
	.status	= false,
	.resources = timer14_resources,
	.num_resources = ARRAY_SIZE(timer14_resources),
	.platform_data = NULL,
};

static const struct resource wwdg_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 11,
};

static const struct resource wwdg_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 11,
};

static const struct resource wwdg_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_WWDG,
	.flags	= 0,
};

static const struct resource *wwdg_resources[] = {
	&wwdg_addr,
	&wwdg_clk,
	&wwdg_reset,
};

static struct device wwdg_device __ccm = {
	.name	= "wwdg",
	.status	= false,
	.resources = wwdg_resources,
	.num_resources = ARRAY_SIZE(wwdg_resources),
	.platform_data = NULL,
};

static const struct resource spi2_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 14,
};

static const struct resource spi2_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 14,
};

static const struct resource spi2_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_SPI2_I2S2,
	.flags	= 0,
};

static const struct resource *spi2_resources[] = {
	&spi2_addr,
	&spi2_clk,
	&spi2_reset,
};

static struct device spi2_device __ccm = {
	.name	= "spi2",
	.status	= false,
	.resources = spi2_resources,
	.num_resources = ARRAY_SIZE(spi2_resources),
	.platform_data = NULL,
};

static const struct resource spi3_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 15,
};

static const struct resource spi3_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 15,
};

static const struct resource spi3_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_SPI3_I2S3,
	.flags	= 0,
};

static const struct resource *spi3_resources[] = {
	&spi3_addr,
	&spi3_clk,
	&spi3_reset,
};

static struct device spi3_device __ccm = {
	.name	= "spi3",
	.status	= false,
	.resources = spi3_resources,
	.num_resources = ARRAY_SIZE(spi3_resources),
	.platform_data = NULL,
};

static const struct resource usart2_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 17,
};

static const struct resource usart2_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 17,
};

static const struct resource usart2_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_USART2,
	.flags	= 0,
};

static const struct resource *usart2_resources[] = {
	&usart2_addr,
	&usart2_clk,
	&usart2_reset,
};

static struct device usart2_device __ccm = {
	.name	= "usart2",
	.status	= false,
	.resources = usart2_resources,
	.num_resources = ARRAY_SIZE(usart2_resources),
	.platform_data = NULL,
};

static const struct resource usart3_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 18,
};

static const struct resource usart3_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 18,
};

static const struct resource usart3_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_USART3,
	.flags	= 0,
};

static const struct resource *usart3_resources[] = {
	&usart3_addr,
	&usart3_clk,
	&usart3_reset,
};

static struct device usart3_device __ccm = {
	.name	= "uart3",
	.status	= false,
	.resources = usart3_resources,
	.num_resources = ARRAY_SIZE(usart3_resources),
	.platform_data = NULL,
};

static const struct resource uart4_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 19,
};

static const struct resource uart4_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 19,
};

static const struct resource uart4_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_UART4,
	.flags	= 0,
};

static const struct resource *uart4_resources[] = {
	&uart4_addr,
	&uart4_clk,
	&uart4_reset,
};

static struct device uart4_device __ccm = {
	.name	= "uart4",
	.status	= false,
	.resources = uart4_resources,
	.num_resources = ARRAY_SIZE(uart4_resources),
	.platform_data = NULL,
};

static const struct resource uart5_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 20,
};

static const struct resource uart5_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 20,
};

static const struct resource uart5_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_UART5,
	.flags	= 0,
};

static const struct resource *uart5_resources[] = {
	&uart5_addr,
	&uart5_clk,
	&uart5_reset,
};

static struct device uart5_device __ccm = {
	.name	= "uart5",
	.status	= false,
	.resources = uart5_resources,
	.num_resources = ARRAY_SIZE(uart5_resources),
	.platform_data = NULL,
};

static const struct resource i2c1_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 21,
};

static const struct resource i2c1_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 21,
};

static const struct resource i2c1_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_I2C1,
	.flags	= 0,
};

static const struct resource *i2c1_resources[] = {
	&i2c1_addr,
	&i2c1_clk,
	&i2c1_reset,
};

static struct device i2c1_device __ccm = {
	.name	= "i2c1",
	.status	= false,
	.resources = i2c1_resources,
	.num_resources = ARRAY_SIZE(i2c1_resources),
	.platform_data = NULL,
};

static const struct resource i2c2_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 22,
};

static const struct resource i2c2_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 22,
};

static const struct resource i2c2_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_I2C2,
	.flags	= 0,
};

static const struct resource *i2c2_resources[] = {
	&i2c2_addr,
	&i2c2_clk,
	&i2c2_reset,
};

static struct device i2c2_device __ccm = {
	.name	= "i2c2",
	.status	= false,
	.resources = i2c2_resources,
	.num_resources = ARRAY_SIZE(i2c2_resources),
	.platform_data = NULL,
};

static const struct resource i2c3_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 23,
};

static const struct resource i2c3_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 23,
};

static const struct resource i2c3_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_I2C3,
	.flags	= 0,
};

static const struct resource *i2c3_resources[] = {
	&i2c3_addr,
	&i2c3_clk,
	&i2c3_reset,
};

static struct device i2c3_device __ccm = {
	.name	= "i2c3",
	.status	= false,
	.resources = i2c3_resources,
	.num_resources = ARRAY_SIZE(i2c3_resources),
	.platform_data = NULL,
};

static const struct resource can1_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 25,
};

static const struct resource can1_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 25,
};

static const struct resource can1_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_CAN1,
	.flags	= 0,
};

static const struct resource *can1_resources[] = {
	&can1_addr,
	&can1_clk,
	&can1_reset,
};

static struct device can1_device __ccm = {
	.name	= "can1",
	.status	= false,
	.resources = can1_resources,
	.num_resources = ARRAY_SIZE(can1_resources),
	.platform_data = NULL,
};

static const struct resource can2_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 26,
};

static const struct resource can2_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 26,
};

static const struct resource can2_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_CAN2,
	.flags	= 0,
};

static const struct resource *can2_resources[] = {
	&can2_addr,
	&can2_clk,
	&can2_reset,
};

static struct device can2_device __ccm = {
	.name	= "can2",
	.status	= false,
	.resources = can2_resources,
	.num_resources = ARRAY_SIZE(can2_resources),
	.platform_data = NULL,
};

static const struct resource pwr_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 28,
};

static const struct resource pwr_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 28,
};

static const struct resource pwr_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_PWR,
	.flags	= 0,
};

static const struct resource *pwr_resources[] = {
	&pwr_addr,
	&pwr_clk,
	&pwr_reset,
};

static struct device pwr_device __ccm = {
	.name	= "pwr",
	.status	= false,
	.resources = pwr_resources,
	.num_resources = ARRAY_SIZE(pwr_resources),
	.platform_data = NULL,
};

static const struct resource dac_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 29,
};

static const struct resource dac_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 29,
};

static const struct resource dac_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_DAC,
	.flags	= 0,
};

static const struct resource *dac_resources[] = {
	&dac_addr,
	&dac_clk,
	&dac_reset,
};

static struct device dac_device __ccm = {
	.name	= "dac",
	.status	= false,
	.resources = dac_resources,
	.num_resources = ARRAY_SIZE(dac_resources),
	.platform_data = NULL,
};

static const struct resource uart7_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 30,
};

static const struct resource uart7_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 30,
};

static const struct resource uart7_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_UART7,
	.flags	= 0,
};

static const struct resource *uart7_resources[] = {
	&uart7_addr,
	&uart7_clk,
	&uart7_reset,
};

static struct device uart7_device __ccm = {
	.name	= "uart7",
	.status	= false,
	.resources = uart7_resources,
	.num_resources = ARRAY_SIZE(uart7_resources),
	.platform_data = NULL,
};

static const struct resource uart8_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x40,
	.flags	= 31,
};

static const struct resource uart8_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x20,
	.flags	= 31,
};

static const struct resource uart8_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_UART8,
	.flags	= 0,
};

static const struct resource *uart8_resources[] = {
	&uart8_addr,
	&uart8_clk,
	&uart8_reset,
};

static struct device uart8_device __ccm = {
	.name	= "uart8",
	.status	= false,
	.resources = uart8_resources,
	.num_resources = ARRAY_SIZE(uart8_resources),
	.platform_data = NULL,
};

static const struct resource rtc_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_RTC,
	.flags	= 0,
};

static const struct resource *rtc_resources[] = {
	&rtc_addr,
};

static struct device rtc_device __ccm = {
	.name	= "rtc",
	.status	= false,
	.resources = rtc_resources,
	.num_resources = ARRAY_SIZE(rtc_resources),
	.platform_data = NULL,
};

static const struct resource iwdg_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_IWDG,
	.flags	= 0,
};

static const struct resource *iwdg_resources[] = {
	&iwdg_addr,
};

static struct device iwdg_device __ccm = {
	.name	= "iwdg",
	.status	= false,
	.resources = iwdg_resources,
	.num_resources = ARRAY_SIZE(iwdg_resources),
	.platform_data = NULL,
};

static const struct resource i2s2ext_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_I2S2EXT,
	.flags	= 0,
};

static const struct resource *i2s2ext_resources[] = {
	&i2s2ext_addr,
};

static struct device i2s2ext_device __ccm = {
	.name	= "i2s2ext",
	.status	= false,
	.resources = i2s2ext_resources,
	.num_resources = ARRAY_SIZE(i2s2ext_resources),
	.platform_data = NULL,
};

static const struct resource i2s3ext_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB1_I2S3EXT,
	.flags	= 0,
};

static const struct resource *i2s3ext_resources[] = {
	&i2s3ext_addr,
};

static struct device i2s3ext_device __ccm = {
	.name	= "i2s3ext",
	.status	= false,
	.resources = i2s3ext_resources,
	.num_resources = ARRAY_SIZE(i2s3ext_resources),
	.platform_data = NULL,
};

/* APB2 */
static const struct resource timer1_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 0,
};

static const struct resource timer1_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 0,
};

static const struct resource timer1_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_TIM1,
	.flags	= 0,
};

static const struct resource *timer1_resources[] = {
	&timer1_addr,
	&timer1_clk,
	&timer1_reset,
};

static struct device timer1_device __ccm = {
	.name	= "timer1",
	.status	= false,
	.resources = timer1_resources,
	.num_resources = ARRAY_SIZE(timer1_resources),
	.platform_data = NULL,
};

static const struct resource timer8_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 1,
};

static const struct resource timer8_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 1,
};

static const struct resource timer8_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_TIM8,
	.flags	= 0,
};

static const struct resource *timer8_resources[] = {
	&timer8_addr,
	&timer8_clk,
	&timer8_reset,
};

static struct device timer8_device __ccm = {
	.name	= "timer8",
	.status	= false,
	.resources = timer8_resources,
	.num_resources = ARRAY_SIZE(timer8_resources),
	.platform_data = NULL,
};

static const struct resource usart1_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 4,
};

static const struct resource usart1_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 4,
};

static const struct resource usart1_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_USART1,
	.flags	= 0,
};

static const struct resource *usart1_resources[] = {
	&usart1_addr,
	&usart1_clk,
	&usart1_reset,
};

static struct device usart1_device __ccm = {
	.name	= "usart1",
	.status	= false,
	.resources = usart1_resources,
	.num_resources = ARRAY_SIZE(usart1_resources),
	.platform_data = NULL,
};

static const struct resource usart6_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 5,
};

static const struct resource usart6_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 5,
};

static const struct resource usart6_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_USART6,
	.flags	= 0,
};

static const struct resource *usart6_resources[] = {
	&usart6_addr,
	&usart6_clk,
	&usart6_reset,
};

static struct device usart6_device __ccm = {
	.name	= "usart6",
	.status	= false,
	.resources = usart6_resources,
	.num_resources = ARRAY_SIZE(usart6_resources),
	.platform_data = NULL,
};

static const struct resource adc_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 8,
};

static const struct resource adc_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 8,
};

static const struct resource adc_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_ADC1_ADC2_ADC3,
	.flags	= 0,
};

static const struct resource *adc_resources[] = {
	&adc_addr,
	&adc_clk,
	&adc_reset,
};

static struct device adc_device __ccm = {
	.name	= "adc",
	.status	= false,
	.resources = adc_resources,
	.num_resources = ARRAY_SIZE(adc_resources),
	.platform_data = NULL,
};

static const struct resource sdio_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 11,
};

static const struct resource sdio_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 11,
};

static const struct resource sdio_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_SDIO,
	.flags	= 0,
};

static const struct resource *sdio_resources[] = {
	&sdio_addr,
	&sdio_clk,
	&sdio_reset,
};

static struct device sdio_device __ccm = {
	.name	= "sdio",
	.status	= false,
	.resources = sdio_resources,
	.num_resources = ARRAY_SIZE(sdio_resources),
	.platform_data = NULL,
};

static const struct resource spi1_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 12,
};

static const struct resource spi1_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 12,
};

static const struct resource spi1_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_SPI1,
	.flags	= 0,
};

static const struct resource *spi1_resources[] = {
	&spi1_addr,
	&spi1_clk,
	&spi1_reset,
};

static struct device spi1_device __ccm = {
	.name	= "spi1",
	.status	= false,
	.resources = spi1_resources,
	.num_resources = ARRAY_SIZE(spi1_resources),
	.platform_data = NULL,
};

static const struct resource syscfg_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 14,
};

static const struct resource syscfg_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 14,
};

static const struct resource syscfg_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_SYSCFG,
	.flags	= 0,
};

static const struct resource *syscfg_resources[] = {
	&syscfg_addr,
	&syscfg_clk,
	&syscfg_reset,
};

static struct device syscfg_device __ccm = {
	.name	= "syscfg",
	.status	= false,
	.resources = syscfg_resources,
	.num_resources = ARRAY_SIZE(syscfg_resources),
	.platform_data = NULL,
};

static const struct resource timer9_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 16,
};

static const struct resource timer9_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 16,
};

static const struct resource timer9_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_TIM9,
	.flags	= 0,
};

static const struct resource *timer9_resources[] = {
	&timer9_addr,
	&timer9_clk,
	&timer9_reset,
};

static struct device timer9_device __ccm = {
	.name	= "timer9",
	.status	= false,
	.resources = timer9_resources,
	.num_resources = ARRAY_SIZE(timer9_resources),
	.platform_data = NULL,
};

static const struct resource timer10_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 17,
};

static const struct resource timer10_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 17,
};

static const struct resource timer10_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_TIM10,
	.flags	= 0,
};

static const struct resource *timer10_resources[] = {
	&timer10_addr,
	&timer10_clk,
	&timer10_reset,
};

static struct device timer10_device __ccm = {
	.name	= "timer10",
	.status	= false,
	.resources = timer10_resources,
	.num_resources = ARRAY_SIZE(timer10_resources),
	.platform_data = NULL,
};

static const struct resource timer11_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x44,
	.flags	= 18,
};

static const struct resource timer11_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x24,
	.flags	= 18,
};

static const struct resource timer11_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_TIM11,
	.flags	= 0,
};

static const struct resource *timer11_resources[] = {
	&timer11_addr,
	&timer11_clk,
	&timer11_reset,
};

static struct device timer11_device __ccm = {
	.name	= "timer11",
	.status	= false,
	.resources = timer11_resources,
	.num_resources = ARRAY_SIZE(timer11_resources),
	.platform_data = NULL,
};

static const struct resource exti_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= APB2_EXTI,
	.flags	= 0,
};

static const struct resource *exti_resources[] = {
	&exti_addr,
};

static struct device exti_device __ccm = {
	.name	= "exti",
	.status	= false,
	.resources = exti_resources,
	.num_resources = ARRAY_SIZE(exti_resources),
	.platform_data = NULL,
};

/* AHB1 */
static const struct resource usb_otg_hs_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 29,
};

static const struct resource usb_otg_hs_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 29,
};

static const struct resource usb_otg_hs_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_USB_OTG_HS,
	.flags	= 0,
};

static const struct resource *usb_otg_hs_resources[] = {
	&usb_otg_hs_addr,
	&usb_otg_hs_clk,
	&usb_otg_hs_reset,
};

static struct device usb_otg_hs_device __ccm = {
	.name	= "dwc2",
	.status	= false,
	.resources = usb_otg_hs_resources,
	.num_resources = ARRAY_SIZE(usb_otg_hs_resources),
	.platform_data = NULL,
};

static const struct resource ethernet_mac_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 25,
};

static const struct resource ethernet_mac_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 25,
};

static const struct resource ethernet_mac_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_ETHERNET_MAC,
	.flags	= 0,
};

static const struct resource *ethernet_mac_resources[] = {
	&ethernet_mac_addr,
	&ethernet_mac_clk,
	&ethernet_mac_reset,
};

static struct device ethernet_mac_device __ccm = {
	.name	= "ethernet_mac",
	.status	= false,
	.resources = ethernet_mac_resources,
	.num_resources = ARRAY_SIZE(ethernet_mac_resources),
	.platform_data = NULL,
};

static const struct resource dma2_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 22,
};

static const struct resource dma2_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 22,
};

static const struct resource dma2_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_DMA2,
	.flags	= 0,
};

static const struct resource *dma2_resources[] = {
	&dma2_addr,
	&dma2_clk,
	&dma2_reset,
};

static struct device dma2_device __ccm = {
	.name	= "dma2",
	.status	= false,
	.resources = dma2_resources,
	.num_resources = ARRAY_SIZE(dma2_resources),
	.platform_data = NULL,
};

static const struct resource dma1_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 21,
};

static const struct resource dma1_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 21,
};

static const struct resource dma1_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_DMA1,
	.flags	= 0,
};

static const struct resource *dma1_resources[] = {
	&dma1_addr,
	&dma1_clk,
	&dma1_reset,
};

static struct device dma1_device __ccm = {
	.name	= "dma1",
	.status	= false,
	.resources = dma1_resources,
	.num_resources = ARRAY_SIZE(dma1_resources),
	.platform_data = NULL,
};

static const struct resource crc_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 12,
};

static const struct resource crc_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 12,
};

static const struct resource crc_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_CRC,
	.flags	= 0,
};

static const struct resource *crc_resources[] = {
	&crc_addr,
	&crc_clk,
	&crc_reset,
};

static struct device crc_device __ccm = {
	.name	= "crc",
	.status	= false,
	.resources = crc_resources,
	.num_resources = ARRAY_SIZE(crc_resources),
	.platform_data = NULL,
};

static const struct resource gpioi_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 8,
};

static const struct resource gpioi_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 8,
};

static const struct resource gpioi_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOI,
	.flags	= 0,
};

static const struct resource *gpioi_resources[] = {
	&gpioi_addr,
	&gpioi_clk,
	&gpioi_reset,
};

static struct device gpioi_device __ccm = {
	.name	= "gpioi",
	.status	= false,
	.resources = gpioi_resources,
	.num_resources = ARRAY_SIZE(gpioi_resources),
	.platform_data = NULL,
};

static const struct resource gpioh_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 7,
};

static const struct resource gpioh_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 7,
};

static const struct resource gpioh_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOH,
	.flags	= 0,
};

static const struct resource *gpioh_resources[] = {
	&gpioh_addr,
	&gpioh_clk,
	&gpioh_reset,
};

static struct device gpioh_device __ccm = {
	.name	= "gpioh",
	.status	= false,
	.resources = gpioh_resources,
	.num_resources = ARRAY_SIZE(gpioh_resources),
	.platform_data = NULL,
};

static const struct resource gpiog_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 6,
};

static const struct resource gpiog_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 6,
};

static const struct resource gpiog_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOG,
	.flags	= 0,
};

static const struct resource *gpiog_resources[] = {
	&gpiog_addr,
	&gpiog_clk,
	&gpiog_reset,
};

static struct device gpiog_device __ccm = {
	.name	= "gpiog",
	.status	= false,
	.resources = gpiog_resources,
	.num_resources = ARRAY_SIZE(gpiog_resources),
	.platform_data = NULL,
};

static const struct resource gpiof_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 5,
};

static const struct resource gpiof_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 5,
};

static const struct resource gpiof_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOF,
	.flags	= 0,
};

static const struct resource *gpiof_resources[] = {
	&gpiof_addr,
	&gpiof_clk,
	&gpiof_reset,
};

static struct device gpiof_device __ccm = {
	.name	= "gpiof",
	.status	= false,
	.resources = gpiof_resources,
	.num_resources = ARRAY_SIZE(gpiof_resources),
	.platform_data = NULL,
};

static const struct resource gpioe_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 4,
};

static const struct resource gpioe_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 4,
};

static const struct resource gpioe_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOE,
	.flags	= 0,
};

static const struct resource *gpioe_resources[] = {
	&gpioe_addr,
	&gpioe_clk,
	&gpioe_reset,
};

static struct device gpioe_device __ccm = {
	.name	= "gpioe",
	.status	= false,
	.resources = gpioe_resources,
	.num_resources = ARRAY_SIZE(gpioe_resources),
	.platform_data = NULL,
};

static const struct resource gpiod_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 3,
};

static const struct resource gpiod_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 3,
};

static const struct resource gpiod_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOD,
	.flags	= 0,
};

static const struct resource *gpiod_resources[] = {
	&gpiod_addr,
	&gpiod_clk,
	&gpiod_reset,
};

static struct device gpiod_device __ccm = {
	.name	= "gpiod",
	.status	= false,
	.resources = gpiod_resources,
	.num_resources = ARRAY_SIZE(gpiod_resources),
	.platform_data = NULL,
};

static const struct resource gpioc_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 2,
};

static const struct resource gpioc_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 2,
};

static const struct resource gpioc_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOC,
	.flags	= 0,
};

static const struct resource *gpioc_resources[] = {
	&gpioc_addr,
	&gpioc_clk,
	&gpioc_reset,
};

static const struct gpio_pinconf gpioc_pc12_conf = {
	.pin		= 12,
	.mode		= GPIO_MODE_OUTPUT,
};

static const struct gpio_pinconf *gpioc_pinconf[] = {
	&gpioc_pc12_conf,
};

static const struct gpio_platform_data gpioc_platform_data = {
	.pinconf	= gpioc_pinconf,
	.num_pins	= ARRAY_SIZE(gpioc_pinconf),
};

static struct device gpioc_device __ccm = {
	.name	= "gpioc",
	.status	= true,
	.resources = gpioc_resources,
	.num_resources = ARRAY_SIZE(gpioc_resources),
	.platform_data = &gpioc_platform_data,
};

static const struct resource gpiob_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 1,
};

static const struct resource gpiob_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 1,
};

static const struct resource gpiob_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOB,
	.flags	= 0,
};

static const struct resource *gpiob_resources[] = {
	&gpiob_addr,
	&gpiob_clk,
	&gpiob_reset,
};

static struct device gpiob_device __ccm = {
	.name	= "gpiob",
	.status	= false,
	.resources = gpiob_resources,
	.num_resources = ARRAY_SIZE(gpiob_resources),
	.platform_data = NULL,
};

static const struct resource gpioa_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x30,
	.flags	= 0,
};

static const struct resource gpioa_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x10,
	.flags	= 0,
};

static const struct resource gpioa_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_GPIOA,
	.flags	= 0,
};

static const struct resource gpioa_irq = {
	.type	= RESOURCE_TYPE_IRQ,
	.start	= 6,
	.flags	= IRQ_TRIGGER_TYPE_EDGE_FALLING,
};

static const struct resource *gpioa_resources[] = {
	&gpioa_addr,
	&gpioa_clk,
	&gpioa_reset,
	&gpioa_irq,
};

static const struct gpio_pinconf gpioa_pa0_conf = {
	.pin		= 0,
	.mode		= GPIO_MODE_INPUT,
	.speed		= GPIO_SPEED_VERY_HIGH,
};

static const struct gpio_pinconf gpioa_pa1_conf = {
	.pin		= 1,
	.mode		= GPIO_MODE_OUTPUT,
	.speed		= GPIO_SPEED_VERY_HIGH,
};

static const struct gpio_pinconf gpioa_pa9_conf = {
	.pin		= 9,
	.mode		= GPIO_MODE_AF,
	.function	= GPIO_FUNCTION(7),
};

static const struct gpio_pinconf gpioa_pa10_conf = {
	.pin		= 10,
	.mode		= GPIO_MODE_AF,
	.function	= GPIO_FUNCTION(7),
};

static const struct gpio_pinconf *gpioa_pinconf[] = {
	&gpioa_pa0_conf,
	&gpioa_pa1_conf,
	&gpioa_pa9_conf,
	&gpioa_pa10_conf,
};

static const struct gpio_platform_data gpioa_platform_data = {
	.pinconf	= gpioa_pinconf,
	.num_pins	= ARRAY_SIZE(gpioa_pinconf),
};

static struct device gpioa_device __ccm = {
	.name	= "gpioa",
	.status	= true,
	.resources = gpioa_resources,
	.num_resources = ARRAY_SIZE(gpioa_resources),
	.platform_data = &gpioa_platform_data,
};

static const struct resource bkpsram_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_BKPSRAM,
	.flags	= 0,
};

static const struct resource *bkpsram_resources[] = {
	&bkpsram_addr,
};

static struct device bkpsram_device __ccm = {
	.name	= "bkpsram",
	.status	= false,
	.resources = bkpsram_resources,
	.num_resources = ARRAY_SIZE(bkpsram_resources),
	.platform_data = NULL,
};

static const struct resource flash_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_FLASH,
	.flags	= 0,
};

static const struct resource *flash_resources[] = {
	&flash_addr,
};

static struct device flash_device __ccm = {
	.name	= "flash",
	.status	= true,
	.resources = flash_resources,
	.num_resources = ARRAY_SIZE(flash_resources),
	.platform_data = NULL,
};

static const struct resource rcc_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB1_RCC,
	.flags	= 0,
};

static const struct resource *rcc_resources[] = {
	&rcc_addr,
};

static struct device rcc_device __ccm = {
	.name	= "rcc",
	.status	= true,
	.resources = rcc_resources,
	.num_resources = ARRAY_SIZE(rcc_resources),
	.platform_data = NULL,
};

/* AHB2 */
static const struct resource dcmi_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x34,
	.flags	= 0,
};

static const struct resource dcmi_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x14,
	.flags	= 0,
};

static const struct resource dcmi_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB2_DCMI,
	.flags	= 0,
};

static const struct resource *dcmi_resources[] = {
	&dcmi_addr,
	&dcmi_clk,
	&dcmi_reset,
};

static struct device dcmi_device __ccm = {
	.name	= "dcmi",
	.status	= false,
	.resources = dcmi_resources,
	.num_resources = ARRAY_SIZE(dcmi_resources),
	.platform_data = NULL,
};

static const struct resource rng_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x34,
	.flags	= 6,
};

static const struct resource rng_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x14,
	.flags	= 6,
};

static const struct resource rng_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB2_RNG,
	.flags	= 0,
};

static const struct resource *rng_resources[] = {
	&rng_addr,
	&rng_clk,
	&rng_reset,
};

static struct device rng_device __ccm = {
	.name	= "rng",
	.status	= false,
	.resources = rng_resources,
	.num_resources = ARRAY_SIZE(rng_resources),
	.platform_data = NULL,
};

static const struct resource usb_otg_fs_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x34,
	.flags	= 7,
};

static const struct resource usb_otg_fs_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x14,
	.flags	= 7,
};

static const struct resource usb_otg_fs_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB2_USB_OTG_FS,
	.flags	= 0,
};

static const struct resource *usb_otg_fs_resources[] = {
	&usb_otg_fs_addr,
	&usb_otg_fs_clk,
	&usb_otg_fs_reset,
};

static struct device usb_otg_fs_device __ccm = {
	.name	= "usb_otg_fs",
	.status	= false,
	.resources = usb_otg_fs_resources,
	.num_resources = ARRAY_SIZE(usb_otg_fs_resources),
	.platform_data = NULL,
};

/* AHB3 */
static const struct resource fsmc_clk = {
	.type	= RESOURCE_TYPE_CLK,
	.start	= 0x38,
	.flags	= 0,
};

static const struct resource fsmc_reset = {
	.type	= RESOURCE_TYPE_RESET,
	.start	= 0x18,
	.flags	= 0,
};

static const struct resource fsmc_addr = {
	.type	= RESOURCE_TYPE_IO_MEM,
	.start	= AHB3_FSMC_CTRL,
	.flags	= 0,
};

static const struct resource *fsmc_resources[] = {
	&fsmc_addr,
	&fsmc_clk,
	&fsmc_reset,
};

static struct device fsmc_device __ccm = {
	.name	= "fsmc",
	.status	= false,
	.resources = fsmc_resources,
	.num_resources = ARRAY_SIZE(fsmc_resources),
	.platform_data = NULL,
};

static struct device *devices[] __used __ccm = {
	/* APB1 */
	&timer2_device,
	&timer3_device,
	&timer4_device,
	&timer5_device,
	&timer6_device,
	&timer7_device,
	&timer12_device,
	&timer13_device,
	&timer14_device,
	&rtc_device,
	&wwdg_device,
	&iwdg_device,
	&i2s2ext_device,
	&spi2_device,
	&spi3_device,
	&i2s3ext_device,
	&usart2_device,
	&usart3_device,
	&uart4_device,
	&uart5_device,
	&i2c1_device,
	&i2c2_device,
	&i2c3_device,
	&can1_device,
	&can2_device,
	&pwr_device,
	&dac_device,
	&uart7_device,
	&uart8_device,

	/* APB2 */
	&timer1_device,
	&timer8_device,
	&usart1_device,
	&usart6_device,
	&adc_device,
	&sdio_device,
	&spi1_device,
	&syscfg_device,
	&exti_device,
	&timer9_device,
	&timer10_device,
	&timer11_device,

	/* AHB1 */
	&usb_otg_hs_device,
	&ethernet_mac_device,
	&dma2_device,
	&dma1_device,
	&bkpsram_device,
	&flash_device,
	&rcc_device,
	&crc_device,

	&gpioa_device,
	&gpiob_device,
	&gpioc_device,
	&gpiod_device,
	&gpioe_device,
	&gpiof_device,
	&gpiog_device,
	&gpioh_device,
	&gpioi_device,

	/* AHB2 */
	&dcmi_device,
	&rng_device,
	&usb_otg_fs_device,

	/* AHB3 */
	&fsmc_device,
};

void machine_init_devices(void)
{
	register_devices(devices, ARRAY_SIZE(devices));
}
