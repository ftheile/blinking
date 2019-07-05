#ifndef _LED_H_
#define _LED_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_ON   false
#define LED_OFF  true

/** A class for an LED.
 */
struct led {
	gpio_num_t gpio;    //!< GPIO no. of the LED
	bool state;         //!< Initial state / current state of LED
	TickType_t delay;   //!< Blink delay
	TaskHandle_t task;  //!< Handle to control the blink task
};

#ifdef CONFIG_LED_DYNAMIC_INSTANCE
/** Dynamic LED creation.
 * \param gpio GPIO no.
 * \param state Initial state of LED
 * \param delay Blink delay
 * \return The created LED instance or NULL on failure.
 */
struct led* led_create(gpio_num_t gpio, bool state, TickType_t delay);

/** Dynamic LED destruction.
 * \param me The LED instance.
 */
void led_destroy(struct led* me);
#endif

/** Static LED initialization.
 * \param me The LED instance
 * \param gpio GPIO no.
 * \param state Initial state of LED
 * \param delay Blink delay
 * \return true on success, false on failure
 */
bool led_init(struct led* me, gpio_num_t gpio, bool state, TickType_t delay);

/** Static LED cleanup.
 * \param me The LED instance
 */
void led_cleanup(struct led* me);

/** Toggle LED state.
 * \param me The LED instance
 */
void led_toggle(struct led* me);

/** Turn LED on.
 * \param me The LED instance
 */
void led_on(struct led* me);

/** Turn LED off.
 * \param me The LED instance
 */
void led_off(struct led* me);

/** Turn LED on or off.
 * \param me The LED instance
 * \param state Desired LED state
 */
void led_set(struct led* me, bool state);

/** Start flashing the LED.
 * \param me The LED instance
 */
void led_flash(struct led* me);

#endif

