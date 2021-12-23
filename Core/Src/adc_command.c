/*
 * adc_command.c
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */

#include "adc_command.h"
#include "adc_driver.h"


static void adc_command_execute(command_t * const self);

void adc_command_constructor(adc_command_t * const self)
{
  static command_vtbl_t const vtbl = {
      .execute = &adc_command_execute
  };

  self->super.vptr = &vtbl;
}

static void adc_command_execute(command_t * const self)
{

}
