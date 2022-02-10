/*
 * serial_listener.h
 *
 *  Created on: Jan 28, 2022
 *      Author: andrii.peleno
 */

#ifndef INC_SERIAL_LISTENER_H_
#define INC_SERIAL_LISTENER_H_

// includes
#include "stm32f4xx_hal.h"

// typedefs
typedef void (*command_received_callback_t)(char *command);

// functions' prototypes
void serial_listener_start(command_received_callback_t command_received_callback);

#endif /* INC_SERIAL_LISTENER_H_ */