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

#ifndef __M4NAOS_GPIO_H
#define __M4NAOS_GPIO_H

#include <m4naos/list.h>
#include <m4naos/kernel.h>

#define GPIO_MODE_INPUT			0x00
#define GPIO_MODE_OUTPUT		0x01
#define GPIO_MODE_AF			0x02
#define GPIO_MODE_ANALOG		0x03

#define GPIO_OUTPUT_TYPE_PUSH_PULL	0x00
#define GPIO_OUTPUT_TYPE_OPEN_DRAIN	0x01

#define GPIO_SPEED_LOW			0x00
#define GPIO_SPEED_MEDIUM		0x01
#define GPIO_SPEED_HIGH			0x02
#define GPIO_SPEED_VERY_HIGH		0x03

#define GPIO_PULL_NONE			0x00
#define GPIO_PULL_UP			0x01
#define GPIO_PULL_DOWN			0x02

#define GPIO_FUNCTION(n)		((n) & 0x0f)

struct gpio_chip;

struct gpio_pinconf {
	u8 pin;
	u8 mode;
	u8 type;
	u8 speed;
	u8 pull_up_down;
	u8 function;
};

struct gpio_platform_data {
	const struct gpio_pinconf **pinconf;
	int num_pins;
};

struct gpio_ops {
	int (*request)(struct gpio_chip *chip, int gpio);
	void (*release)(struct gpio_chip *chip, int gpio);
	int (*set_direction)(struct gpio_chip *chip, int gpio, int dir);
	int (*set_bias)(struct gpio_chip *chip, int gpio, int bias);
	int (*set_speed)(struct gpio_chip *chip, int gpio, int speed);
	int (*set_value)(struct gpio_chip *chip, int gpio, int value);
	int (*get_value)(struct gpio_chip *chip, int gpio);
};

struct gpio_chip {
	struct list_head list;
	const struct gpio_ops *ops;
	int ngpio;
	int base;
};

int gpio_register(struct gpio_chip *chip);
int gpio_request(int gpio);
void gpio_release(int gpio);
int gpio_set_direction(int gpio, int dir);
int gpio_set_bias(int gpio, int bias);
int gpio_set_speed(int gpio, int speed);
int gpio_set_value(int gpio, int value);
int gpio_get_value(int gpio);

#endif /* __M4NAOS_GPIO_H */
