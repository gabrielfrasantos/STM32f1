#include <misc.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

void main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
// Configure clocks for GPIOA and TIM2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

// Configure NVIC -- see preceding section
	NVIC_InitTypeDef NVIC_InitStructure;
// No StructInit call in API
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

// Configure Timer
        TIM_TimeBaseInitTypeDef TIMER_InitStructure;
        
	TIM_TimeBaseStructInit(&TIMER_InitStructure);
	TIMER_InitStructure.TIM_Prescaler = SystemCoreClock/100000 - 1; // 0..239
	TIMER_InitStructure.TIM_Period = 1000 - 1; // 0..999
	TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIMER_InitStructure);

// Enable Timer Interrupt , enable timer
	TIM_ITConfig(TIM2, TIM_IT_Update , ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	while(1) { /* do nothing */ }
}

void TIM2_IRQHandler(void)
{
	/* do something */
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}
