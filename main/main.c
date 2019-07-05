/* Blinking LED example.

   This example is based on the first example in Agus Kurniawan's
   book "Internet of Things Projects with ESP32".

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "led.h"  // my own component!
#include "sdkconfig.h"

// Availabled GPIOs with LEDs:
#define LED_GREEN GPIO_NUM_2
#define LED_RED   GPIO_NUM_0
#define LED_BLUE  GPIO_NUM_4

void app_main()
{
	struct led* led_green;
	struct led* led_red;
	struct led* led_blue;

	// Create dynamic LEDs
	led_green = led_create(LED_GREEN, LED_OFF,  500 / portTICK_PERIOD_MS);
	led_red   = led_create(LED_RED,   LED_OFF, 1000 / portTICK_PERIOD_MS);
	led_blue  = led_create(LED_BLUE,  LED_OFF, 2000 / portTICK_PERIOD_MS);

	// Initialize static LEDs
//	static struct led led_g;
//	static struct led led_r;
//	static struct led led_b;
//	led_green = &led_g;
//	led_red = &led_r;
//	led_blue = &led_b;
//	led_init(led_green, LED_GREEN, LED_OFF,  500 / portTICK_PERIOD_MS);
//	led_init(led_red,   LED_RED,   LED_OFF, 1000 / portTICK_PERIOD_MS);
//	led_init(led_blue,  LED_BLUE,  LED_OFF, 2000 / portTICK_PERIOD_MS);

	// Start flashing the LEDs:
	led_flash(led_green);
	led_flash(led_red);
	led_flash(led_blue);

	// Destroy dynamic LEDs:
//	led_destroy(led_green);
//	led_destroy(led_red);
//	led_destroy(led_blue);

	// Cleanup static LEDs:
//	led_cleanup(green_led);
//	led_cleanup(red_led);
//	led_cleanup(blue_led);
}

