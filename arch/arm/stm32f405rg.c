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
#include <m4naos/kernel.h>
#include <m4naos/reset.h>

#define str(n)		#n

#define DECLARE_CLK(n, o, b)		\
struct clk n##_clk __ccm  = {		\
	.offset	= o,			\
	.bit	= b,			\
}

#define DECLARE_RESET(n, o, b)		\
struct reset n##_reset __ccm  = {	\
	.offset	= o,			\
	.bit	= b,			\
}

#define DECLARE_DEVICE(b, n, r, c, s, p)\
struct device n##_device __ccm = {	\
	.base	= (b),			\
	.name	= str(n),		\
	.reset	= (r),			\
	.clk	= (c),			\
	.status	= (s),			\
	.platform_data = (p),		\
}

/* APB1 */
static DECLARE_CLK(timer2, 0x40, 0);
static DECLARE_CLK(timer3, 0x40, 1);
static DECLARE_CLK(timer4, 0x40, 2);
static DECLARE_CLK(timer5, 0x40, 3);
static DECLARE_CLK(timer6, 0x40, 4);
static DECLARE_CLK(timer7, 0x40, 5);
static DECLARE_CLK(timer12, 0x40, 6);
static DECLARE_CLK(timer13, 0x40, 7);
static DECLARE_CLK(timer14, 0x40, 8);
static DECLARE_CLK(wwdg, 0x40, 11);
static DECLARE_CLK(spi2, 0x40, 14);
static DECLARE_CLK(spi3, 0x40, 15);
static DECLARE_CLK(uart2, 0x40, 17);
static DECLARE_CLK(uart3, 0x40, 18);
static DECLARE_CLK(uart4, 0x40, 19);
static DECLARE_CLK(uart5, 0x40, 20);
static DECLARE_CLK(i2c1, 0x40, 21);
static DECLARE_CLK(i2c2, 0x40, 22);
static DECLARE_CLK(i2c3, 0x40, 23);
static DECLARE_CLK(can1, 0x40, 25);
static DECLARE_CLK(can2, 0x40, 26);
static DECLARE_CLK(pwr, 0x40, 28);
static DECLARE_CLK(dac, 0x40, 29);
static DECLARE_CLK(uart7, 0x40, 30);
static DECLARE_CLK(uart8, 0x40, 31);

static DECLARE_RESET(timer2, 0x20, 0);
static DECLARE_RESET(timer3, 0x20, 1);
static DECLARE_RESET(timer4, 0x20, 2);
static DECLARE_RESET(timer5, 0x20, 3);
static DECLARE_RESET(timer6, 0x20, 4);
static DECLARE_RESET(timer7, 0x20, 5);
static DECLARE_RESET(timer12, 0x20, 6);
static DECLARE_RESET(timer13, 0x20, 7);
static DECLARE_RESET(timer14, 0x20, 8);
static DECLARE_RESET(wwdg, 0x20, 11);
static DECLARE_RESET(spi2, 0x20, 14);
static DECLARE_RESET(spi3, 0x20, 15);
static DECLARE_RESET(uart2, 0x20, 17);
static DECLARE_RESET(uart3, 0x20, 18);
static DECLARE_RESET(uart4, 0x20, 19);
static DECLARE_RESET(uart5, 0x20, 20);
static DECLARE_RESET(i2c1, 0x20, 21);
static DECLARE_RESET(i2c2, 0x20, 22);
static DECLARE_RESET(i2c3, 0x20, 23);
static DECLARE_RESET(can1, 0x20, 25);
static DECLARE_RESET(can2, 0x20, 26);
static DECLARE_RESET(pwr, 0x20, 28);
static DECLARE_RESET(dac, 0x20, 29);
static DECLARE_RESET(uart7, 0x20, 30);
static DECLARE_RESET(uart8, 0x20, 31);

