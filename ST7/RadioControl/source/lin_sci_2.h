/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/lin_sci_2.h,v 1.3.6.2 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.3.6.2 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: lin_sci_2.h,v $
	Revision 1.3.6.2  2009/05/22 06:37:55  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.3.6.1  2007/12/06 14:32:13  vaclav dvorak
	- comments of files by new	
	Revision 1.3  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/


#ifndef LINSCI2_H
#define LINSCI2_H

#include "comm_commands.h"
/*---FUNCTIONS---*/

void LIN_SCI_2_Init(void);
@stack void putchar(uint8 c);   
@stack _Bool testID(uint8 tmpId);
bool SCI_GetDataReady(void);
bool SCI_IsTransmitFinished(void);
bool SCI_GetNextPacket(uint8* data);         

bool SCI_SendData(uint8* stByte);
bool SCI_SendData_b(uint8 byte0,uint8 byte1,uint8 byte2,uint8 byte3,uint8 byte4);

/*---CONSTANTS---*/

#define SCI2_RX_BUF_COUNT 5  
#define SCI2_TX_BUF_COUNT 5


#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

