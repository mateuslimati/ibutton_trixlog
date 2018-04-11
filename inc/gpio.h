/*
 * gpio.h
 *
 *  Created on: 8 de abr de 2018
 *      Author: Mateus Lima
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f0xx_gpio.h"

void delay();
void GPIO_Config(uint32_t RCC_AHBPeriph, uint32_t GPIO_Pin, uint32_t Mode);

#endif /* GPIO_H_ */
