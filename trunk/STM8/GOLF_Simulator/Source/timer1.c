/******************** (c) 2008 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.1 $
DATE 		: 				$Date: 2009/05/15 09:27:06 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
******************************************************************************/


#include <stm8_map.h>
#include "Timer1.h"



const u32 FOSC=16000000;
volatile u8 PWM1_DC = 50;

/**
*		Holds Board status - mirror of extern variable in "main.c"
*/
extern BOARD_STATUS_TYPE BoardStatus;

/*****************************************************************************
 * Name : 	TIM2_Init
 * Input: 	
 * Output:
 * Description : Configure the SPI
 *	Comments :
 *****************************************************************************/
void TIM1_Init(void)
{ 
	
	
	//TIM1->PSCR = 	128;			// 128
	//TIM1->ARRH = (u8)(counterValue>>8);
	//TIM1->ARRL = (u8)(counterValue & 0x00FF);
		
	PWM_SetFrequency(0);
	
	TIM1->IER = 0x00;
	
	TIM1->CCMR1 = 0x40;			// inactive mode  ch1
	TIM1->CCMR2 = 0x40;			// inactive mode  ch2
	TIM1->CCMR3 = 0x40;			// inactive mode  ch3
	TIM1->CCMR4 = 0x68;			// PWM1 mode  ch4
	
	TIM1->CCER1	= 0;
	TIM1->CCER2	= TIM1_CCER2_CC4E;		// only PWM chanel 1
	TIM1->BKR |= 0x80;
	
	
	TIM1->EGR |= TIM1_EGR_UG;
	TIM1->CR1 = TIM1_CR1_ARPE |TIM1_CR1_CEN;				;		// 0 000 010
	
		
	
}




/*****************************************************************************
 * Name : 	PWM_SetFrequency
 * Input: 	frequency  (0...65535 Hz)   0 = approx. 0.1Hz
 * Output:
 * Description : Configure the PWM frequency
 *	Comments :
 *****************************************************************************/

void PWM_SetFrequency( u16 frequency)
{
	u16 tmp_prsc;
	u16 tmp_cnt;
	u32 tmp_div;   // osc/ freq
	bool ug = false;
			
	if (frequency == 0){
		TIM1->PSCRH = 	0xFF;		
		TIM1->PSCRL = 	0xFF;				
		TIM1->ARRH = 0xFF;
		TIM1->ARRL = 0xFF;		
	}else{
		if (TIM1->PSCRH > 0x00 ) ug = true;
		tmp_div = FOSC/frequency;
		
		// INT( div /  65535)+1
		tmp_prsc = tmp_div/65536;
		tmp_prsc++;
		
		tmp_cnt = tmp_div/tmp_prsc;
		
		tmp_prsc--;
		
		TIM1->ARRH = (u8)(tmp_cnt >> 8);
		TIM1->ARRL = (u8)(tmp_cnt & 0x00FF);	
		TIM1->PSCRH = (u8)(tmp_prsc >> 8);		
		TIM1->PSCRL = (u8)(tmp_prsc & 0x00FF);		
		// duty update
		tmp_cnt >>= 1;
		
		TIM1->CCR4H =	(u8)(tmp_cnt >> 8); 		// duty 1			
		TIM1->CCR4L = (u8)(tmp_cnt & 0x00FF);						
		
	}

	if (ug) {
		TIM1->EGR |= TIM1_EGR_UG;	
	}	
}

/*****************************************************************************
 * Name : 	PWM_GetFrequency
 * Input: 	
 * Output:				frequency  (0...65535 Hz)   0 = approx. 0.1Hz
 * Description : return the PWM frequency
 *	Comments :
 *****************************************************************************/

u16 PWM_GetFrequency( void )
{
	u16 tmpFreq;
	u16 tmp_prsc;
	u16 tmp_cnt;
	
	tmp_cnt = (u16)(TIM1->ARRH<<8)+TIM1->ARRL;
	tmp_prsc = (u16)(TIM1->PSCRH<<8)+TIM1->PSCRL;
	if (tmp_cnt > 0 && tmp_prsc > 0)	tmpFreq = FOSC/tmp_cnt/tmp_cnt;
	else tmpFreq = 0xFFFF;
	return (tmpFreq); 
}