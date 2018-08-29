#include <misc.h>

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