/*
 * ibutton.c
 *
 *  Created on: 8 de abr de 2018
 *      Author: mateus
 */

#include "ibutton.h"
#include "oneWire.h"
#include "usart.h"

unsigned char ROM_NO[8];
uint8_t LastDiscrepancy;
uint8_t LastFamilyDiscrepancy;
unsigned char LastDeviceFlag;

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

//
unsigned char search(uint8_t *newAddr)
{
   uint8_t id_bit_number;
   uint8_t last_zero, rom_byte_number;
   unsigned char search_result;
   uint8_t id_bit, cmp_id_bit;

   unsigned char rom_byte_mask, search_direction;

   // initialize for search
   id_bit_number = 1;
   last_zero = 0;
   rom_byte_number = 0;
   rom_byte_mask = 1;
   search_result = 0x00;

   // if the last call was not the last one
   if (!LastDeviceFlag) {
      // 1-Wire reset
      if (!OW_reset_pulse()){
         // reset the search
         LastDiscrepancy = 0;
         LastDeviceFlag = 0x00;
         LastFamilyDiscrepancy = 0;
         return 0x00;
      }

      // issue the search command

      OW_write_byte(0xF0);   // NORMAL SEARCH

      // loop to do the search
      do
      {
         // read a bit and its complement
         id_bit = OW_read_bit();
         cmp_id_bit = OW_read_bit();

         // check for no devices on 1-wire
         if ((id_bit == 1) && (cmp_id_bit == 1)) {
            break;
         } else {
            // all devices coupled have 0 or 1
            if (id_bit != cmp_id_bit) {
               search_direction = id_bit;  // bit write value for search
            } else {
               // if this discrepancy if before the Last Discrepancy
               // on a previous next then pick the same as last time
               if (id_bit_number < LastDiscrepancy) {
                  search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
               } else {
                  // if equal to last pick 1, if not then pick 0
                  search_direction = (id_bit_number == LastDiscrepancy);
               }
               // if 0 was picked then record its position in LastZero
               if (search_direction == 0) {
                  last_zero = id_bit_number;

                  // check for Last discrepancy in family
                  if (last_zero < 9)
                     LastFamilyDiscrepancy = last_zero;
               }
            }

            // set or clear the bit in the ROM byte rom_byte_number
            // with mask rom_byte_mask
            if (search_direction == 1)
              ROM_NO[rom_byte_number] |= rom_byte_mask;
            else
              ROM_NO[rom_byte_number] &= ~rom_byte_mask;

            // serial number search direction write bit
            OW_write_bit(search_direction);

            // increment the byte counter id_bit_number
            // and shift the mask rom_byte_mask
            id_bit_number++;
            rom_byte_mask <<= 1;

            // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
            if (rom_byte_mask == 0) {
                rom_byte_number++;
                rom_byte_mask = 1;
            }
         }
      }
      while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7

      // if the search was successful then
      if (!(id_bit_number < 65)) {
         // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
         LastDiscrepancy = last_zero;

         // check for last device
         if (LastDiscrepancy == 0) {
            LastDeviceFlag = 0x01;
         }
         search_result = 0x01;
      }
   }
   // if no device found then reset counters so next 'search' will be like a first
   if (!search_result || !ROM_NO[0]) {
      LastDiscrepancy = 0;
      LastDeviceFlag = 0x00;
      LastFamilyDiscrepancy = 0;
      search_result = 0x00;
   } else {
      for (int i = 0; i < 8; i++) newAddr[i] = ROM_NO[i];
   }
   return search_result;
}

uint8_t crc8(const uint8_t *addr, uint8_t len)
{
	uint8_t crc = 0;

	while (len--) {

		uint8_t inbyte = *addr++;
		for (uint8_t i = 8; i; i--) {
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix) crc ^= 0x8C;
			inbyte >>= 1;
		}
	}
	return crc;
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

