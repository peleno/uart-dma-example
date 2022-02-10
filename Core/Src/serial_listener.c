/*
 * serial_listener.c
 *
 *  Created on: Jan 28, 2022
 *      Author: andrii.peleno
 */

// includes
#include <stdio.h>
#include <stdbool.h>
#include "serial_listener.h"
#include "stm32f4xx_hal.h"

// constants
#define RX_BUFFER_SIZE 100
#define RX_DMA_BUFFER_SIZE 2

// runtime data
char uart_rx_buffer[RX_BUFFER_SIZE];
static uint8_t uart_rx_buffer_index = 0;
static uint8_t uart_rx_dma_buffer[RX_DMA_BUFFER_SIZE];
static command_received_callback_t on_command_received;

// extern
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;

// private function's prototypes
static void add_byte_to_rx_buffer(uint8_t rx_byte);
static void dma_receive_first_byte(DMA_HandleTypeDef *hdma);
static void dma_receive_second_byte(DMA_HandleTypeDef *hdma);
static void dma_init_interrupts(DMA_HandleTypeDef *hdma);

// public functions implementation
void serial_listener_start(command_received_callback_t command_received_callback)
{
    on_command_received = command_received_callback;
    dma_init_interrupts(&hdma_usart3_rx);
}

// static functions implementation
static void dma_init_interrupts(DMA_HandleTypeDef *hdma)
{
    HAL_DMA_RegisterCallback(hdma, HAL_DMA_XFER_HALFCPLT_CB_ID, &dma_receive_first_byte);
    HAL_DMA_RegisterCallback(hdma, HAL_DMA_XFER_CPLT_CB_ID, &dma_receive_second_byte);
    huart3.Instance->CR3 |= USART_CR3_DMAR;

    HAL_DMA_Start_IT(hdma,
                     (uint32_t) &huart3.Instance->DR,
                     (uint32_t) uart_rx_dma_buffer,
                     RX_DMA_BUFFER_SIZE);
}

static void dma_receive_first_byte(DMA_HandleTypeDef *hdma)
{
    uint8_t rx_byte = uart_rx_dma_buffer[0];
    add_byte_to_rx_buffer(rx_byte);
}

static void dma_receive_second_byte(DMA_HandleTypeDef *hdma)
{
    uint8_t rx_byte = uart_rx_dma_buffer[1];
    add_byte_to_rx_buffer(rx_byte);
}

static void add_byte_to_rx_buffer(uint8_t rx_byte)
{
    if (rx_byte == '\r') {
        uart_rx_buffer[uart_rx_buffer_index] = '\0';
        on_command_received(uart_rx_buffer);
        uart_rx_buffer_index = 0;
    } else {
        uart_rx_buffer[uart_rx_buffer_index] = rx_byte;
        uart_rx_buffer_index++;
    }
}
