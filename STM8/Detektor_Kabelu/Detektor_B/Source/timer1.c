/******************** (c) 2008 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.1 $
DATE 		: 				$Date: 2009/05/15 09:27:06 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
******************************************************************************/


#include <stm8_map.h>
#include "Timer1.h"

/*****************************************************************************
 * Name : 	
 * Input: 	
 * Output:
 * Description : 
 *	Comments :
 *****************************************************************************/
void TIM1_Init(void)
{      
	TIM1->PSCRH = 	0x3E;		 	// 
	TIM1->PSCRL = 	0x7F;		 	// 
	TIM1->ARRH =  0x07;
	TIM1->ARRL =  0xff;				

//	TIM1->IER = 0x00 | TIM1_IER_UIE;
	
	TIM1->EGR |= TIM1_EGR_UG;
	TIM1->CR2 = 0x00;
	TIM1->CR1 = TIM1_CR1_ARPE;
	TIM1->CR1 |= TIM1_CR1_CEN;				;		// 0 000 010

}



/*****************************************************************************
 * Name : 	   TIMER1_Interrupt
 * Input:
 * Output:  
 * Description :   NOT ACTIVE
 *	Comments :
 *****************************************************************************/   

@far @interrupt void TIM1_UPD_OVF_Interrupt (void)
{
	if ( TIM1->SR1 & TIM1_SR1_UIF){
		
		GPIOH->ODR ^= 0x01;
		TIM1->SR1 &= (u8)~TIM1_SR1_UIF;
	}
}

/*****************************************************************************
 * Name : 	   TIMER3_Interrupt
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/   

u16 TIM1_GetValue(void)
{
	u16 tmp;		
	tmp = (u16)(TIM1->CNTRH << 8);
	tmp += TIM1->CNTRL;
	return tmp;	
}
