/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/timer_16bit.h,v 1.5.6.3 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.5.6.3 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: timer_16bit.h,v $
	
	

******************************************************************************/



#ifndef TIMER16_H
#define TIMER16_H

/*---FUNCTIONS---*/

void TIMER16_Init(void);
//_Bool TIMER16_CounterA(_Bool clear);
	
void TIMER16_SetTimeout(uint16 timeout);  // for sleep mode enter
bool TIMER16_IsTimeoutExpired(void);

void TIMER16_SetTime(uint16 time);	// for CAN message send (100ms)
bool TIMER16_IsTimeExpired(void);

bool TIMER16_GetLEDState(void);
bool TIMER16_GetCntState(void);


/*---CONSTANTS---*/

/*-- VARABLES--*/

/*---CONSTANTS---*/


#endif

/*** (c) 2006  STMicroelectronics ****************** END OF FILE ***/

