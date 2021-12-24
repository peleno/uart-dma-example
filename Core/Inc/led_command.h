/*
 * led_command.h
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */

#ifndef INC_LED_COMMAND_H_
#define INC_LED_COMMAND_H_

#include "command.h"

typedef struct {
    command_t super;
} led_command_t;

void led_command_constructor(led_command_t *const self);

#endif /* INC_LED_COMMAND_H_ */
