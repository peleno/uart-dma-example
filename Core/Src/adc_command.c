/*
 * adc_command.c
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */

#include <stdio.h>
#include "adc_command.h"
#include "adc_driver.h"
#include "stm32f4xx_hal.h"
#include "uart_utils.h"


static void adc_command_execute(command_t *const self);

extern ADC_HandleTypeDef hadc1;

void adc_command_constructor(adc_command_t *const self)
{
    static command_vtbl_t const vtbl = { .execute = &adc_command_execute };

    self->super.vptr = &vtbl;
}

static void adc_command_execute(command_t *const self)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint8_t raw_adc_value = HAL_ADC_GetValue(&hadc1);
    uart_printf("Raw ADC value: %hu\n\r", raw_adc_value);
}
