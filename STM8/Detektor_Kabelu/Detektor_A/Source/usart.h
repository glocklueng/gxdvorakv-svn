/******************** (c) 2006 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.2 $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $
MODIFICATIONS :
******************************************************************************/


#ifndef USART_H
#define USART_H

/*---FUNCTIONS---*/

void USART_Init(void);
bool USART_GetDataReady(void);
bool USART_IsTransmitFinished(void);
bool USART_GetNextPacket(u8* data);         
bool USART_SendData(u8* stByte);
bool USART_SendBytesMessage(u8 b0, u8 b1, u8 b2, u8 b3, u8 b4);

void USART_TimeoutHandler(void);

/* internal functions */

void putchar(u8 c);   
bool testID(u8 tmpId);



#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

