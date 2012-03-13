/******************** (c) 2009 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.2 $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
$log:$
******************************************************************************/



#ifndef GPIO_H
#define GPIO_H
                      
#include <stm8_map.h> 

                      
/*---FUNCTIONS---*/
void GPIO_Init(void);

/*---CONSTANTS---*/



#define LED_ON  (GPIOG->ODR &=(u8)~0x08)
#define LED_OFF	(GPIOG->ODR |= 0x08)

#define START		((BitField8_Type*)(&(GPIOF->IDR)))->b4 
#define OK			((BitField8_Type*)(&(GPIOA->ODR)))->b1 
#define FAIL		((BitField8_Type*)(&(GPIOA->ODR)))->b2 
#define ZLUTA		((BitField8_Type*)(&(GPIOE->ODR)))->b5
#define KONCAK	((BitField8_Type*)(&(GPIOD->IDR)))->b7


#endif


/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/

