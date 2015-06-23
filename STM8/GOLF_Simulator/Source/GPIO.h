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



#define LED_ON  (GPIOE->ODR &=(u8)~0x02)
#define LED_OFF	(GPIOE->ODR |= 0x02)
#define OIL_PRESS ((BitField8_Type*)(&(GPIOE->ODR)))->b3

#endif


/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/

