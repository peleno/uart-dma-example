/*
 * commands_manager.c
 *
 *  Created on: Oct 8, 2021
 *      Author: andrii.peleno
 */

#include <stdio.h>
#include "command.h"
#include "adc_command.h"
#include "led_command.h"
#include "commands_manager.h"


static const command_t commands[COMMANDS_COUNT] = {
    {.name = "adc", .execute = adc_command_execute},
    {.name = "led", .execute = led_command_execute}
};


void process_command(char *command_name)
{
    for (int i = 0; i < COMMANDS_COUNT; i++) {
        command_t command = commands[i];
        if (strcmp(command.name, command_name) == 0) {
            command.execute();
            return;
        }
    }
    uart_printf("Command is not recognized\n\r");
}
