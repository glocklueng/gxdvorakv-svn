/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/ports.h,v 1.4.2.1 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.4.2.1 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: ports.h,v $
	Revision 1.4.2.1  2009/05/22 06:37:55  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.4  2007/10/25 06:56:50  vaclav dvorak
	*** empty log message ***
	
	Revision 1.3  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/


#ifndef PORTS7_H
#define PORTS7_H
                       
#include "std_types.h"                       
                       
/*---FUNCTIONS---*/

void PORTS_Init(void);

/*---CONSTANTS---*/


/*---HARDWARE CONNECTIONS---*/

#define LED_ON		(PCDR &= ~0x04)
#define LED_OFF	(PCDR |= 0x04)
#define CAN_EN	(((BitField8_Type*)(&PDDR))->b1)	// read write possible
#define CAN_NSTB (((BitField8_Type*)(&PCDR))->b7)	// read write possible
#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

