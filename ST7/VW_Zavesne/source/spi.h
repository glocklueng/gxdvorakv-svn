/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 					
VERSION  : 				
DATE 		: 				
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
******************************************************************************/



#ifndef SPI1_H
#define SPI1_H

#include "std_types.h"

	
/*---FUNCTIONS---*/

void SPI_Init(void);
//_Bool SPI_Send(L9952drv_StatusRegType dataIn ,L9952drv_StatusRegType *dataOut);
void SPI_Send(uint8 *dataIn ,uint8 *dataOut);
//void SPI_SetMirroring(_Bool status);

/*---CONSTANTS---*/

#define Chipselect_HI PBDR |= 0x01
#define Chipselect_LO PBDR &= ~0x01

#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

