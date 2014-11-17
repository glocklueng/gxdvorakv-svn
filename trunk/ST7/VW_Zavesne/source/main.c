/**************** (c) 2002  STMicroelectronics **********************
     
PROJECT  :
COMPILER : 

MODULE  :  main.c
VERSION :  

CREATION DATE : 01.2001 

AUTHOR : CMG 8-bit Micro Application Team 

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

DESCRIPTION :   Main Routine
              
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

MODIFICATIONS :

 ******************************************************************************
 THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. ST MICROELECTRONICS
 SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES
 WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.
 ******************************************************************************

******************************************************************************/

/* Include files */

#include "lib.h"        /* Predifined libraries working at bit level */
#include "std_types.h"
#include "L9952.h"
#include "spi.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

///   variables

extern volatile  L9952_CR0_TYPE L9952_cr0;
extern volatile  L9952_CR1_TYPE L9952_cr1;
extern volatile  L9952_CR2_TYPE L9952_cr2;
extern volatile  L9952_SR0_TYPE L9952_sr0;
extern volatile  L9952_SR1_TYPE L9952_sr1;

uint16 timeout;
uint16 timebase;
const uint16 TIME_BASE_TIME = 10;
uint8 timeExpired;

/**
*
*/
void Port_Init(void)
{
	// io init
	PADR = 0x00;
	PADDR = 0x00;
	PAOR  = 0x00;   // 
	
	
	PBDR = 0x01;					//  SPI CSN = 1
	PBDDR = 0x0B; 				//  0000 1011
	PBOR = 0xFF;					//  1111 1111 
}

/**
lite timer 1ms interrupt
*/
volatile @interrupt void LT_RTC1_Interrupt(void)
{
	LTCSR1;
	if (timeout >0) {
	--timeout;
	}
	
	if (timebase >0 ){
		-- timebase;
	}else{
		timebase = TIME_BASE_TIME;
		timeExpired = true;
	}
	return;
}



/**
*
*/
void main(void)
{ 
	uint16 i;

	Port_Init();
	SPI_Init();
	L9952_RegInit();
	
	//  LITE2 timer set
	LTCSR2 = 0;
	LTCSR1 = 0x10;		// 0001 0010  1ms time base

	
	// clock controll
	//AVDTHCR &= ~ 0xE0;
	//AVDTHCR |= 0x60;  // Fosc - RC/2 = 4MHz

  EnableInterrupts;  
	
	/**  L9952 configuration ***/
	//L9952_cr2.bit.IC1 = 1;	// cyclic with T2
	L9952_cr2.bit.LSOVUV = 1;	// LS ON during OV/UV
	L9952_RefreshRegister(SPI_CR2);		// read out SR0
	
	L9952_cr1.bit.W0 = 1;		// WU1 disabled as a wakeup source
	L9952_cr1.bit.W1 = 1;		// WU2 disabled as a wakeup source
	L9952_cr1.bit.W2 = 1;		// WU3 disabled as a wakeup source
	L9952_cr1.bit.W3 = 1;		// WU4 disabled as a wakeup source
	L9952_cr1.bit.W4 = 1;		// Out1 OLWU disabled as a wakeup source
	L9952_cr1.bit.W5 = 1;		// Out2 OLWU disabled as a wakeup source
	L9952_cr1.bit.W6 = 1;		// Out3 OLWU disabled as a wakeup source
	L9952_cr1.bit.W7 = 1;		// Out1 OLWU disabled as a wakeup source	
	L9952_cr1.bit.U0 = 0;		// PU at WU1
	L9952_cr1.bit.U1 = 0;		// PD at WU2
	L9952_cr1.bit.U2 = 0;		// PD at WU3
	L9952_cr1.bit.U3 = 0;		// PD at WU4	
	L9952_cr1.bit.Looping	= 0;		// DO3,4 = WU3,4
	L9952_cr1.bit.T20 = 0;	// timer 2  50ms/0.1 ms
	L9952_cr1.bit.clr = 1;	// !!! CLEAR STATUS FLAGS	
	L9952_RefreshRegister(SPI_CR1);		// read out SR1
	
	L9952_cr0.bit.HS11 = 1;	// HS out in timer 1 mode
	L9952_cr0.bit.HS21 = 1;	// HS out in timer 1 mode
	L9952_cr0.bit.HS31 = 1;	// HS out in timer 1 mode
	
	L9952_cr0.bit.HS41 = 1;	// HS out in timer 1 mode	
	L9952_cr0.bit.HS40 = 1;	// HS out in timer 2 mode	
	
	L9952_RefreshRegister(SPI_CR0);		// read out SR1
	

  while(1) {            // never ending loop. (<=> jra assembler instruction)
	
	
	
		L9952_RefreshRegister(SPI_CR0);		// read out SR1
		for ( i = 0; i < 0xfffe; ++i);
		L9952_cr2.bit.IC1 = 1;	// cyclic with T2
		L9952_RefreshRegister(SPI_CR2);		// read out SR0
		for ( i = 0; i < 0xfffe; ++i);
		L9952_RefreshRegister(SPI_CR0);		// read out SR1
		for ( i = 0; i < 0xfffe; ++i);
		L9952_cr2.bit.IC1 = 2;	// cyclic with T2
		L9952_RefreshRegister(SPI_CR2);		// read out SR0
		for ( i = 0; i < 0xfffe; ++i);
		L9952_RefreshRegister(SPI_CR0);		// read out SR1
		for ( i = 0; i < 0xfffe; ++i);
		L9952_cr2.bit.IC1 = 3;	// cyclic with T2
		L9952_RefreshRegister(SPI_CR2);		// read out SR0
		for ( i = 0; i < 0xfffe; ++i);
		L9952_RefreshRegister(SPI_CR0);		// read out SR1
		for ( i = 0; i < 0xfffe; ++i);
		L9952_cr2.bit.IC1 = 0;	// cyclic with T2
		L9952_RefreshRegister(SPI_CR2);		// read out SR0
		for ( i = 0; i < 0xfffe; ++i);
		L9952_RefreshRegister(SPI_CR0);		// read out SR1
		for ( i = 0; i < 0xfffe; ++i);
	

  } // while(1) loop                            
} // main loop

/*** (c) 2002  STMcroelectronics ****************** END OF FILE ***/
