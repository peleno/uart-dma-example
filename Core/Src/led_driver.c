/*
 * led_driver.c
 *
 *  Created on: Oct 8, 2021
 *      Author: andrii.peleno
 */

#include "stm32f4xx_hal.h"

void toggle_led1()
{
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
}
