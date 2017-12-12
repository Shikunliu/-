/*
*********************************************************************************************************
*
*	ģ������ : MODSͨ��ģ��. ��վģʽ
*	�ļ����� : modbus_slave.c
*	��    �� : V1.0
*	˵    �� : ���� MODS_Poll()�� MODS_ReciveNew(), MODS_SendWithCRC(), MODS_RxTimeOut(), MODS_AnalyzeApp()
*
*
*********************************************************************************************************
*/
#include "bsp.h"
#include "bsp_uart_fifo.h"
#include "modbus_slave.h"
#include <inttypes.h>
#include <string.h>

uint8_t g_mods_timeout = 0;
uint32_t timer_flag = 0;
uint32_t limit_switch_flag_1 =0;
uint32_t limit_switch_flag_2 =0;
uint32_t c = 0;
MODS_T g_tModS;
VAR_T g_tVar;

/*
*********************************************************************************************************
*	�� �� ��: MODS_Poll
*	����˵��: �������ݰ�. �����������������á�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MODS_Poll(void)
{
	uint8_t wrong_message_report[4]={0xF9, 0xF1, 0x06, 0x01};			//У�������,����λ�����ԣ������ط�
	uint8_t wrong_message_report_bit_number[4]={0xF9, 0xF1, 0x06, 0x02};	 //λ������
	uint8_t wrong_message_report_head[4]={0xF9, 0xF1, 0x06, 0x03};			 //��ͷ����
	//uint16_t addr;
	uint16_t crc1;
	// ����3.5���ַ�ʱ���ִ��MODH_RxTimeOut()������ȫ�ֱ��� g_rtu_timeout = 1; ֪ͨ������ʼ���� 
	if (g_mods_timeout == 0)	
	{
		return;								// û�г�ʱ���������ա���Ҫ���� g_tModS.RxCount 
	}
	//USART1_SendString("\r\n ����MODS_POLL(); \r\n");
	g_mods_timeout = 0;	 					// ���־ 
	
	
	if (g_tModS.RxCount != g_tModS.RxBuf[2])				// ���յ��������ֽ�������
	{
		MODS_SendWithCRC(wrong_message_report_bit_number, 4);
		g_tModS.RxCount = 0;
		return;	
	}
	if (0xF8 != g_tModS.RxBuf[0])				// ���յ��ı�ͷ����
	{
		MODS_SendWithCRC(wrong_message_report_head, 4);
		g_tModS.RxCount = 0;
		return;	
	}
	
	/*
	// վ��ַ (1�ֽڣ� 
	addr = g_tModS.RxBuf[0];				// ��1�ֽ� վ��
	if (addr != UART2_BAUD)		 			// �ж��������͵������ַ�Ƿ����
	{
		goto err_ret;
	}
	 */

	crc1 = sum_check(g_tModS.RxBuf, g_tModS.RxCount);	  	// ����У���
	//printf("%02X",crc1);	  
	if (crc1 != g_tModS.RxBuf[g_tModS.RxCount-1])
	{
		MODS_SendWithCRC(wrong_message_report, 4);
		g_tModS.RxCount = 0;
		return;
	}

	// ����Ӧ�ò�Э��
	if (0xF1 == g_tModS.RxBuf[1]) 
	{	
		MODS_AnalyzeApp();
	}
	else if (0xF2 == g_tModS.RxBuf[1])
	{
		MODS_AnalyzeApp_F2();
	}						

	g_tModS.RxCount = 0;					// ��������������������´�֡ͬ�� 
	
}

