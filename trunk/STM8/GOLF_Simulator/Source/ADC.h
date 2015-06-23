/******************** (c) 2009 STMicroelectronics ****************************
VERSION  : 				
DATE 		: 			
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :

******************************************************************************/



#ifndef ADC_H
#define ADC_H

#include <stm8_map.h>


/*---FUNCTIONS---*/

void ADC_Init(void);
const u16 ADC_GetValue(const u8 chanel);
const u8 ADC_GetValue8b(const u8 chanel);


/*---CONSTANTS---*/
// Chanels definition



#define ADC_SPEED_CHANEL 	5
#define ADC_REV_CHANEL	7


#endif


/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/

