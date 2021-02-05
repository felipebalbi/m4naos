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

#ifndef __M4NAOS_HARDWARE_H
#define __M4NAOS_HARDWARE_H

#include <m4naos/types.h>

/* Memory Map */
#define APB1_BASE		0x40000000
#define APB1_TIM2		(APB1_BASE + 0x0000)
#define APB1_TIM3		(APB1_BASE + 0x0400)
#define APB1_TIM4		(APB1_BASE + 0x0800)
#define APB1_TIM5		(APB1_BASE + 0x0c00)
#define APB1_TIM6		(APB1_BASE + 0x1000)
#define APB1_TIM7		(APB1_BASE + 0x1400)
#define APB1_TIM12		(APB1_BASE + 0x1800)
#define APB1_TIM13		(APB1_BASE + 0x1c00)
#define APB1_TIM14		(APB1_BASE + 0x2000)
#define APB1_RTC		(APB1_BASE + 0x2800)
#define APB1_WWDG		(APB1_BASE + 0x2c00)
#define APB1_IWDG		(APB1_BASE + 0x3000)
#define APB1_I2S2EXT		(APB1_BASE + 0x3400)
#define APB1_SPI2_I2S2		(APB1_BASE + 0x3800)
#define APB1_SPI3_I2S3		(APB1_BASE + 0x3c00)
#define APB1_I2S3EXT		(APB1_BASE + 0x4000)
#define APB1_USART2		(APB1_BASE + 0x4400)
#define APB1_USART3		(APB1_BASE + 0x4800)
#define APB1_UART4		(APB1_BASE + 0x4c00)
#define APB1_UART5		(APB1_BASE + 0x5000)
#define APB1_I2C1		(APB1_BASE + 0x5400)
#define APB1_I2C2		(APB1_BASE + 0x5800)
#define APB1_I2C3		(APB1_BASE + 0x5c00)
#define APB1_CAN1		(APB1_BASE + 0x6400)
#define APB1_CAN2		(APB1_BASE + 0x6800)
#define APB1_PWR		(APB1_BASE + 0x7000)
#define APB1_DAC		(APB1_BASE + 0x7400)

#define APB2_BASE		0x40010000
#define APB2_TIM1		(APB2_BASE + 0x0000)
#define APB2_TIM8		(APB2_BASE + 0x0400)
#define APB2_USART1		(APB2_BASE + 0x1000)
#define APB2_USART6		(APB2_BASE + 0x1400)
#define APB2_ADC1_ADC2_ADC3	(APB2_BASE + 0x2000)
#define APB2_SDIO		(APB2_BASE + 0x2C00)
#define APB2_SPI1		(APB2_BASE + 0x3000)
#define APB2_SYSCFG		(APB2_BASE + 0x3800)
#define APB2_EXTI		(APB2_BASE + 0x3C00)
#define APB2_TIM9		(APB2_BASE + 0x4000)
#define APB2_TIM10		(APB2_BASE + 0x4400)
#define APB2_TIM11		(APB2_BASE + 0x4800)

#define AHB1_BASE		0x40020000
#define AHB1_USB_OTG_HS		(AHB1_BASE + 0x0000)
#define AHB1_ETHERNET_MAC	(AHB1_BASE + 0x8000)
#define AHB1_DMA2		(AHB1_BASE + 0x6400)
#define AHB1_DMA1		(AHB1_BASE + 0x6000)
#define AHB1_BKPSRAM		(AHB1_BASE + 0x4000)
#define AHB1_FLASH		(AHB1_BASE + 0x3C00)
#define AHB1_RCC		(AHB1_BASE + 0x3800)
#define AHB1_CRC		(AHB1_BASE + 0x3000)
#define AHB1_GPIOI		(AHB1_BASE + 0x2000)
#define AHB1_GPIOH		(AHB1_BASE + 0x1C00)
#define AHB1_GPIOG		(AHB1_BASE + 0x1800)
#define AHB1_GPIOF		(AHB1_BASE + 0x1400)
#define AHB1_GPIOE		(AHB1_BASE + 0x1000)
#define AHB1_GPIOD		(AHB1_BASE + 0x0C00)
#define AHB1_GPIOC		(AHB1_BASE + 0x0800)
#define AHB1_GPIOB		(AHB1_BASE + 0x0400)
#define AHB1_GPIOA		(AHB1_BASE + 0x0000)

#define AHB2_BASE		0x50050000
#define AHB2_DCMI		(AHB2_BASE + 0x0000)
#define AHB2_RNG		(AHB2_BASE + 0x0800)

#define AHB3_BASE		0x60000000
#define AHB3_FSMC_BANK1		(AHB3_BASE + 0x00000000)
#define AHB3_FSMC_BANK2		(AHB3_BASE + 0x10000000)
#define AHB3_FSMC_BANK3		(AHB3_BASE + 0x20000000)
#define AHB3_FSMC_BANK4		(AHB3_BASE + 0x30000000)
#define AHB3_FSMC_CTRL		(AHB3_BASE + 0x40000000)

/* System Control Space */
#define SCS_BASE		0xe000e000

/* System Timer */
#define SYST_BASE		0xe000e010

/* Nested Vectored Interrupt Controller */
#define NVIC_BASE		0xe000e100

/* System Control Block */
#define SCB_BASE		0xe000ed00
#define SCB_CPUID		0x00
#define SCB_ICSR		0x04
#define SCB_VTOR		0x08
#define SCB_AIRCR		0x0c
#define SCB_SCR			0x10
#define SCB_CCR			0x14
#define SCB_SHPR2		0x18
#define SCB_SHPR3		0x1c

#define SCB_CPUID_REVISION(n)	((n) & 0x0f)
#define SCB_CPUID_PARTNO(n)	(((n) & 0xfff0) >> 4)
#define SCB_CPUID_ARCH(n)	(((n) & 0xf0000) >> 16)
#define SCB_CPUID_VARIANT(n)	(((n) & 0xf00000) >> 20)
#define SCB_CPUID_IMPL(n)	(((n) & 0xff000000) >> 24)

#define SCB_VTOR_TBLOFF(n)	((n) & 0xffffff00)

static inline void __wfi(void)
{
	asm("wfi");
}

static inline void __dsb(void)
{
	asm("dsb");
}

static inline void __dmb(void)
{
	asm("dmb");
}

static inline void __isb(void)
{
	asm("isb");
}

#endif /* __M4NAOS_HARDWARE_H */
