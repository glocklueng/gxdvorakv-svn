/******************** (c) 2008 STMicroelectronics ****************************
VERSION  : 				$Revision $
DATE 		: 				$Date: 2009/05/15 09:27:06 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $
       	
******************************************************************************/


#ifndef TIM1_H
#define TIM1_H
                      
#include <stm8_map.h>

                      
/*---FUNCTIONS---*/

void TIM1_Init(void);
void PWM_SetFrequency( u16 frequency);
u16 PWM_GetFrequency( void );

/*---CONSTANTS---*/

#endif


/*** (c) 2008  STMicroelectronics ****************** END OF FILE ***/

