/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: C:/CVS_REPOSITORY/CompanionAppBoard/ST7/source/L9952.h,v 1.3 2007/01/15 14:08:36 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.3 $

DATE 		: 				$Date: 2007/01/15 14:08:36 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: L9952.h,v $
	Revision 1.3  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/05/05 12:07:08  vaclav dvorak
	- Changed Header
	- corrected PWM2 control - Current measuremen didn't work on rev. 1.3.
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/
 

#ifndef L9952_H
#define L9952_H    

#include "spi.h"   


#define CR0	0
#define CR1	1
#define CR2	2


// *---FUNCTIONS---*/
void  L9952_ChipInit(void);
void 	L9952_SetRegister(uint8 regNumber ,uint8 *value);   
void L9952_GOV1Standby(void);
void  L9952_SendTestCmd(void);

void L9952_SetVReg1CurrentMonitor(uint8 value);
 

#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/
