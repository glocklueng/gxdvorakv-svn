/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/timer_8bit.h,v 1.3 2007/01/15 14:08:36 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.3 $

DATE 		: 				$Date: 2007/01/15 14:08:36 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: timer_8bit.h,v $
	Revision 1.3  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/



#ifndef TIMER8_H
#define TIMER8_H     


/*---FUNCTIONS---*/

void TIMER8_Init(void);  
bool TIMER8_SetDiv(uint8 divNbr);

#endif

/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

