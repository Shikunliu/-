/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           bsp_limit_switch.c
** Last modified Date:  2017-11-27
** Last Version:        V1.00
** Descriptions:        Ӳ�������ļ�
**
**----------------------------------------------------------------------------------------------------
** Created by:          Shikun
** Created date:        2017-11-27
** Version:             V1.00
** Descriptions:        ��дʾ������
**
**----------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:        
** Version:            
** Descriptions:        
**
*****************************************************************/ 


#include "bsp_limit_switch.h"
#include "bsp_led.h"

/**
	*�������ƣ�void BUTTON_Configuration(void)
	*
	*��ڲ�������
	*
	*���ڲ�������
	*
	*����˵����BUTTON��ʼ������
    */
void BUTTON_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	  //ʹ�����ȼ�����2

	/*�ⲿ�ж���*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn ; 	  //  ����EXIT��15-10�ߵ��ж�����, EXTI15_10_IRQn������stm32f10x.h��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ;	   //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		   //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure);	  //��Ĵ���д�����

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource11);	  //��������ʹ�õĶ˿�����Ϊ�ⲿ�ж��������� ��port, pin��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource12);
}

/**
	*�������ƣ�void EXTI_Configuration(void)
	*
	*��ڲ�������
	*
	*���ڲ�������
	*
	*����˵����EXTI��ʼ������
    */
void EXTI_Configuration(void) //����ͨ������Ӧ�Ĵ�����ʽ
{
	EXTI_InitTypeDef EXTI_InitStructure;
	/*PD11�ⲿ�ж�����*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line11; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd	= ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/*PD12�ⲿ�ж�����*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd	= ENABLE; 
	EXTI_Init(&EXTI_InitStructure);	   //����λ��stm32f10x_exit.c

}

/**
  * @name	void EXTI9_5_IRQHandler(void)	
  * @brief	�ⲿ�ж���Ӧ�����������ⲿ��USER1��
  * @param  None
  * @retval	None
  */
void EXTI15_10_IRQHandler(void)	  //�жϺ�����Դ
{
	extern uint32_t limit_switch_flag_1;
	extern uint32_t limit_switch_flag_2;
		
	if(EXTI_GetITStatus(EXTI_Line11)!= RESET) //����������if�ж��ж�Դ 
	{  
		EXTI_ClearITPendingBit(EXTI_Line11);   //����жϱ�־
		LED3(1);
		limit_switch_flag_1=1;
	}

	if(EXTI_GetITStatus(EXTI_Line12)!= RESET)  
	{  
		EXTI_ClearITPendingBit(EXTI_Line12);
		LED4(1);
		limit_switch_flag_2=1;
	}    

}

/*************************************************************/
