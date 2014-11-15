/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "std_types.h"

/***************************************************
*		GLOBAL 	VARIABLES
****************************************************/

volatile uint16 pwm;
const uint16	PWM_MIN = 200;
const uint16	PWM_MAX	=	2200;
const uint16	PWM_L1 = 600;
const uint16	PWM_L2 = 1300;
const uint16	PWM_L3 = 1800;
const uint16	PWM_L4 = 2000;
const uint16   DELAY = 300;
/**
*		daylight value   0 = day, 0xff = night
*/
volatile static uint8 initial;


#define WDC_Refresh() (LTCSR |= 0x01) // wdc refresh

/**
*		EEProm location for daylight permanent value
*/
volatile static uint8 EE_Bright@0x1010;

/***********************************************************
*		INTERRUPT RUTINES
***********************************************************/
/**
*			LT oveflow interrupt
*/
volatile @interrupt void LT_OF_Interrupt(void)
{ 
	PADR ^= 0x20;
	LTCSR;
	return;
} 

/**
*			ART oveflow interrupt
*/
volatile @interrupt void AT_OF_Interrupt(void)
{ 
	return;
} 

/**
*			ART compare interrupt
*/
volatile @interrupt void AT_CMP_Interrupt(void)
{  
		DCR0H = (uint8)(pwm >>8 );
		DCR0L = (uint8)(pwm & 0x00ff);
		PWM0CSR;
		WDC_Refresh();
		return;
} 

/**
* 		AWU interrupt
*/
volatile @interrupt void AWU_Interrupt(void)
{  
	uint8 darknes;	
	AWUCSR;
	PADR &= ~0x20;
	while(!(ADCCSR & 0x80));
	darknes = ADCDRH;
	if (darknes <  initial){
		AWUCSR |= 0x01;
		PADR |= 0x20;		
		Halt;
	}else{
		ATCSR |= 0x01;
		PWMCR |= 0x01;		
	}
	return;
} 



/***********************************************************
*			main
***********************************************************/
void main (void)
{
	uint16 analogVal;
	sint16 i;
	uint16 j;
	uint8 darknes;
	uint16 initD;
	
	AVDTHCR = 0x83;		//  fcpu  = frc /16
	RCCR = 0x70;		// 
	/** ports init **/	
	PADR = 0x00;
	PADDR |= 0x21;		
	PAOR  = 0x31;   	// push pull PA0, pullup PA4
	/* external interrupts */
	EICR2 = 0x02;		// PA4-EI3 falling edge
	/** ADC **/
	ADCCSR = 0x02;		// ch 2 = PA2
	ADCCSR |= 0x20;  //ADC ON
	initD = 0;
	
	/** brithness read **/
	if (!(PADR & 0x10)){
		PAOR  &= ~0x10;   // disable interrupts
			// initialize of brightness value   PA 4 == 0	
		for (i = 0;i<8;++i){
		
			while(!(ADCCSR & 0x80));
			initD += ADCDRH;
		}
		initial = (uint8)(initD>>3);
		if (initial > 10 ) initial -=10;
		EECSR |= 0x02;
		EE_Bright = initial;
		EECSR |= 0x01;
		WDC_Refresh();
		while(EECSR & 0x01);
		WDC_Refresh();
		for (i = 0; i< 5;++i){
			PADR |= 0x01;
			for (j = 1800; j>1; --j);
			WDC_Refresh();
				PADR &= ~0x01;
			for (j = 1800; j>1; --j);		
			WDC_Refresh();
		}
	}else {		
		initial = EE_Bright;
	
	}
	/** LIte Timer **/
	//LTCSR |= 0x10;		// int enable
	
	/** AWU **/
	AWUCSR = 0x01;
	AWUPR = 0xff;
		
	/** AT timer **/   	// PWM settings
	ATRH = 0x06;
	ATRL = 0x0A;
	DCR0H = 0x06;
	DCR0L = 0x0B;
	ATCSR = 0x11;				// CMP IE enable
	PWM0CSR = 0x00;
	PWMCR = 0x01;
	pwm = 1550;
	
	
	EnableInterrupts;
	
	do{
		for (i = PWM_MIN; i<PWM_MAX;  ){			
		//	WDC_Refresh();
			for (j = DELAY; j>1; --j);			
			pwm = i+1545;
			if (i < PWM_L1) {i++;}
			else if (i <PWM_L2) {i+=2;}
				else if (i<PWM_L3){ i+=3;}
					else if (i< PWM_L4){ i+=4;}
							else i+=5;										
		}
			
		for (i = PWM_MAX-1; i>= PWM_MIN; ){						
			for (j = DELAY; j>1; --j);			
			pwm = i+1545;
			if (i < PWM_L1) --i;
				else if (i <PWM_L2) i-=2;
					else if (i<PWM_L3) i-=3;
						else if (i<PWM_L4) i-=4;
							else i-=5;						
		}
		if(ADCCSR & 0x80){
			darknes = ADCDRH;
			if (darknes <  initial){
				ATCSR &= ~0x03;
				PWMCR &= ~0x01;
				PADR &= ~ 0x01;
				Halt;
			}
		}	
	}while (1);
}