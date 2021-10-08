/*
 * parser.c
 *
 *  Created on: Oct 7, 2021
 *      Author: andrii.peleno
 */

#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include "pt.h"
#include "stm32f4xx_hal.h"
#include "adc_driver.h"
#include "led_driver.h"
#include "main.h"


#define TX_BUFFER_SIZE 30
#define RX_BUFFER_SIZE 10
#define RX_DMA_BUFFER_SIZE 2


char uart_rx_buffer[RX_BUFFER_SIZE];
uint8_t uart_rx_buffer_index = 0;
uint8_t uart_rx_dma_buffer[RX_DMA_BUFFER_SIZE];
volatile bool is_receiving_complete = false;
volatile bool is_adc_command_received = false;
struct pt pt;


static void dma_receive_first_byte(DMA_HandleTypeDef *hdma);
static void dma_receive_second_byte(DMA_HandleTypeDef *hdma);
static void add_byte_to_rx_buffer(uint8_t rx_byte);
static void usart_transmit_formatted_string(UART_HandleTypeDef *huart2, const char *format, ...);
static void dma_init_interrupts();
static void usart2_transmit_adc_message(struct pt *pt);

void parse()
{
  PT_INIT(&pt);
  dma_init_interrupts();

  while (1)
  {
    if (is_receiving_complete)
    {
      if (strcmp(uart_rx_buffer, "adc") == 0)
      {
        is_adc_command_received = true;
      }

      else if (strcmp(uart_rx_buffer, "led") == 0)
      {
        toggle_led1();
      }

      if (is_adc_command_received)
      {
        usart2_transmit_adc_message(&pt);
      }
      usart_transmit_formatted_string(&huart2, "You sent: %s\n\r", (char*) uart_rx_buffer);
      uart_rx_buffer_index = 0;
      is_receiving_complete = false;
    }
  }
}

static void usart2_transmit_adc_message(struct pt *pt)
{
  uint8_t *raw_value_pointer;
  raw_value_pointer = NULL;
  adc_read_raw_value(pt, &hadc1, raw_value_pointer);
  uint8_t raw_adc_value = *raw_value_pointer;
  usart_transmit_formatted_string(&huart2, "Raw ADC value: %hu\n\r", raw_adc_value);
  is_adc_command_received = false;
}

static void dma_init_interrupts()
{
  HAL_DMA_RegisterCallback(&hdma_usart2_rx, HAL_DMA_XFER_HALFCPLT_CB_ID, &dma_receive_first_byte);
  HAL_DMA_RegisterCallback(&hdma_usart2_rx, HAL_DMA_XFER_CPLT_CB_ID, &dma_receive_second_byte);
  huart2.Instance->CR3 |= USART_CR3_DMAR;
  HAL_DMA_Start_IT(&hdma_usart2_rx, (uint32_t) &huart2.Instance->DR, (uint32_t) uart_rx_dma_buffer,
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
  if (rx_byte == '\r')
  {
    is_receiving_complete = true;
    uart_rx_buffer[uart_rx_buffer_index] = '\0';
  }
  else
  {
    uart_rx_buffer[uart_rx_buffer_index] = rx_byte;
    uart_rx_buffer_index++;
  }
}

static void usart_transmit_formatted_string(UART_HandleTypeDef *huart, const char *format, ...)
{
  va_list args;
  va_start(args, format);

  static char uart_tx_buffer[TX_BUFFER_SIZE] = { 0 };
  vsprintf(uart_tx_buffer, format, args);
  HAL_UART_Transmit(huart, (uint8_t *) uart_tx_buffer, strlen(uart_tx_buffer), 100);
}