static DECLARE_DEVICE(APB1_TIM2, timer2, &timer2_reset, &timer2_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM3, timer3, &timer3_reset, &timer3_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM4, timer4, &timer4_reset, &timer4_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM5, timer5, &timer5_reset, &timer5_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM6, timer6, &timer6_reset, &timer6_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM7, timer7, &timer7_reset, &timer7_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM12, timer12, &timer12_reset, &timer12_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM13, timer13, &timer13_reset, &timer13_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_TIM14, timer14, &timer14_reset, &timer14_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_RTC, rtc, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(APB1_WWDG, wwdg, &wwdg_reset, &wwdg_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_IWDG, iwdg, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(APB1_I2S2EXT, i2s2ext, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(APB1_SPI2_I2S2, spi2, &spi2_reset, &spi2_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_SPI3_I2S3, spi3, &spi3_reset, &spi3_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_I2S3EXT, i2s3ext, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(APB1_USART2, usart2, &uart2_reset, &uart2_clk,
		false, NULL);
static DECLARE_DEVICE(APB1_USART3, usart3, &uart3_reset, &uart3_clk,
		false, NULL);
static DECLARE_DEVICE(APB1_UART4, uart4, &uart4_reset, &uart4_clk,
		false, NULL);
static DECLARE_DEVICE(APB1_UART5, uart5, &uart5_reset, &uart5_clk,
		false, NULL);
static DECLARE_DEVICE(APB1_I2C1, i2c1, &i2c1_reset, &i2c1_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_I2C2, i2c2, &i2c2_reset, &i2c2_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_I2C3, i2c3, &i2c3_reset, &i2c3_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_CAN1, can1, &can1_reset, &can1_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_CAN2, can2, &can2_reset, &can2_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_PWR, pwr, &pwr_reset, &pwr_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_DAC, dac, &dac_reset, &dac_clk,
		true, NULL);
static DECLARE_DEVICE(APB1_UART7, uart7, &uart7_reset, &uart7_clk,
		false, NULL);
static DECLARE_DEVICE(APB1_UART8, uart8, &uart8_reset, &uart8_clk,
		false, NULL);

/* APB2 */
static DECLARE_CLK(timer1, 0x44, 0);
static DECLARE_CLK(timer8, 0x44, 1);
static DECLARE_CLK(usart1, 0x44, 4);
static DECLARE_CLK(usart6, 0x44, 5);
static DECLARE_CLK(adc, 0x44, 8);
static DECLARE_CLK(sdio, 0x44, 11);
static DECLARE_CLK(spi1, 0x44, 12);
static DECLARE_CLK(syscfg, 0x44, 14);
static DECLARE_CLK(timer9, 0x44, 16);
static DECLARE_CLK(timer10, 0x44, 17);
static DECLARE_CLK(timer11, 0x44, 18);

static DECLARE_RESET(timer1, 0x24, 0);
static DECLARE_RESET(timer8, 0x24, 1);
static DECLARE_RESET(usart1, 0x24, 4);
static DECLARE_RESET(usart6, 0x24, 5);
static DECLARE_RESET(adc, 0x24, 8);
static DECLARE_RESET(sdio, 0x24, 11);
static DECLARE_RESET(spi1, 0x24, 12);
static DECLARE_RESET(syscfg, 0x24, 14);
static DECLARE_RESET(timer9, 0x24, 16);
static DECLARE_RESET(timer10, 0x24, 17);
static DECLARE_RESET(timer11, 0x24, 18);

static DECLARE_DEVICE(APB2_TIM1, timer1, &timer1_reset, &timer1_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_TIM8, timer8, &timer8_reset, &timer8_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_USART1, usart1, &usart1_reset, &usart1_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_USART6, usart6, &usart6_reset, &usart6_clk,
		false, NULL);
static DECLARE_DEVICE(APB2_ADC1_ADC2_ADC3, adc, &adc_reset, &adc_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_SDIO, sdio, &sdio_reset, &sdio_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_SPI1, spi1, &spi1_reset, &spi1_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_SYSCFG, syscfg, &syscfg_reset, &syscfg_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_EXTI, exti, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(APB2_TIM9, timer9, &timer9_reset, &timer9_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_TIM10, timer10, &timer10_reset, &timer10_clk,
		true, NULL);
static DECLARE_DEVICE(APB2_TIM11, timer11, &timer11_reset, &timer11_clk,
		true, NULL);

/* AHB1 */
static DECLARE_CLK(usb_otg_hs, 0x30, 29);
static DECLARE_CLK(ethernet_mac, 0x30, 25);
static DECLARE_CLK(dma2, 0x30, 22);
static DECLARE_CLK(dma1, 0x30, 21);
static DECLARE_CLK(crc, 0x30, 12);
static DECLARE_CLK(gpioi, 0x30, 8);
static DECLARE_CLK(gpioh, 0x30, 7);
static DECLARE_CLK(gpiog, 0x30, 6);
static DECLARE_CLK(gpiof, 0x30, 5);
static DECLARE_CLK(gpioe, 0x30, 4);
static DECLARE_CLK(gpiod, 0x30, 3);
static DECLARE_CLK(gpioc, 0x30, 2);
static DECLARE_CLK(gpiob, 0x30, 1);
static DECLARE_CLK(gpioa, 0x30, 0);

static DECLARE_RESET(usb_otg_hs, 0x10, 29);
static DECLARE_RESET(ethernet_mac, 0x10, 25);
static DECLARE_RESET(dma2, 0x10, 22);
static DECLARE_RESET(dma1, 0x10, 21);
static DECLARE_RESET(crc, 0x10, 12);
static DECLARE_RESET(gpioi, 0x10, 8);
static DECLARE_RESET(gpioh, 0x10, 7);
static DECLARE_RESET(gpiog, 0x10, 6);
static DECLARE_RESET(gpiof, 0x10, 5);
static DECLARE_RESET(gpioe, 0x10, 4);
static DECLARE_RESET(gpiod, 0x10, 3);
static DECLARE_RESET(gpioc, 0x10, 2);
static DECLARE_RESET(gpiob, 0x10, 1);
static DECLARE_RESET(gpioa, 0x10, 0);

static DECLARE_DEVICE(AHB1_USB_OTG_HS, usb_otg_hs, &usb_otg_hs_reset,
		&usb_otg_hs_clk, true, NULL);
static DECLARE_DEVICE(AHB1_ETHERNET_MAC, ethernet_mac, &ethernet_mac_reset,
		&ethernet_mac_clk, true, NULL);
static DECLARE_DEVICE(AHB1_DMA2, dma2, &dma2_reset, &dma2_clk,
		true, NULL);
static DECLARE_DEVICE(AHB1_DMA1, dma1, &dma1_reset, &dma1_clk,
		true, NULL);
static DECLARE_DEVICE(AHB1_BKPSRAM, bkpsram, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(AHB1_FLASH, flash, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(AHB1_RCC, rcc, NULL, NULL,
		true, NULL);
static DECLARE_DEVICE(AHB1_CRC, crc, &crc_reset, &crc_clk,
		true, NULL);
static DECLARE_DEVICE(AHB1_GPIOI, gpioi, &gpioi_reset, &gpioi_clk,
		false, NULL);
static DECLARE_DEVICE(AHB1_GPIOH, gpioh, &gpioh_reset, &gpioh_clk,
		false, NULL);
static DECLARE_DEVICE(AHB1_GPIOG, gpiog, &gpiog_reset, &gpiog_clk,
		false, NULL);
static DECLARE_DEVICE(AHB1_GPIOF, gpiof, &gpiof_reset, &gpiof_clk,
		false, NULL);
static DECLARE_DEVICE(AHB1_GPIOE, gpioe, &gpioe_reset, &gpioe_clk,
		false, NULL);
static DECLARE_DEVICE(AHB1_GPIOD, gpiod, &gpiod_reset, &gpiod_clk,
		false, NULL);
static DECLARE_DEVICE(AHB1_GPIOC, gpioc, &gpioc_reset, &gpioc_clk,
		true, NULL);
static DECLARE_DEVICE(AHB1_GPIOB, gpiob, &gpiob_reset, &gpiob_clk,
		false, NULL);

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
	&gpioa_pa9_conf,
	&gpioa_pa10_conf,
};

static const struct gpio_platform_data gpioa_platform_data = {
	.pinconf	= gpioa_pinconf,
	.num_pins	= 2,
};

static DECLARE_DEVICE(AHB1_GPIOA, gpioa, &gpioa_reset, &gpioa_clk,
		true, &gpioa_platform_data);

/* AHB2 */
static DECLARE_CLK(dcmi, 0x34, 0);
static DECLARE_CLK(rng, 0x34, 6);
static DECLARE_CLK(usb_otg_fs, 0x34, 7);

static DECLARE_RESET(dcmi, 0x14, 0);
static DECLARE_RESET(rng, 0x14, 6);
static DECLARE_RESET(usb_otg_fs, 0x14, 7);

static DECLARE_DEVICE(AHB2_DCMI, dcmi, &dcmi_reset, &dcmi_clk,
		true, NULL);
static DECLARE_DEVICE(AHB2_RNG, rng, &rng_reset, &rng_clk,
		true, NULL);
static DECLARE_DEVICE(AHB2_USB_OTG_FS, usb_otg_fs, &usb_otg_fs_reset,
		&usb_otg_fs_clk,
		true, NULL);

/* AHB3 */
static DECLARE_CLK(fsmc, 0x38, 0);

static DECLARE_RESET(fsmc, 0x18, 0);

static DECLARE_DEVICE(AHB3_FSMC_CTRL, fsmc, &fsmc_reset, &fsmc_clk,
		true, NULL);

static struct device *devices[] __ccm __used = {
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
	&gpioi_device,
	&gpioh_device,
	&gpiog_device,
	&gpiof_device,
	&gpioe_device,
	&gpiod_device,
	&gpioc_device,
	&gpiob_device,
	&gpioa_device,

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
