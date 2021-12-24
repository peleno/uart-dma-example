/*
 * commands_creator.c
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */

#include "command.h"
#include "adc_command.h"
#include "led_command.h"

typedef struct {
    char *command_string;
    command_t *command;
} command_map_t;

adc_command_t *adc_command;
led_command_t *led_command;
//command_map_t command_maps[5];

void init_commands()
{
    adc_command_constructor(adc_command);
    led_command_constructor(led_command);
    command_map_t command_maps[] = { { .command_string = "adc", .command = &adc_command->super },
                                     { .command_string = "led", .command = &led_command->super } };
}
