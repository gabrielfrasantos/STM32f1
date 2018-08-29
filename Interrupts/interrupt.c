#include <misc.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

main{
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
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/100000 - 1; // 0..239
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 0..999
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

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
