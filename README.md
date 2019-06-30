# ESP32 blinking LEDs example
This repository contains a LED *component*. The LED component creates a task to blink the LED. The application in `main/main.c` uses that LED component. See Espressif's documentation of the [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#example-project) to get an understanding of the directory structure.

The application creates three LED instances to control the RGB LED on [Espressif's WROVER kit](https://docs.espressif.com/projects/esp-idf/en/latest/hw-reference/modules-and-boards.html#esp-wrover-kit-v4-1).

The task function in the LED component is always the same (`static void blink(struct led* me)`), only the parameter passed to that function differs (context to the task function). So _the same_ task function gets instantiated three times.

This differs from other, often-seen examples which declare three different task functions (e.g. `static void blink1(void* unused)`, `static void blink2(void* unused)`, `static void blink3(void* unused)`) to implement a specific behaviour.
Those examples don't use / ignore the the parameter to the task function.

