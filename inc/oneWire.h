/*
 * OneWire.h
 *
 *  Created on: 8 de abr de 2018
 *      Author: mateus
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include "gpio.h"

/** P R O T O T Y P E S ******************************************************/
void wait(uint32_t delay_time);
void drive_one_wire_low (void);
void drive_one_wire_high (void);
unsigned char read__one_wire (void);
void OW_write_bit (unsigned char write_data);
unsigned char OW_read_bit (void);
unsigned char OW_reset_pulse(void);
void OW_write_byte (unsigned char write_data);
unsigned char OW_read_byte (void);


#endif /* ONEWIRE_H_ */
