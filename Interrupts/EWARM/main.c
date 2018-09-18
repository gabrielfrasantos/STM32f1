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
        
        GPIO_InitTypeDef  GPIO_InitStructure;
        /* Initialize LED which connected to PC13 */
// Enable PORTC Clock
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        /* Configure the GPIO_LED pin */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        
        GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")
        
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

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
	TIMER_InitStructure.TIM_Prescaler = 65535; 
	TIMER_InitStructure.TIM_Period = 732; 
	TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIMER_InitStructure);

// Enable Timer Interrupt , enable timer
	TIM_ITConfig(TIM2, TIM_IT_Update , ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	while(1) { 
            //GPIO_SetBits(GPIOC, GPIO_Pin_13); // Set C13 to High level ("1")
            GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")
        }
}

void TIM2_IRQHandler(void)
{
	/* do something */
        GPIOC->ODR ^= GPIO_Pin_13;
        for (int i=0; i<1000000; i++){
        }
        GPIOC->ODR ^= GPIO_Pin_13; 
        for (int i=0; i<1000000; i++){
        }
        GPIOC->ODR ^= GPIO_Pin_13;
        for (int i=0; i<1000000; i++){
        }
        GPIOC->ODR ^= GPIO_Pin_13;
        for (int i=0; i<1000000; i++){
        }
        GPIOC->ODR ^= GPIO_Pin_13;
        for (int i=0; i<1000000; i++){
        }
        GPIOC->ODR ^= GPIO_Pin_13;
        for (int i=0; i<1000000; i++){
        }
        GPIOC->ODR ^= GPIO_Pin_13;
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}
