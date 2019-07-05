#include "led.h"

static void blink(struct led* me)
{
	while (1) {
		me->state = !me->state;
		gpio_set_level(me->gpio, me->state);
		vTaskDelay(me->delay);
	}
}

#ifdef CONFIG_LED_DYNAMIC_INSTANCE
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
#endif

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
		ret = (xTaskCreate((TaskFunction_t)blink, "blink", configMINIMAL_STACK_SIZE, me, 5, &me->task) == pdPASS);
	}
	return ret;
}

void led_cleanup(struct led* me)
{
	if (me) {
		vTaskDelete(me->task);
		gpio_set_level(me->gpio, LED_OFF);
	}
}

void led_toggle(struct led* me)
{
	if (me) {
		vTaskSuspend(me->task);
		me->state = !me->state;
		gpio_set_level(me->gpio, me->state);
	}
}

void led_on(struct led* me)
{
	if (me) {
		vTaskSuspend(me->task);
		me->state = LED_ON;
		gpio_set_level(me->gpio, me->state);
	}
}

void led_off(struct led* me)
{
	if (me) {
		vTaskSuspend(me->task);
		me->state = LED_OFF;
		gpio_set_level(me->gpio, me->state);
	}
}

void led_set(struct led* me, bool state)
{
	if (me) {
		vTaskSuspend(me->task);
		me->state = state;
		gpio_set_level(me->gpio, me->state);
	}
}

void led_flash(struct led* me)
{
	if (me) {
		vTaskResume(me->task);
	}
}

