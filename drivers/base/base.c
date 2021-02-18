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

#define str(n)		#n

#define DECLARE_DEVICE(b, n)		\
struct device n##_device __ccm = {	\
	.base	= (b),			\
	.name	= str(n),		\
}

static LIST_HEAD(drivers_list);

static DECLARE_DEVICE(APB1_TIM2, timer2);
static DECLARE_DEVICE(APB1_TIM3, timer3);
static DECLARE_DEVICE(APB1_TIM4, timer4);
static DECLARE_DEVICE(APB1_TIM5, timer5);
static DECLARE_DEVICE(APB1_TIM6, timer6);
static DECLARE_DEVICE(APB1_TIM7, timer7);
static DECLARE_DEVICE(APB1_TIM12, timer12);
static DECLARE_DEVICE(APB1_TIM13, timer13);
static DECLARE_DEVICE(APB1_TIM14, timer14);
static DECLARE_DEVICE(APB1_RTC, rtc);
static DECLARE_DEVICE(APB1_WWDG, wwdg);
static DECLARE_DEVICE(APB1_IWDG, iwdg);
static DECLARE_DEVICE(APB1_I2S2EXT, i2s2ext);
static DECLARE_DEVICE(APB1_SPI2_I2S2, spi2_i2s2);
static DECLARE_DEVICE(APB1_SPI3_I2S3, spi3_i2s3);
static DECLARE_DEVICE(APB1_I2S3EXT, i2s3ext);
static DECLARE_DEVICE(APB1_USART2, usart2);
static DECLARE_DEVICE(APB1_USART3, usart3);
static DECLARE_DEVICE(APB1_UART4, uart4);
static DECLARE_DEVICE(APB1_UART5, uart5);
static DECLARE_DEVICE(APB1_I2C1, i2c1);
static DECLARE_DEVICE(APB1_I2C2, i2c2);
static DECLARE_DEVICE(APB1_I2C3, i2c3);
static DECLARE_DEVICE(APB1_CAN1, can1);
static DECLARE_DEVICE(APB1_CAN2, can2);
static DECLARE_DEVICE(APB1_PWR, pwr);
static DECLARE_DEVICE(APB1_DAC, dac);
static DECLARE_DEVICE(APB2_TIM1, tim1);
static DECLARE_DEVICE(APB2_TIM8, tim8);
static DECLARE_DEVICE(APB2_USART1, usart1);
static DECLARE_DEVICE(APB2_USART6, usart6);
static DECLARE_DEVICE(APB2_ADC1_ADC2_ADC3, adc1_adc2_adc3);
static DECLARE_DEVICE(APB2_SDIO, sdio);
static DECLARE_DEVICE(APB2_SPI1, spi1);
static DECLARE_DEVICE(APB2_SYSCFG, syscfg);
static DECLARE_DEVICE(APB2_EXTI, exti);
static DECLARE_DEVICE(APB2_TIM9, tim9);
static DECLARE_DEVICE(APB2_TIM10, tim10);
static DECLARE_DEVICE(APB2_TIM11, tim11);
static DECLARE_DEVICE(AHB1_USB_OTG_HS, usb_otg_hs);
static DECLARE_DEVICE(AHB1_ETHERNET_MAC, ethernet_mac);
static DECLARE_DEVICE(AHB1_DMA2, dma2);
static DECLARE_DEVICE(AHB1_DMA1, dma1);
static DECLARE_DEVICE(AHB1_BKPSRAM, bkpsram);
static DECLARE_DEVICE(AHB1_FLASH, flash);
static DECLARE_DEVICE(AHB1_RCC, rcc);
static DECLARE_DEVICE(AHB1_CRC, crc);
static DECLARE_DEVICE(AHB1_GPIOI, gpioi);
static DECLARE_DEVICE(AHB1_GPIOH, gpioh);
static DECLARE_DEVICE(AHB1_GPIOG, gpiog);
static DECLARE_DEVICE(AHB1_GPIOF, gpiof);
static DECLARE_DEVICE(AHB1_GPIOE, gpioe);
static DECLARE_DEVICE(AHB1_GPIOD, gpiod);
static DECLARE_DEVICE(AHB1_GPIOC, gpioc);
static DECLARE_DEVICE(AHB1_GPIOB, gpiob);
static DECLARE_DEVICE(AHB1_GPIOA, gpioa);
static DECLARE_DEVICE(AHB2_DCMI, dcmi);
static DECLARE_DEVICE(AHB2_RNG, rng);
static DECLARE_DEVICE(AHB3_FSMC_BANK1, fsmc_bank1);
static DECLARE_DEVICE(AHB3_FSMC_BANK2, fsmc_bank2);
static DECLARE_DEVICE(AHB3_FSMC_BANK3, fsmc_bank3);
static DECLARE_DEVICE(AHB3_FSMC_BANK4, fsmc_bank4);
static DECLARE_DEVICE(AHB3_FSMC_CTRL, fsmc_ctrl);

static struct device *devices[] __ccm = {
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
	&spi2_i2s2_device,
	&spi3_i2s3_device,
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
	&tim1_device,
	&tim8_device,
	&usart1_device,
	&usart6_device,
	&adc1_adc2_adc3_device,
	&sdio_device,
	&spi1_device,
	&syscfg_device,
	&exti_device,
	&tim9_device,
	&tim10_device,
	&tim11_device,
	&usb_otg_hs_device,
	&ethernet_mac_device,
	&dma2_device,
	&dma1_device,
	&bkpsram_device,
	&flash_device,
	&rcc_device,
	&crc_device,
	&gpioi_device,
	&gpioh_device,
	&gpiog_device,
	&gpiof_device,
	&gpioe_device,
	&gpiod_device,
	&gpioc_device,
	&gpiob_device,
	&gpioa_device,
	&dcmi_device,
	&rng_device,
	&fsmc_bank1_device,
	&fsmc_bank2_device,
	&fsmc_bank3_device,
	&fsmc_bank4_device,
	&fsmc_ctrl_device,
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
		struct device *dev = devices[i];
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
