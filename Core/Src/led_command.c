/*
 * led_command.c
 *
 *  Created on: 8 жовт. 2021 р.
 *      Author: andrii.peleno
 */

#include "led_command.h"
#include "led_driver.h"

static void led_command_execute(command_t * const self);

void led_command_constructor(led_command_t * const self)
{
  static command_vtbl_t const vtbl = {
      .execute = led_command_execute
  };
  self->super.vptr = &vtbl;

}

static void led_command_execute(command_t * const self)
{
  toggle_led1();
}
