/*
 * adc_driver.h
 *
 *  Created on: Oct 7, 2021
 *      Author: andrii.peleno
 */

#ifndef INC_ADC_DRIVER_H_
#define INC_ADC_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "pt.h"

PT_THREAD( adc_read_raw_value(struct pt *pt, ADC_HandleTypeDef *hadc1, uint8_t *raw_value_pointer));

#endif /* INC_ADC_DRIVER_H_ */
