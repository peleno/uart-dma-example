/*
 * uart_utils.h
 *
 *  Created on: Feb 10, 2022
 *      Author: andrii.peleno
 */

#ifndef INC_UART_LISTENER_H_
#define INC_UART_LISTENER_H_

#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart3;

void uart_printf(const char *format, ...);

#endif /* INC_UART_LISTENER_H_ */