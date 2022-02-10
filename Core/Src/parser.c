/*
 * parser.c
 *
 *  Created on: Oct 7, 2021
 *      Author: andrii.peleno
 */

#include "parser.h"
#include <string.h>
#include "adc_command.h"
#include "led_command.h"
#include "command.h"
#include "serial_listener.h"
#include "uart_utils.h"

static void process_command(char *command);


void parse()
{
    serial_listener_start(process_command);
}

static void process_command(char *command)
{
    command_t *command_p;
    led_command_t led_command;
    adc_command_t adc_command;
    led_command_constructor(&led_command);
    adc_command_constructor(&adc_command);    

    if (strcmp(command, "adc") == 0) {
        command_p = &adc_command.super;
    } else if (strcmp(command, "led") == 0) {
        command_p = &led_command.super;
    } else {
        command_p = NULL;
    }

    if (command_p != NULL) {
        command_execute(command_p);
    }
    uart_printf("You sent: %s\n\r", command);
}
