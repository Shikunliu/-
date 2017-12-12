#ifndef __HW_CONFIG_H_
#define __HW_CONFIG_H_
#include "stm32f10x_conf.h"






/* BUTTON */
#define RCC_APB2Periph_BUTTON	RCC_APB2Periph_GPIOD
#define GPIO_ButtonPort	GPIOD
#define BUTTON1	GPIO_Pin_8


/* º¯ÊýÉùÃ÷ */

void NVIC_Configuration(void);
void USART_Configuration(void);

#endif
/***************************** (END OF FILE) *********************************/
