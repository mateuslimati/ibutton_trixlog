/*
 * OneWire.c
 *
 *  Created on: 8 de abr de 2018
 *      Author: mateus
 */

#include "ibutton.h"
#include "oneWire.h"
#include "gpio.h"
#include "delay.h"

//****** V A R I A B L E S ********************************************************/
unsigned char macro_delay;

/**********************************************************************
* Function:        void drive_OW_low (void)
* PreCondition:    None
* Input:		   None
* Output:		   None
* Overview:		   Configure the OW_PIN as Output and drive the OW_PIN LOW.
***********************************************************************/
void drive_OW_low (void){

	GPIO_Config(GPIOB, GPIO_Pin_4, GPIO_Mode_OUT);
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);

}

/**********************************************************************
* Function:        void drive_OW_high (void)
* PreCondition:    None
* Input:		   None
* Output:		   None
* Overview:		   Configure the OW_PIN as Output and drive the OW_PIN HIGH.
***********************************************************************/
void drive_OW_high (void){

	GPIO_Config(GPIOB, GPIO_Pin_4, GPIO_Mode_OUT);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

/**********************************************************************
* Function:        unsigned char read_OW (void)
* PreCondition:    None
* Input:		   None
* Output:		   Return the status of OW pin.
* Overview:		   Configure as Input pin and Read the status of OW_PIN
***********************************************************************/
unsigned char read_OW(void){

	unsigned char read_data=0;

	GPIO_Config(GPIOB, GPIO_Pin_4, GPIO_Mode_IN);

	 if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4))
	 	read_data = SET;
	 else
		read_data = CLEARBIN;

	return read_data;
}

/**********************************************************************
* Function:        unsigned char OW_reset_pulse(void)
* PreCondition:    None
* Input:		   None
* Output:		   Return the Presense Pulse from the slave.
* Overview:		   Initialization sequence start with reset pulse.
*				   This code generates reset sequence as per the protocol
***********************************************************************/
unsigned char OW_reset_pulse(void){

	unsigned char presence_detect;

  	drive_OW_low(); 				// Drive the bus low
  	Delay_us(480);	  			// delay 480 microsecond (us)
 	drive_OW_high();  				// Release the bus
 	Delay_us(70);				// delay 70 microsecond (us)
	presence_detect = read_OW();	//Sample for presence pulse from slave
	Delay_us(410);	  			// delay 410 microsecond (us)
	drive_OW_high();		    	// Release the bus
	if(presence_detect == 0x01)
		return 0x00;
	return 0x01;

}

/**********************************************************************
* Function:        void OW_write_bit (unsigned char write_data)
* PreCondition:    None
* Input:		   Write a bit to 1-wire slave device.
* Output:		   None
* Overview:		   This function used to transmit a single bit to slave device.
*
***********************************************************************/

void OW_write_bit(unsigned char write_bit){

	if(write_bit)
	{
		//writing a bit '1'
		drive_OW_low(); 				// Drive the bus low
		Delay_us(10);				// delay 6 microsecond (us)
		drive_OW_high();  				// Release the bus
		Delay_us(55);				// delay 64 microsecond (us)
	}
	else
	{
		//writing a bit '0'
		drive_OW_low(); 				// Drive the bus low
		Delay_us(65);				// delay 60 microsecond (us)
		drive_OW_high();  				// Release the bus
		Delay_us(5);				// delay 10 microsecond for recovery (us)
	}
}


/**********************************************************************
* Function:        unsigned char OW_read_bit (void)
* PreCondition:    None
* Input:		   None
* Output:		   Return the status of the OW PIN
* Overview:		   This function used to read a single bit from the slave device.
*
***********************************************************************/

unsigned char OW_read_bit(void){

	unsigned char read_data;
	//reading a bit
	drive_OW_low(); 						// Drive the bus low
	Delay_us(13);						// delay 6 microsecond (us)

	read_data = read_OW();					//Read the status of OW_PIN

	Delay_us(53);						// delay 55 microsecond (us)
	return read_data;

}

/**********************************************************************
* Function:        void OW_write_byte (unsigned char write_data)
* PreCondition:    None
* Input:		   Send byte to 1-wire slave device
* Output:		   None
* Overview:		   This function used to transmit a complete byte to slave device.
*
***********************************************************************/
void OW_write_byte (unsigned char write_data){

	unsigned char loop;

	for (loop = 0; loop < 8; loop++)
	{
		OW_write_bit(write_data & 0x01); 	//Sending LS-bit first
		write_data >>= 1;					// shift the data byte for the next bit to send
	}

}

/**********************************************************************
* Function:        unsigned char OW_read_byte (void)
* PreCondition:    None
* Input:		   None
* Output:		   Return the read byte from slave device
* Overview:		   This function used to read a complete byte from the slave device.
*
***********************************************************************/

unsigned char OW_read_byte(void){

	unsigned char bitMask;
	unsigned char r = 0;

	for (bitMask = 0x01; bitMask; bitMask <<= 1){
		if(OW_read_bit())
			r |= bitMask;

	}
	return r;

}
