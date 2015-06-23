/******************** (c) 2008 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.2 $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
******************************************************************************/


#include <stm8_map.h>
#include "gpio.h"

/*****************************************************************************
 * Name : 	
 * Input: 	
 * Output:
 * Description :
 *	Comments :
 *****************************************************************************/
void GPIO_Init(void)
{      
		GPIOA->ODR = 0x00;
		GPIOA->DDR = 0x00;
		GPIOA->CR1 = 0x00;
		
		GPIOB->DDR = 0x00;				// 0010 0000
		GPIOB->CR1 = 0x00;
		GPIOB->ODR = 0x00;
		
		GPIOC->ODR = 0x00;
		GPIOC->DDR = 0x10;
    GPIOC->CR1 = 0x10;
		
		GPIOD->ODR = 0x00;
		GPIOD->DDR = 0x02;
    GPIOD->CR1 = 0x02;

		GPIOE->ODR = 0x00;
		GPIOE->DDR = 0x0A;					// 0001 0000
		GPIOE->CR1 = 0x0A;
		
		GPIOG->ODR = 0x01;
		GPIOG->DDR = 0x01;					// 0001 0000
		GPIOG->CR1 = 0x01;
		GPIOG->CR2 = 0x02;

}       

/*** (c) 2008  STMicroelectronics ****************** END OF FILE ***/










