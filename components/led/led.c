#include "led.h"
#include "sdkconfig.h"

static void blink(struct led* me)
{
	while (1) {
		led_toggle(me);
		vTaskDelay(me->delay);
	}
}

struct led* led_create(gpio_num_t gpio, bool state, TickType_t delay)
{
	struct led* ret = malloc(sizeof(struct led));
	if (!led_init(ret, gpio, state, delay)) {
		led_destroy(ret);
		ret = NULL;
	}
	return ret;
}

void led_destroy(struct led* me)
{
	led_cleanup(me);
	free(me);
}

bool led_init(struct led* me, gpio_num_t gpio, bool state, TickType_t delay)
{
	bool ret = false;
	if (me) {
		// Init members:
		me->gpio = gpio;
		me->state = state;
		me->delay = delay;

		// Init HW:
		gpio_pad_select_gpio(me->gpio);
		gpio_set_level(me->gpio, me->state);
		gpio_set_direction(me->gpio, GPIO_MODE_OUTPUT);

		// Create blink task:
		ret = (xTaskCreate((TaskFunction_t)blink, "blink", configMINIMAL_STACK_SIZE + 128, me, 5, &me->task) == pdPASS);
	}
	return ret;
}

void led_cleanup(struct led* me)
{
	if (me) {
		vTaskDelete(me->task);
		gpio_set_level(me->gpio, 0);
	}
}

void led_toggle(struct led* me)
{
	if (me) {
		me->state = !me->state;
		gpio_set_level(me->gpio, me->state);
	}
}

