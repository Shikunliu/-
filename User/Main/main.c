/*******************************************************
**------------------------File Info-------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2017-12-08
** Last Version:        V1.00
** Descriptions:        
**
**----------------------------------------------------------------------------------------------------
** Created by:          Shikun Liu
** Created date:        2017-12-08
** Version:             V1.00
** Descriptions:        秀吧机器人流量控制模块主函数
**
**----------------------------------------------------------------------------------------------------
** Modified by:         	
** Modified date:        
** Version:            
** Descriptions:        
**
*****************************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "hw_config.h"
#include "bsp.h"
//#include "response_function.h"
#include "modbus_slave.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int main(void)
{
  SystemInit();     	//系统初始化, 配置始终，在启动文件里已经被调用
  bsp_Init();			//初始化
  //printf("\r\n USART1测试正常! \r\n");
 	
  while(1)
  {			 
		MODS_Poll();		//Modbus通信
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);   

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************END OF FILE************************************/
