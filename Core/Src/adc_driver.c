/*
 * adc_driver.c
 *
 *  Created on: Oct 7, 2021
 *      Author: andrii.peleno
 */

#include "adc_driver.h"
#include "stm32f4xx_hal.h"
#include "pt.h"
#include <stdbool.h>
#include "main.h"


static bool adc_conversion_ended(ADC_HandleTypeDef *hadc);


PT_THREAD(adc_read_raw_value(struct pt *pt, ADC_HandleTypeDef *hadc1, uint8_t *raw_value_pointer))
{
  PT_BEGIN(pt);

  HAL_ADC_Start(hadc1);
  PT_WAIT_UNTIL(pt, adc_conversion_ended(hadc1));

  /* Clear regular group conversion flag */
  __HAL_ADC_CLEAR_FLAG(hadc1, ADC_FLAG_STRT | ADC_FLAG_EOC);

  /* Update ADC state machine */
  SET_BIT(hadc1->State, HAL_ADC_STATE_REG_EOC);

  *raw_value_pointer = HAL_ADC_GetValue(hadc1);
  PT_END(pt);
}

static bool adc_conversion_ended(ADC_HandleTypeDef *hadc)
{
  return __HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOC);
}
