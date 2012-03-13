/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companion Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/timer_16bit.c,v 1.6.6.4 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.6.6.4 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: timer_16bit.c,v $
	
******************************************************************************/


#include "std_types.h"
#include "debug.h"
#include "timer_16bit.h"    
//#include "ports.h"

/**
 *   counter variables
 */

uint16 	countLED;
uint16	countCnt;
//uint8 	countTimeoutBurst;
volatile uint16 	countTime;
volatile uint16 	countTimeout; //  

/**
 *		counter values       BASE 100 uS
 */   

 		uint16	COUNT_LED =10000; 		//  1s /50ms  10000/500
const uint16 	COUNT_LED_OFF = 10000;
const uint16 	COUNT_LED_ON = 500;
const uint16 	COUNT_CNT = 100;



		
/**
 *   flag if the timer matched preset value
 */
volatile bool ledState;
volatile bool timeoutExpired;
volatile bool timeExpired;
volatile bool checkCnt;
    
/*****************************************************************************
 * Name : 	   TIMER16_Init
 * Input:
 * Output:  
 * Description :   Configure the Timer
 *	Comments :
 *****************************************************************************/   
void TIMER16_Init(void)        
{                              
  
		T16CSR = 0x04; // disable timer
   	T16CLR = 0;           
  	  	
  	  	T16CSR;
	   T16OC2HR = 0xf0;		// only to disble OC2 interrupt before the OC1
   	
   	
		T16OC1HR = 0x01;
		T16CSR;
   	T16OC1LR = 0x70;			// set time 100us   finp = 4 MHz >> 400 imp = 0x190
										// - 4 for reset to 0xFC and -xx for interrupt management

/*      CONTROL REGISTER 1:     7 6 5 4 3 2 1 0
                                X - - - - - - -         ICE: Input Capture Interrupt Enable
                                - X - - - - - -         OCIE: Output Compare Interrupt Enable
                                - - X - - - - -         TOIE: Timer Overflow Interrupt Enable
                                - - - X - - - -         FOLV2: Force Output Compare 2
                                - - - - X - - -         FOLV1: Force Output Compare 1
                                - - - - - X - -         OLVL2: Output Level 2 
                                - - - - - - X -         IEDG1: Input Edge 1
                                - - - - - - - X         OLVL1: Output Level 1
                                0 0 0 0 0 0 0 1                    */
		T16CR1=0x40;                
  
/*      CONTROL REGISTER 2:     7 6 5 4 3 2 1 0
                                X - - - - - - -         OC1E: Output Compare 1 Enable
                                - X - - - - - -         OC2E: Output Compare 2 Enable
                                - - X - - - - -         OPM: One Pulse Mode
                                - - - x - - - -         PWM: Pulse Width Modulation Mode
                                - - - - X - - -         CC1: Timer Clock: 0 fcpu/4 0 fcpu/2 1 fcpu/8 1 ext
                                - - - - - X - -         CC0:              0        1        0        1
                                - - - - - - X -         IEDG2: Input Edge 2
                                - - - - - - - X         EXEDG: External Clock Edge
                                1 0 0 0 0 1 0 0                    */
		T16CR2=0x04; 
  		
  		/*6CSR;
	   T16OC1LR;
	  	
	  	T16CSR;
   	T16OC2LR;     */
   	
		timeoutExpired = false;
		timeExpired = false;
		checkCnt  = false;
		countTimeout = 0;
		countTime = 1;
		countCnt = COUNT_CNT;
		T16CSR &= ~0x4; 
		
}


/*****************************************************************************
 * Name : 	   TIMER16_Interrupt 
 * Input:
 * Output:  
 * Description :   timer Interrupt Service Routine
 *	Comments :
 *****************************************************************************/   
@interrupt void TIMER16_Interrupt(void)
{  
   unsigned char status;  
	
	PDDR |= 0x08;
	
  status = T16CSR;	
	//Trap;
	if(status & OCF1){  
         
 	   	T16OC1LR;        
	   	T16CLR = 0xFC;
	  	
			if (countCnt > 1){
				-- countCnt;
			}else{
				countCnt = COUNT_CNT;
				checkCnt = true;
			}

			if (countTime > 1){
				--countTime;
			}else if (countTime == 1){
				countTime =1;
				timeExpired = true;	
			}
			
			if (countTimeout > 1){
				--countTimeout;
			}else if (countTimeout == 1){
				countTimeout = 0;
				timeoutExpired = true;	
			}
			
			if (++countLED == COUNT_LED){
				if (ledState){		// on - set off
					COUNT_LED = COUNT_LED_OFF;
					ledState = false;
					countLED = 0;
				}else {
					COUNT_LED = COUNT_LED_ON;
					ledState = true;
					countLED = 0;
				}				
			}
			
		
		//	PADR &= ~0x40;
	}else if(status & TOF) {
   	   T16CLR; 
		//	Trap;
   }else if (status & OCF2){
			T16OC2LR;
	}	
	PDDR &= ~0x08;
}


/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description :  
 *	Comments :
 *****************************************************************************/   
void TIMER16_SetTime(uint16 time){     

	countTime = time;
	timeExpired = false;
}


/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description :  
 *	Comments :
 *****************************************************************************/   
bool TIMER16_IsTimeExpired(void){     
	return timeExpired;
}

/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description :  
 *	Comments :
 *****************************************************************************/   
void TIMER16_SetTimeout(uint16 timeout){     

	countTimeout = timeout;
	timeoutExpired = false;
}


/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description :  
 *	Comments :
 *****************************************************************************/   
bool TIMER16_IsTimeoutExpired(void){     
	return timeoutExpired;
}




/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description :  
 *	Comments :
 *****************************************************************************/   
bool TIMER16_GetLEDState(void){     	
	return ledState;	
}



/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description :  
 *	Comments :
 *****************************************************************************/   
bool TIMER16_GetCntState(void){     	
	if (checkCnt){
		checkCnt = false;
		return true;	
	}else{
		return false;
	}
}


/*** (c) 2006  STMicroelectronics ****************** END OF FILE ***/
 


