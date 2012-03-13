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
		GPIOA->DDR = 0x06;
		GPIOA->CR1 = 0x06;
		
		GPIOB->DDR = 0x00;				// 0010 0000
		GPIOB->CR1 = 0x00;
		GPIOB->ODR = 0x00;
		
		GPIOC->DDR = 0x00;				// 0001 1110
		GPIOC->CR1 = 0xFF;
		GPIOC->ODR = 0x00;
		
		GPIOD->ODR = 0x00;
		GPIOD->DDR = 0x00;
    GPIOD->CR1 = 0xFF;

		GPIOE->ODR = 0x00;
		GPIOE->DDR = 0x20;					// 0001 0000
		GPIOE->CR1 = 0x20;
		
		GPIOF->DDR = 0x00;		// 0110 0000
		GPIOF->CR1 = 0x10;		// 0110 0000
		GPIOF->ODR = 0x00;		// 0100 0000
				
		GPIOG->DDR  = 0x08;
		GPIOG->CR1  = 0x08;
				

}       



/*****************************************************************************
 * Name : 	   GIPOD_Interrupt
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/   

@far @interrupt void GPIOD_EI3_Interrupt (void)
{
	
	
}

/*** (c) 2008  STMicroelectronics ****************** END OF FILE ***/










