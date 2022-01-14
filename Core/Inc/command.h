/*
 * command.h
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

typedef struct command_vtbl command_vtbl_t;

typedef struct {
    command_vtbl_t const *vptr;
} command_t;

struct command_vtbl {
    void (*execute)(command_t *const self);
};

void command_execute(command_t *const self);

#endif /* INC_COMMAND_H_ */
