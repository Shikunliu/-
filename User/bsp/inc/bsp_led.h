/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x_conf.h"

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
#define PFout(n)	*((volatile unsigned long *)(0x42000000+((GPIOF_ODR_Addr-0x40000000)<<5)+(n<<2)))

/* LED */
#define RCC_APB2Periph_LED	RCC_APB2Periph_GPIOD
#define LED_PORT	GPIOD
#define LED1_PIN	GPIO_Pin_2
#define LED2_PIN	GPIO_Pin_3
#define LED3_PIN	GPIO_Pin_4
#define LED4_PIN	GPIO_Pin_7

#define LED1(x)   ((x) ? (GPIO_SetBits(LED_PORT, LED1_PIN)) : (GPIO_ResetBits(LED_PORT, LED1_PIN)));	//若x为0，Reset；反之为Set
#define LED2(x)   ((x) ? (GPIO_SetBits(LED_PORT, LED2_PIN)) : (GPIO_ResetBits(LED_PORT, LED2_PIN)));
#define LED3(x)   ((x) ? (GPIO_SetBits(LED_PORT, LED3_PIN)) : (GPIO_ResetBits(LED_PORT, LED3_PIN)));
#define LED4(x)   ((x) ? (GPIO_SetBits(LED_PORT, LED4_PIN)) : (GPIO_ResetBits(LED_PORT, LED4_PIN)));



void LED_Configuration(void);

#endif
/***************************** (END OF FILE) *********************************/
