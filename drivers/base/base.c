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

#define DECLARE_DEVICE(b, n)	\
{				\
	.base	= (b),		\
	.name	= (n),		\
}

static LIST_HEAD(drivers_list);

static struct device devices[] __ccm = {
	DECLARE_DEVICE(APB1_TIM2, "timer2"),
	DECLARE_DEVICE(APB1_TIM3, "timer3"),
	DECLARE_DEVICE(APB1_TIM4, "timer4"),
	DECLARE_DEVICE(APB1_TIM5, "timer5"),
	DECLARE_DEVICE(APB1_TIM6, "timer6"),
	DECLARE_DEVICE(APB1_TIM7, "timer7"),
	DECLARE_DEVICE(APB1_TIM12, "timer12"),
	DECLARE_DEVICE(APB1_TIM13, "timer13"),
	DECLARE_DEVICE(APB1_TIM14, "timer14"),
	DECLARE_DEVICE(APB1_RTC, "rtc"),
	DECLARE_DEVICE(APB1_WWDG, "wwdg"),
	DECLARE_DEVICE(APB1_IWDG, "iwdg"),
	DECLARE_DEVICE(APB1_I2S2EXT, "i2s2ext"),
	DECLARE_DEVICE(APB1_SPI2_I2S2, "spi2_i2s2"),
	DECLARE_DEVICE(APB1_SPI3_I2S3, "spi3_i2s3"),
	DECLARE_DEVICE(APB1_I2S3EXT, "i2s3ext"),
	DECLARE_DEVICE(APB1_USART2, "usart2"),
	DECLARE_DEVICE(APB1_USART3, "usart3"),
	DECLARE_DEVICE(APB1_UART4, "uart4"),
	DECLARE_DEVICE(APB1_UART5, "uart5"),
	DECLARE_DEVICE(APB1_I2C1, "i2c1"),
	DECLARE_DEVICE(APB1_I2C2, "i2c2"),
	DECLARE_DEVICE(APB1_I2C3, "i2c3"),
	DECLARE_DEVICE(APB1_CAN1, "can1"),
	DECLARE_DEVICE(APB1_CAN2, "can2"),
	DECLARE_DEVICE(APB1_PWR, "pwr"),
	DECLARE_DEVICE(APB1_DAC, "dac"),

	DECLARE_DEVICE(APB2_TIM1, "tim1"),
	DECLARE_DEVICE(APB2_TIM8, "tim8"),
	DECLARE_DEVICE(APB2_USART1, "usart1"),
	DECLARE_DEVICE(APB2_USART6, "usart6"),
	DECLARE_DEVICE(APB2_ADC1_ADC2_ADC3, "adc1_adc2_adc3"),
	DECLARE_DEVICE(APB2_SDIO, "sdio"),
	DECLARE_DEVICE(APB2_SPI1, "spi1"),
	DECLARE_DEVICE(APB2_SYSCFG, "syscfg"),
	DECLARE_DEVICE(APB2_EXTI, "exti"),
	DECLARE_DEVICE(APB2_TIM9, "tim9"),
	DECLARE_DEVICE(APB2_TIM10, "tim10"),
	DECLARE_DEVICE(APB2_TIM11, "tim11"),

	DECLARE_DEVICE(AHB1_USB_OTG_HS, "usb_otg_hs"),
	DECLARE_DEVICE(AHB1_ETHERNET_MAC, "ethernet_mac"),
	DECLARE_DEVICE(AHB1_DMA2, "dma2"),
	DECLARE_DEVICE(AHB1_DMA1, "dma1"),
	DECLARE_DEVICE(AHB1_BKPSRAM, "bkpsram"),
	DECLARE_DEVICE(AHB1_FLASH, "flash"),
	DECLARE_DEVICE(AHB1_RCC, "rcc"),
	DECLARE_DEVICE(AHB1_CRC, "crc"),
	DECLARE_DEVICE(AHB1_GPIOI, "gpioi"),
	DECLARE_DEVICE(AHB1_GPIOH, "gpioh"),
	DECLARE_DEVICE(AHB1_GPIOG, "gpiog"),
	DECLARE_DEVICE(AHB1_GPIOF, "gpiof"),
	DECLARE_DEVICE(AHB1_GPIOE, "gpioe"),
	DECLARE_DEVICE(AHB1_GPIOD, "gpiod"),
	DECLARE_DEVICE(AHB1_GPIOC, "gpioc"),
	DECLARE_DEVICE(AHB1_GPIOB, "gpiob"),
	DECLARE_DEVICE(AHB1_GPIOA, "gpioa"),

	DECLARE_DEVICE(AHB2_DCMI, "dcmi"),
	DECLARE_DEVICE(AHB2_RNG, "rng"),

	DECLARE_DEVICE(AHB3_FSMC_BANK1, "fsmc_bank1"),
	DECLARE_DEVICE(AHB3_FSMC_BANK2, "fsmc_bank2"),
	DECLARE_DEVICE(AHB3_FSMC_BANK3, "fsmc_bank3"),
	DECLARE_DEVICE(AHB3_FSMC_BANK4, "fsmc_bank4"),
	DECLARE_DEVICE(AHB3_FSMC_CTRL, "fsmc_ctrl"),
};

int register_driver(struct driver *drv)
{
	list_add_tail(&drv->list, &drivers_list);
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
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(devices); i++) {
		struct device *dev = &devices[i];
		struct driver *drv;

		list_for_each_entry(drv, &drivers_list, list) {
			if (!driver_match(dev, drv))
				continue;

			ret = driver_probe(dev, drv);
			if (ret < 0) {
				printf("%s: initialization error --> %d\n",
						dev->name, ret);
				continue;
			}
		}
	}

	return 0;
}
