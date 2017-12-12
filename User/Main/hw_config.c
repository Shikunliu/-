/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           hw_config.c
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
** Modified by:         ZQJ
** Modified date:        
** Version:            
** Descriptions:        
**
*****************************************************************/ 

#include "hw_config.h" 


void USART_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD 
						   |RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /*USART1端口配置
	  PA9 TX 复用推挽输出 PA10 RX 浮空输入模式*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 	  //A的Pin9!!!!!!!!

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	    //A的pin10

	/*USART2端口配置
	  PD5 TX 复用推挽输出 PD6 RX 浮空输入模式*/
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
      	
    /*--------------USART1 USART2配置-------------------*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_Cmd(USART2, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		
}

