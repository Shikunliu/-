/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           bsp_limit_switch.c
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


#include "bsp_limit_switch.h"
#include "bsp_led.h"

/**
	*函数名称：void BUTTON_Configuration(void)
	*
	*入口参数：无
	*
	*出口参数：无
	*
	*功能说明：BUTTON初始化配置
    */
void BUTTON_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	  //使用优先级分组2

	/*外部中断线*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn ; 	  //  配置EXIT第15-10线的中断向量, EXTI15_10_IRQn定义于stm32f10x.h中
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ;	   //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		   //子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure);	  //向寄存器写入参数

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource11);	  //将按键所使用的端口配置为外部中断输入引脚 （port, pin）
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD , GPIO_PinSource12);
}

/**
	*函数名称：void EXTI_Configuration(void)
	*
	*入口参数：无
	*
	*出口参数：无
	*
	*功能说明：EXTI初始化配置
    */
void EXTI_Configuration(void) //配置通道和相应的触发方式
{
	EXTI_InitTypeDef EXTI_InitStructure;
	/*PD11外部中断输入*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line11; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd	= ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/*PD12外部中断输入*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd	= ENABLE; 
	EXTI_Init(&EXTI_InitStructure);	   //函数位于stm32f10x_exit.c

}

/**
  * @name	void EXTI9_5_IRQHandler(void)	
  * @brief	外部中断响应函数，这里外部接USER1键
  * @param  None
  * @retval	None
  */
void EXTI15_10_IRQHandler(void)	  //中断函数入源
{
	extern uint32_t limit_switch_flag_1;
	extern uint32_t limit_switch_flag_2;
		
	if(EXTI_GetITStatus(EXTI_Line11)!= RESET) //首先用两个if判断中断源 
	{  
		EXTI_ClearITPendingBit(EXTI_Line11);   //清除中断标志
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
