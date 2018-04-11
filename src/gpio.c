/**
  ******************************************************************************
  * @file    gpio.c
  * @author  Mateus
  * @version V1.0
  * @date    07-April-2018
  * @brief   gpio function.
  ******************************************************************************
*/

#include "stm32f0xx_gpio.h"


void GPIO_Config(uint32_t RCC_AHBPeriph, uint32_t GPIO_Pin, uint8_t Mode){

	GPIO_InitTypeDef GPIO_Configure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph, ENABLE);

	GPIO_Configure.GPIO_Pin = GPIO_Pin;
	GPIO_Configure.GPIO_Mode = Mode;
	GPIO_Configure.GPIO_OType = GPIO_OType_PP;
	GPIO_Configure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Configure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init(GPIOB, &GPIO_Configure);

}
