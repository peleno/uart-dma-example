/*
 * command.h
 *
 *  Created on: Oct 8, 2021
 *      Author: andrii.peleno
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_


typedef void (*command_handler_t)();

typedef struct {
    char *name;
    command_handler_t execute;
} command_t;


#endif /* INC_COMMAND_H_ */
