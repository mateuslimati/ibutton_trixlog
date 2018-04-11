/**
  ******************************************************************************
  * @file    main.c
  * @author  Mateus Lima
  * @version V1.0
  * @date    04-April-2018
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "ibutton.h"
#include "usart.h"

volatile uint32_t Milliseconds = 0;


void SysTick_Handler(void){
	Milliseconds++; //Increment millisecond variable
}

void DelayMil(uint64_t MilS){
	volatile uint64_t MSStart = Milliseconds;
	while((Milliseconds - MSStart)<MilS) asm volatile("nop");
}

int main(void){

	SystemInit(); //Ensure CPU is running at correctly set clock speed
	SystemCoreClockUpdate(); //Update SystemCoreClock variable to current clock speed
	SysTick_Config(SystemCoreClock/1000); //Set up a systick interrupt every millisecond

	GPIO_Config(RCC_AHBPeriph_GPIOB, GPIO_Pin_3, GPIO_Mode_OUT);
	USART1_DeInit();
	USART1_EnableRxInterrupt();

	Milliseconds = 0;
	unsigned char temp;
	unsigned char serial_number[8];

	while(1){

		GPIO_ResetBits(GPIOB, GPIO_Pin_3);
		if(Detect_Slave_Device()){
			USART1_PutString("SLAVE Device is present\r\n");
			OW_write_byte(0x33); //Here is the code to read a serial number
			USART1_PutString("SERIAL NUMBER:  \r\n");
			for(temp = 0; temp<8; temp++)
				serial_number[temp] = OW_read_byte();	// Read 64-bit registration (48-bit serial number) number from 1-wire Slave Device

			for(temp = 0; temp<8; temp++){
				hex_ascii(serial_number[temp]);
				if(temp%2 != 0)
					USART1_PutString(" ");
			}//Convert Hex Value into ASCII and send to terminal
			USART1_PutString("\n\r");
			GPIO_SetBits(GPIOB, GPIO_Pin_3);
			DelayMil(250);
		}

	}
}
