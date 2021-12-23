/*
 * command.c
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */


#include "command.h"

void command_execute(command_t * const self)
{
  self->vptr->execute(self);
}
