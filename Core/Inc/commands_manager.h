/*
 * commands_manager.h
 *
 *  Created on: Feb 11, 2022
 *      Author: andrii.peleno
 */

#ifndef INC_COMMANDS_MANAGER_H_
#define INC_COMMANDS_MANAGER_H_


typedef enum {
    ADC_COMMAND,
    LED_COMMAND,
    COMMANDS_COUNT
} command_types;


void process_command(char *command_name);


#endif /* INC_COMMANDS_MANAGER_H_ */
