/*
*********************************************************************************************************
*
*	ģ������ : Һλ����������ģ��
*	�ļ����� : bsp_level_input.c
*	��    �� : V1.0
*	˵    �� : 
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

	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource11);	  //��������ʹ�õĶ˿�����Ϊ�ⲿ�ж��������� ��port, pin��
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource12);
}

