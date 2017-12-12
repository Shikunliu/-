/*
*********************************************************************************************************
*
*	模块名称 : 液位传感器输入模块
*	文件名称 : bsp_level_input.c
*	版    本 : V1.0
*	说    明 : 
*
*
*
*********************************************************************************************************
*/

#include "bsp_level_sensor_input.h"

void LEVEL_SENSOR_INPUT_Configuration(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource11);	  //将按键所使用的端口配置为外部中断输入引脚 （port, pin）
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource12);
}

