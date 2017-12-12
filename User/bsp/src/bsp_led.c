/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           bsp_LED.c
** Last modified Date:  2017-11-27
** Last Version:        V1.00
** Descriptions:        硬件配置文件
**
**----------------------------------------------------------------------------------------------------
** Created by:          Shikun
** Created date:        2017-11-27
** Version:             V1.00
** Descriptions:        编写示例代码
**
**----------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:        
** Version:            
** Descriptions:        
**
*****************************************************************/ 


#include "bsp_led.h"



void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LED, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //io口八种工作方式的一种：PP，push&pull， 推挽输出
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	/*---------初始化状态四个LED全OFF------------*/
	LED1(0);
	LED2(0);
	LED3(0);
	LED4(0);
}

/***************************** (END OF FILE) *********************************/
