# ESP32 blinking LEDs example
This repository contains a LED *component*. The LED component creates a software timer to flash the LED. The application in `main/main.c` uses that LED component. See Espressif's documentation of the [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#example-project) to get an understanding of the directory structure.

The application creates three LED instances to control the RGB LED on [Espressif's WROVER kit](https://docs.espressif.com/projects/esp-idf/en/latest/hw-reference/modules-and-boards.html#esp-wrover-kit-v4-1).

The LED initializer `led_init()` passes the LED instance to the timer "constructor" `xTimerCreate()`.

The LED flash function (`static void blink(TimerHandle_t timer)`) then uses `pvTimerGetTimerID()` to retrieve the LED instance from the passed timer handle.

