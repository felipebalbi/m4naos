#include <errno.h>
#include <m4naos/driver.h>
#include <m4naos/gpio.h>
#include <m4naos/list.h>

static LIST_HEAD(gpio_chips_list);
static int gpio_num_base;

int gpio_register(struct gpio_chip *chip)
{
	chip->base = gpio_num_base;
	gpio_num_base += chip->ngpio;

	list_add_tail(&chip->list, &gpio_chips_list);

	return 0;
}

int gpio_request(int gpio)
{
	struct gpio_chip *chip = NULL;

	list_for_each_entry(chip, &gpio_chips_list, list) {
		if (gpio < chip->base || gpio > chip->base + chip->ngpio)
			continue;

		return chip->ops->request(chip, gpio - chip->base);
	}

	return -ENODEV;
}

void gpio_release(int gpio)
{
	struct gpio_chip *chip = NULL;

	list_for_each_entry(chip, &gpio_chips_list, list) {
		if (gpio < chip->base || gpio > chip->base + chip->ngpio)
			continue;

		chip->ops->release(chip, gpio - chip->base);
		break;
	}
}

int gpio_set_direction(int gpio, int dir)
{
	struct gpio_chip *chip = NULL;

	list_for_each_entry(chip, &gpio_chips_list, list) {
		if (gpio < chip->base || gpio > chip->base + chip->ngpio)
			continue;

		return chip->ops->set_direction(chip, gpio - chip->base, dir);
	}
}

int gpio_set_bias(int gpio, int bias)
{
	struct gpio_chip *chip = NULL;

	list_for_each_entry(chip, &gpio_chips_list, list) {
		if (gpio < chip->base || gpio > chip->base + chip->ngpio)
			continue;

		return chip->ops->set_direction(chip, gpio - chip->base, bias);
	}
}

int gpio_set_speed(int gpio, int speed)
{
	struct gpio_chip *chip = NULL;

	list_for_each_entry(chip, &gpio_chips_list, list) {
		if (gpio < chip->base || gpio > chip->base + chip->ngpio)
			continue;

		return chip->ops->set_direction(chip, gpio - chip->base, speed);
	}
}

int gpio_set_value(int gpio, int value)
{
	struct gpio_chip *chip = NULL;

	list_for_each_entry(chip, &gpio_chips_list, list) {
		if (gpio < chip->base || gpio > chip->base + chip->ngpio)
			continue;

		return chip->ops->set_value(chip, gpio - chip->base, value);
	}
}

int gpio_get_value(int gpio)
{
	struct gpio_chip *chip = NULL;

	list_for_each_entry(chip, &gpio_chips_list, list) {
		if (gpio < chip->base || gpio > chip->base + chip->ngpio)
			continue;

		chip->ops->get_value(chip, gpio - chip->base);
		break;
	}
}

int gpio_init(void)
{
	return 0;
}
subsys_init(gpio_init);