/*
*********************************************************************************************************
*	�� �� ��: MODS_ReciveNew
*	����˵��: ���ڽ����жϷ���������ñ����������յ�һ���ֽ�ʱ��ִ��һ�α�������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MODS_ReciveNew(uint8_t _byte)
{
	uint32_t timeout;
	g_mods_timeout = 0;	
	timeout = 35000000 / UART2_BAUD;			// ���㳬ʱʱ�䣬��λus 35000000   ???Ӧ����3500000
	
	// Ӳ����ʱ�жϣ���ʱ����us Ӳ����ʱ��1����ADC, ��ʱ��2����Modbus
	bsp_StartHardTimer(1, timeout, (void *)MODS_RxTimeOut);

	if (g_tModS.RxCount < S_RX_BUF_SIZE)
	{	
		g_tModS.RxBuf[g_tModS.RxCount++]=_byte;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: MODS_SendWithCRC
*	����˵��: ����һ������, �Զ�׷��2�ֽ�CRC
*	��    ��: _pBuf ���ݣ�
*			  _ucLen ���ݳ��ȣ�����CRC��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void MODS_SendWithCRC(uint8_t *_pBuf, uint8_t _ucLen)
{
	uint16_t crc;
	uint8_t buf[S_TX_BUF_SIZE];

	memcpy(buf, _pBuf, _ucLen);
	crc = sum_check(_pBuf, _ucLen);
	//buf[_ucLen++] = crc >> 8;
	//buf[_ucLen++] = crc;
	//USART1_SendString("\r\n ����MODS_SendWithCRC \r\n");
	buf[_ucLen++] = crc;
	RS485_SendBuf(buf, _ucLen);
}


/*
*********************************************************************************************************
*	�� �� ��: MODS_RxTimeOut
*	����˵��: ����3.5���ַ�ʱ���ִ�б������� ����ȫ�ֱ��� g_mods_timeout = 1; ֪ͨ������ʼ���롣
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void MODS_RxTimeOut(void)
{
	g_mods_timeout = 1;
}

/*
*********************************************************************************************************
*	�� �� ��: MODS_AnalyzeApp
*	����˵��: ����Ӧ�ò�Э��, ��������ָ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void MODS_AnalyzeApp(void)
{
	uint8_t txbuf[4] = {0xF9, 0xF1, 0x06, 0x00};		//������������
	uint32_t counter = 0;
	limit_switch_flag_1 = 0;
	limit_switch_flag_2 = 0;
	
	if(g_tModS.RxBuf[3]==0x01)
	{
		counter = (g_tModS.RxBuf[4]/10)*2000;  //������ƿ�һ���10ml������ÿ�����ƿڲ�ͬ����g_tModS.RxBuf[4]�д�����Ҫ��ml������Ϊ50ml��50/10=5sec��5sec * 2000Ϊ����timer��ֵ
	
		while(limit_switch_flag_1!=1)
		{
			 LED1(0);
		}
		limit_switch_flag_1 = 0;

		TIMER_Configuration(counter);//  ���Զ���timer
		TIM_Cmd(TIM4, ENABLE);

		while(timer_flag!=2)
		{
			 Delay();
			 RELAY2(1);
			 LED1(1); 
		}
		LED3(0);//
		timer_flag = 0;
		RELAY2(0);
		LED1(0); 
		MODS_SendWithCRC(txbuf, 4);
	}

	if(g_tModS.RxBuf[3]==0x02)
	{
		counter = (g_tModS.RxBuf[4]/10)*2000;  //������ƿ�һ���10ml������ÿ�����ƿڲ�ͬ����g_tModS.RxBuf[4]�д�����Ҫ��ml������Ϊ50ml��50/10=5sec��5sec * 2000Ϊ����timer��ֵ
	
		while(limit_switch_flag_2!=1)
		{
			 LED2(0);
		}
		limit_switch_flag_2 = 0;

		TIMER_Configuration(counter);//  ���Զ���timer
		TIM_Cmd(TIM4, ENABLE);
		
		while(timer_flag!=2)
		{
			 Delay();
			 RELAY2(1);
			 LED2(1); 
		}
		LED4(0);//
		timer_flag = 0;
		RELAY2(0);
		LED2(0); 
		MODS_SendWithCRC(txbuf, 4);
	}
		
}


/*
*********************************************************************************************************
*	�� �� ��: MODS_AnalyzeApp_F2
*	����˵��: ����Ӧ�ò�Э��, ������ѯ����ָ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void MODS_AnalyzeApp_F2(void)	 
{
	 uint8_t txbuf_0[9] = {0xF9, 0xF2, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	 uint8_t txbuf_1[9] = {0xF9, 0xF2, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
	 //uint8_t txbuf_2[4] = {0xF9, 0xF2, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
	 //F9	F2	0D	XX	XX	XX	XX	XX	XX
	 
	 if(g_tModS.RxBuf[3]==0x00)
	{
		   if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)==0)
		   {
		  	 MODS_SendWithCRC(txbuf_0, 9);
		   }
		   else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)==1)	
		   {
		   	 MODS_SendWithCRC(txbuf_1, 9);
		   }	   
	}
	else if(g_tModS.RxBuf[3]==0x01)
	{
		if(g_tModS.RxBuf[8]==0x01)
		{
			if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)==0)
		   {
		  	 MODS_SendWithCRC(txbuf_0, 9);
		   }
		   else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)==1)	
		   {
		   	 MODS_SendWithCRC(txbuf_1, 9);
		   }
		}
		else
		{
			MODS_SendWithCRC(txbuf_0, 9);
		} 
	}
}

/************************END OF FILE************************************/