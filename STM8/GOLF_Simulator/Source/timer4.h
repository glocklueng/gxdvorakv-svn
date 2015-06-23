/******************** (c) 2008 STMicroelectronics ****************************
VERSION  : 				$Revision $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $
MODIFICATION:
	$Log: timer4.h,v $
	Revision 1.2  2009/09/23 12:16:55  Vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2009/05/15 09:27:06  Vaclav dvorak
	project start
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
******************************************************************************/


#ifndef TIM4_H
#define TIM4_H
                      
#include <stm8_map.h>

                      
/*---FUNCTIONS---*/

void TIM4_Init(void);
bool GetLedState(void);
bool IsCAN_MSG1_Send(void);
bool IsSpeedAdjustTime(void);
bool IsTimeoutExpired(void);
void SetTimeoutTime(const u16 time);  // parameter : T = time * 0.1 ms


/*---CONSTANTS---*/

#endif


/*** (c) 2008  STMicroelectronics ****************** END OF FILE ***/

