/*
 * adc_command.h
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */

#ifndef INC_ADC_COMMAND_H_
#define INC_ADC_COMMAND_H_

#include "command.h"

typedef struct
{
  command_t super;
} adc_command_t;

void adc_command_constructor(adc_command_t * const self);

#endif /* INC_ADC_COMMAND_H_ */
