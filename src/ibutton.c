/*
 * ibutton.c
 *
 *  Created on: 8 de abr de 2018
 *      Author: mateus
 */

#include "ibutton.h"
#include "oneWire.h"
#include "usart.h"

/**********************************************************************
* Function:        unsigned char Detect_Slave_Device(void)
* PreCondition:    None
* Input:		   None
* Output:		   1 - Not Present   0 - Present
* Overview:   	   To check the presence of slave device.
***********************************************************************/

unsigned char Detect_Slave_Device(void){

	if (!OW_reset_pulse())
		return HIGH;
	else
		return LOW;
}

/**********************************************************************
* Function:        void hex_ascii(unsigned char display_data)
* PreCondition:    None
* Input:		   HEX Value
* Output:		   None
* Side Effects:
* Overview:		 Convert Hex Value to ASCII and send to PC;
***********************************************************************/
void hex_ascii(unsigned char display_data)
{
	unsigned char temp;
	temp = ((display_data & 0xF0)>>4);
	if (temp <= 0x09)
		USART1_PutByte(temp+'0');
	else
		USART1_PutByte(temp+'0'+0x07);

	temp = display_data & 0x0F;
	if (temp <= 0x09)
		USART1_PutByte(temp+'0');
	else
		USART1_PutByte(temp+'0'+0x07);
}
