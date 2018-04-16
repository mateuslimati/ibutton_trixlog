/*
 * delay.c
 *
 *  Created on: 9 de abr de 2018
 *      Author: mateus
 */

#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"
#include <stdint.h>
#include "delay.h"

// init delay
// delay function: micros >= 1;
void delay_us(uint32_t micros){

	uint32_t us_multiplier;

    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks); // Get system clocks
    us_multiplier = RCC_Clocks.SYSCLK_Frequency / 1000000; //For 1 us delay, we need to divide with 1M */

	micros *= us_multiplier;

	//substitute 8 cycles for each call of asm code below == //micros /= 8;

//	__asm(" movw r0, (micros) \n"
//	"loop: sub r0, #8 \n"
//    " bhi loop \n");
}


// Init timer for Microseconds delays
void _init_us() {
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	// Time base configuration
	TIM_TimeBaseInitTypeDef TIM;
	TIM_TimeBaseStructInit(&TIM);
	TIM.TIM_Prescaler = (SystemCoreClock/DELAY_TIM_FREQUENCY_US)-1;
	TIM.TIM_Period = UINT16_MAX;
	TIM.TIM_ClockDivision = 0;
	TIM.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM);

	// Enable counter for TIM2
	TIM_Cmd(TIM2,ENABLE);
}

// Init and start timer for Milliseconds delays
void _init_ms() {
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	// Time base configuration
	TIM_TimeBaseInitTypeDef TIM;
	TIM_TimeBaseStructInit(&TIM);
	TIM.TIM_Prescaler = (SystemCoreClock/DELAY_TIM_FREQUENCY_MS)-1;
	TIM.TIM_Period = UINT16_MAX;
	TIM.TIM_ClockDivision = 0;
	TIM.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM);

	// Enable counter for TIM2
	TIM_Cmd(TIM2,ENABLE);
}

// Stop timer
void _stop_timer() {
	TIM_Cmd(TIM2,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,DISABLE); // Powersavings?
}

// Do delay for nTime milliseconds
void Delay_ms(uint32_t mSecs) {
	// Init and start timer
	_init_ms();

	// Dummy loop with 16 bit count wrap around
	volatile uint32_t start = TIM2->CNT;
	while((TIM2->CNT-start) <= mSecs);

	// Stop timer
	_stop_timer();
}

// Do delay for nTime microseconds
void Delay_us(uint32_t uSecs) {
	// Init and start timer
	_init_us();

	// Dummy loop with 16 bit count wrap around
	volatile uint32_t start = TIM2->CNT;
	while((TIM2->CNT-start) <= uSecs);

// Stop timer
	_stop_timer();
}
