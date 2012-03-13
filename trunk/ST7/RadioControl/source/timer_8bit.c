/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/timer_8bit.c,v 1.3 2007/01/15 14:08:36 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.3 $

DATE 		: 				$Date: 2007/01/15 14:08:36 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: timer_8bit.c,v $
	Revision 1.3  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/


#include "std_types.h"
#include "debug.h"
#include "timer_8bit.h"  


  
     
/*****************************************************************************
 * Name : 	   TIMER8_Init
 * Input:
 * Output:  
 * Description :   Configure the Timer
 *	Comments :
 *****************************************************************************/   

void TIMER8_Init(void)
{                     

		T8CSR = 0x04;
      T8CTR = 0;
             
  	   T8CSR;
  		T8OC1R = 0x80;     
	
	   T8CSR;   
   	T8OC2R = 0xF0;   

	 /*      CONTROL REGISTER 1:     7 6 5 4 3 2 1 0
                                X - - - - - - -         ICE: Input Capture Interrupt Enable
                                - X - - - - - -         OCIE: Output Compare Interrupt Enable
                                - - X - - - - -         TOIE: Timer Overflow Interrupt Enable
                                - - - X - - - -         FOLV2: Force Output Compare 2
                                - - - - X - - -         FOLV1: Force Output Compare 1
                                - - - - - X - -         OLVL2: Output Level 2 
                                - - - - - - X -         IEDG1: Input Edge 1
                                - - - - - - - X         OLVL1: Output Level 1
                                0 0 0 0 0 0 0 0                    */
   	T8CR1= 0x01;		// 	  0 0 0 0|0 0 0 1          

/*      CONTROL REGISTER 2:     7 6 5 4 3 2 1 0
                                X - - - - - - -         OC1E: Output Compare 1 Enable
                                - X - - - - - -         OC2E: Output Compare 2 Enable
                                - - X - - - - -         OPM: One Pulse Mode
                                - - - X - - - -         PWM: Pulse Width Modulation Mode
                                - - - - X - - -         CC1: Timer Clock: 0 fcpu/4 0 fcpu/2 1 fcpu/8 1 fosc/8000
                                - - - - - X - -         CC0:              0        1        0        1
                                - - - - - - X -         IEDG2: Input Edge 2
                                - - - - - - - X         EXEDG: External Clock Edge
                                0 0 0 0 0 0 0 0                    */
   	T8CR2= 0x94;		//      1 0 0 1 0 1 0 0
      
		T8CSR = 0x00;
}



/*****************************************************************************
 * Name : 	   TIMER8_Interrupt 
 * Input:
 * Output:  
 * Description :   timer Interrupt Service Routine
 *	Comments :
 *****************************************************************************/   
@interrupt void TIMER8_Interrupt(void)
{  
 
}

/*****************************************************************************
 * Name : 	   TIMER8_
 * Input:
 * Output:  
 * Description :   timer Interrupt Service Routine
 *	Comments :
 *****************************************************************************/   
bool TIMER8_SetDiv(uint8 divNbr)
{
	switch (divNbr){
			case 2:			
				T8CR2 &= ~0x08;			// cpu / 2	= 01
				T8CR2 |= 0x04;
			break; 
			case 4:
				T8CR2 &= ~0x0C;			// cpu / 4  = 00
			break;
			case 8:
				T8CR2 &= ~0x04;			// cpu / 8  = 10
				T8CR2 |= 0x08;
			break;
			case 10:
				T8CR2 |= 0x0C;			// cpu / 8000 = 11
			break;
			default:
			return false;
	}
}

  

/*** (c) 2006  STMicroelectronics ****************** END OF FILE ***/
 


