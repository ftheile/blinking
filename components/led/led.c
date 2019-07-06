#include "led.h"

#define TIMER_BLOCK_TIME (100 / portTICK_PERIOD_MS)

static void blink(TimerHandle_t timer)
{
	struct led* me = pvTimerGetTimerID(timer);
	me->state = !me->state;
	gpio_set_level(me->gpio, me->state);
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

		// Create blink timer:
		me->timer = xTimerCreate("blink", delay, pdTRUE, me, blink);
		ret = (me->timer != NULL);
	}
	return ret;
}

void led_cleanup(struct led* me)
{
	if (me) {
		xTimerStop(me->timer, TIMER_BLOCK_TIME);
		xTimerDelete(me->timer, TIMER_BLOCK_TIME);
		gpio_set_level(me->gpio, LED_OFF);
	}
}

bool led_toggle(struct led* me)
{
	bool ret = false;
	if (me) {
		ret = (xTimerStop(me->timer, TIMER_BLOCK_TIME) == pdTRUE);
		me->state = !me->state;
		gpio_set_level(me->gpio, me->state);
	}
	return ret;
}

bool led_on(struct led* me)
{
	bool ret = false;
	if (me) {
		ret = (xTimerStop(me->timer, TIMER_BLOCK_TIME) == pdTRUE);
		me->state = LED_ON;
		gpio_set_level(me->gpio, me->state);
	}
	return ret;
}

bool led_off(struct led* me)
{
	bool ret = false;
	if (me) {
		ret = (xTimerStop(me->timer, TIMER_BLOCK_TIME) == pdTRUE);
		me->state = LED_OFF;
		gpio_set_level(me->gpio, me->state);
	}
	return ret;
}

bool led_set(struct led* me, bool state)
{
	bool ret = false;
	if (me) {
		ret = (xTimerStop(me->timer, TIMER_BLOCK_TIME) == pdTRUE);
		me->state = state;
		gpio_set_level(me->gpio, me->state);
	}
	return ret;
}

bool led_flash(struct led* me)
{
	bool ret = false;
	if (me) {
		ret = (xTimerStart(me->timer, TIMER_BLOCK_TIME) == pdTRUE);
	}
	return ret;
}

