/******************** (c) 2008 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.2 $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATION:
	$Log: timer4.c,v $
		

******************************************************************************/


#include <stm8_map.h>
#include "Timer4.h"
#include "usart.h"

const u16 LED_ON_TIME 	=	500; 
const u16 LED_OFF_TIME 	= 9500;
const u16 CAN_MSG1_TIME = 100;
const u16 SPEED_ADJ_TIME = 500;

volatile u16 ledCounter;
volatile bool ledState;

volatile u16 CAN_MSG1_counter;
volatile bool CAN_MSG1_state;


volatile u16 SpeedAdjust_counter;
volatile bool SpeedAdjust_state;


volatile u16 timeoutCounter;
volatile bool timeoutState;




/*****************************************************************************
 * Name : 	TIM4_Init
 * Input: 	
 * Output:
 * Description : Configure the Timer 4
 *	Comments :
 *****************************************************************************/
void TIM4_Init(void)
{      
		TIM4->PSCR = 0x04;           // fmaster / 16
		TIM4->ARR = 100;          	// auto reload register			fMASTER = 16MHz		-> 100us
		TIM4->IER |= TIM4_IER_UIE;	// interrupt enable
		TIM4->CR1=0x81;							// timer enable	
		
		ledCounter = LED_ON_TIME;
		CAN_MSG1_counter = CAN_MSG1_TIME;
		SpeedAdjust_counter= SPEED_ADJ_TIME;
}




/*****************************************************************************
 * Name : 	   TIMER4_Interrupt
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/   

@far @interrupt void TIM4_UPD_OVF_Interrupt (void)
{  

		TIM4->SR1 = 0;
		
		if (!--ledCounter){
			if (ledState){	
				ledCounter = LED_OFF_TIME;
				ledState = false;
			}else {
				ledCounter = LED_ON_TIME;
				ledState = true;				
			}
		}
		if ( timeoutCounter ){
			if (--timeoutCounter  == 0) {
				timeoutState = true;
			}			 
		}
	
		if (!--CAN_MSG1_counter){
			CAN_MSG1_counter = CAN_MSG1_TIME;
			CAN_MSG1_state = true;
		}	
		
		if (!--SpeedAdjust_counter){
			SpeedAdjust_counter = SPEED_ADJ_TIME;
			SpeedAdjust_state = true;
		}			

}

/*****************************************************************************
 * Name : 
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/   
bool GetLedState(void)
{
	return ledState;
}
/*****************************************************************************
 * Name : 
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/
bool IsCAN_MSG1_Send(void)
{
	if (CAN_MSG1_state){
			CAN_MSG1_state = false;
		return true;
	}else return false;
	
}
/*****************************************************************************
 * Name : 
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/
bool IsSpeedAdjustTime(void)
{
	if (SpeedAdjust_state){
			SpeedAdjust_state = false;
		return true;
	}else return false;
	
}


/*****************************************************************************
 * Name : 
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/   
void SetTimeoutTime(const u16 time)
{
	timeoutCounter = time;
	timeoutState = false;
}


/*****************************************************************************
 * Name : 
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/   
bool IsTimeoutExpired(void)
{
	return timeoutState;	
}

/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/