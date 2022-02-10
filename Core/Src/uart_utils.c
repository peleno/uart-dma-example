/*
 * uart_utils.c
 *
 *  Created on: Feb 10, 2022
 *      Author: andrii.peleno
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "uart_utils.h"

#define TX_BUFFER_SIZE 30
#define TX_TIMEOUT 100 // in milliseconds


static void uart_printf_with_handle(UART_HandleTypeDef *huart, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    static char uart_tx_buffer[TX_BUFFER_SIZE] = { 0 };
    vsprintf(uart_tx_buffer, format, args);
    if (TX_BUFFER_SIZE < strlen(uart_tx_buffer)) {
        // cannot transmit such large message
        return;
    }
    HAL_UART_Transmit(huart, (uint8_t*) uart_tx_buffer, strlen(uart_tx_buffer), TX_TIMEOUT);
}

void uart_printf(const char *format, ...)
{
    uart_printf_with_handle(&huart3, format);
}