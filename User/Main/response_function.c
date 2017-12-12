/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           hw_config.c
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
** Modified by:         ZQJ
** Modified date:        
** Version:            
** Descriptions:        
**
*****************************************************************/ 

#include "response_function.h" 
#include "stm32f10x.h"
//#include "hw_config.h"
//#include "stm32f10x_it.h"

/**
	*���ƣ�void response_usart(void)
	*���룺��
	*�������
	*���ܣ���Ӧ����
	*˵����
**/


void response_usart(u8* USART_RX_BUF)
{
	if(USART_RX_BUF[0]=='1')
		{
			RELAY1(1); USART1_SendString("\r\n 1�ŵ�ŷ��Ѵ�! \r\n");
		}
		else if(USART_RX_BUF[0]=='0') 
		{
			RELAY1(0); USART1_SendString("\r\n 1�ŵ�ŷ��ѹر�! \r\n");
		}
	
		if(USART_RX_BUF[1]=='1')
		{
			RELAY2(1); USART1_SendString("\r\n 2�ŵ�ŷ��Ѵ�! \r\n");
		}
		else if(USART_RX_BUF[1]=='0') 
		{
			RELAY2(0); USART1_SendString("\r\n 2�ŵ�ŷ��ѹر�! \r\n");
		}

		if(USART_RX_BUF[2]=='1')
		{
			LED1(1); USART1_SendString("\r\n LED1����! \r\n");
		}
		else if(USART_RX_BUF[2]=='0') 
		{
			LED1(0); USART1_SendString("\r\n LED1Ϩ��! \r\n");
		}
	
		if(USART_RX_BUF[3]=='1')
		{
			LED2(1); USART1_SendString("\r\n LED2����!  \r\n");
		}
		else if(USART_RX_BUF[3]=='0') 
		{
			LED2(0); USART1_SendString("\r\n LED2Ϩ��! \r\n");
		}

		if(USART_RX_BUF[4]=='1')
		{
			LED3(1); USART1_SendString("\r\n LED3����!  \r\n");
		}
		else if(USART_RX_BUF[4]=='0') 
		{
			LED3(0); USART1_SendString("\r\n LED3Ϩ��!  \r\n");
		}
	
		if(USART_RX_BUF[5]=='1')
		{
			LED4(1); USART1_SendString("\r\n LED4����! \r\n");
		}
		else if(USART_RX_BUF[5]=='0') 
		{
			LED4(0); USART1_SendString("\r\n LED4Ϩ��!  \r\n");
		}
	
}