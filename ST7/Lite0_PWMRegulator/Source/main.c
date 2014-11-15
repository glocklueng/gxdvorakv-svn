/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "std_types.h"

const uint16 PWM_MIN_OFF = 30;
const uint16 PWM_MIN_ON = 40;
const uint16 PWM_START =55;

main()
{
	uint16 analogVal;
	uint16 i;
	
	
	
	PADR = 0x00;
	PADDR = 0x21;
	PAOR  = 0x01;   // push pull PA0
	
	AVDTHCR &= ~ 0xE0;
	AVDTHCR |= 0x20;
	// PWM settings
	//ATCSR = 0x08;  // LT as a clock source
	ATCSR = 0x10;
	ATRH = 0x00;
	ATRL = 0x00;
	
	DCR0H = 0x07;
	DCR0L = 0xFF;
	PWM0CSR = 0x00;
	PWMCR = 0x01;  // enable output (PA0)
	
	// ADC
	ADCCSR = 0x42;   // ch2   stop  speed
	
	ADCCSR |= 0x20;		//start adc
	
	LTCSR |= 0x01; // wdc refresh
	do{
		
		if (ADCCSR & 0x80){
		PADR |= 0x20;
			//analogVal = ADCDRL;
			analogVal = ADCDRH;  // read only uper 8 bits
			LTCSR |= 0x01; // wdc refresh		
		PADR &= ~0x20;			
			
		}		
		if (PWM0CSR & 0x01){  // PWM update
		/*	 if (analogVal < PWM_MIN_OFF) { 
				analogVal = PWM_MIN_OFF;
				PWMCR = 0x00;
				PADR &= ~0x01;
			}else if ((analogVal < PWM_START)&&(analogVal > PWM_MIN_ON )){
				analogVal = PWM_START; 
				PWMCR = 0x01;				
			}else {
				PWMCR = 0x01;
			}*/
			if (analogVal < PWM_MIN_OFF) { 
				analogVal = 2;
				//PWMCR = 0x00;
			//	PADR &= ~0x01;
			//	PADR &= ~0x01;
			}else if (analogVal < PWM_START){
				analogVal = PWM_START;
				analogVal  *= 16;	
			}else{
				analogVal  *= 16;	
			}
			
			DCR0H = (uint8)(analogVal >> 8);
			DCR0L = (uint8)(analogVal & 0x00ff);
		}
		
		
	}while (1);
}