#include <misc.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"

void main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitTypeDef  GPIO_InitStructure;
  /* Configure PC.13 pin as PP */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure PA.04 pin as in floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* Connect EXTI0 Line to PC.13 pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);

  EXTI_InitTypeDef   EXTI_InitStructure;
  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitTypeDef   NVIC_InitStructure;
  /* Enable and set EXTI0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  while(1) 
  { 
    GPIO_SetBits(GPIOC, GPIO_Pin_13); // Set C13 to High level ("1")
    //GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")
  }
}

void EXTI4_IRQHandler(void)
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
        EXTI_ClearITPendingBit(EXTI_Line4);
}
