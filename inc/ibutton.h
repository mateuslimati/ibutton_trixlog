/*
 * ibutton.h
 *
 *  Created on: 8 de abr de 2018
 *      Author: mateus
 */

#ifndef IBUTTON_H_
#define IBUTTON_H_

/******* G E N E R I C   D E F I N I T I O N S ************************************************/

#include "oneWire.h"

#define READ_COMMAND_DS2411  	0x33         // Command to read the 64-bit serial number from 1-wire slave device.
#define	HIGH	1
#define	LOW		0
#define	OUTPUT	0
#define	INPUT 	1
#define	CLEARBIN 0


unsigned char Detect_Slave_Device(void);
void hex_ascii(unsigned char display_data);

#endif /* IBUTTON_H_ */
