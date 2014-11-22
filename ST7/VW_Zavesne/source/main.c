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

#define WDC_TIME 10U
#define MOTOR_TOUT  2500U
#define MOTOR_TOUT_LOCK  4000U
//#define KONTAKT_TOUT 1000U
#define MOTOR_CCPT   1000U			// 1000ms
#define SLEEP_TIMEOUT		5000U
#define FS_INDICATION_TOUT 10000U
#define SAFETY_LOCK_TOUT	6000U

///   variables

extern volatile  L9952_CR0_TYPE L9952_cr0;
extern volatile  L9952_CR1_TYPE L9952_cr1;
extern volatile  L9952_CR2_TYPE L9952_cr2;
extern volatile  L9952_SR0_TYPE L9952_sr0;
extern volatile  L9952_SR1_TYPE L9952_sr1;

/*
	PON		--- po zapnuti, behem diagnotiky, dokud neni pozadavek na odjsiteni	
	RELEASE  ---  odjistovani
	WAIT  --- cekani v odjsitenem stavu pred zajistenim
	LOCK  --- zajistovani
	WAIT_TO_SLEEP --- zajisteno, ceka se na podminky pro STB mod
	GO_TO_SLEEP	  --- ceka na vyprseni timeout and jde to standby modu
	ERROR_UNSAFE  --- stav kdy neni znam stav, nebo je odjisteno
	ERROR_FS --- nelze odjistit, ale je detekovan zajiseny stav	
*/
enum  {PON, RELEASE, WAIT, LOCK, WAIT_TO_SLEEP, GO_TO_SLEEP, 
												ERROR_UNSAFE, ERROR_FS} SM_State;
volatile uint16 timeout;
volatile uint16 timeout2;
uint16 timebase;
const uint16 TIME_BASE_TIME = 10;
uint8 timeExpired;
volatile uint8 wdcTimeBase;
volatile uint8 WDCExpired;
uint8 coldStart;
uint8 safetyLock;
uint8 safetyLockCounter;

uint8 RC_CAL @ 0xDEE0;
uint8 RC_CAL_lo @ 0xDEE1;


/**
*
*/

void Port_Init(void)
{
	// io init
	PADR = 0x00;
	PADDR = 0x01;
	PAOR  = 0x01;   // 
	
	
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
	PADR |= 0x01;
	if (timeout >0) {
	--timeout;
	}
	
	if ( timeout2 > 0){
	-- timeout2;	
	}
	
	if (timebase >0 ){
		-- timebase;
	}else{
		timebase = TIME_BASE_TIME;
		timeExpired = true;
	}
	
	if (wdcTimeBase >= WDC_TIME-1){
		WDCExpired = true;
	}else{
		++wdcTimeBase;
	}
	PADR &= ~0x01;
		return;
}

/**
*
*/
void ResetWDCTimer(void)
{
		wdcTimeBase = 0;
		WDCExpired = false;
}

/**
*
*/
void Delay(uint16 time)
{
	for ( ;time >0; --time)	{
		;
	}
	return;
}

/**
*
*/
void main(void)
{ 
	uint16 i;

	RCCR = 0xE7;	//RC_CAL;	 RC calibration
	//SICSR &= ~0x60;
	//SICSR |= RC_CAL_lo & 0x60;
	Port_Init();
	SPI_Init();
	L9952_RegInit();
	coldStart = false;
	safetyLock = false;
	safetyLockCounter = 0;
		
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
	if ( L9952_sr0.bit.coldStart){
		coldStart = true;
	}
	
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
	
	// power on diagnostika
	
	L9952_cr0.bit.HS12 = 0;L9952_cr0.bit.HS11 = 0;L9952_cr0.bit.HS10 = 1; // out 1 ON
	L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 0;L9952_cr0.bit.HS20 = 0; // out 2 
	L9952_cr0.bit.HS32 = 0;L9952_cr0.bit.HS31 = 0;L9952_cr0.bit.HS30 = 0; // out 3 
	L9952_cr0.bit.HS42 = 0;L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
	
	L9952_RefreshRegister(SPI_CR0);		// read out SR0

	L9952_RefreshWDC();
	ResetWDCTimer();
	
	
	SM_State = PON;
	
	/*
		WU1   --- tlacitko (LS)  0 = aktivni
		WU2   --- svetlo kufru 12V input,  1 = aktivni
		WU3   --- koncak - zajisteno, 1 = aktivni
		WU4   --- koncak odjsiteno,   1 = aktivni
	
		Out1  --- napajeni tlacitka (cyclic, pro cteni ve standby, static v activ modu)
		Out2  --- LED v tlacitku  ( on, off, PWM)
		Out4  --- napajeni koncaku - static
		
	*/

  while(1) {            // never ending loop. (<=> jra assembler instruction)
	
		if ( WDCExpired){
			L9952_RefreshWDC();
			ResetWDCTimer();
		}
		
		//SM_State = PON;
		
		switch (SM_State){
			case PON:
				safetyLock= false;
				L9952_cr0.bit.rel1 = 0;
				L9952_cr0.bit.rel2 = 0;			
				L9952_cr0.bit.HS42 = 0;L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
				L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 0;L9952_cr0.bit.HS20 = 0; // out2-LED-OFF 
				L9952_RefreshRegister(SPI_CR0);	// read out SR0				
				if (( L9952_sr0.bit.WU3 == 0) && coldStart){  // neni zajisteno
					timeout = MOTOR_TOUT_LOCK;
					SM_State = LOCK;	
				}else{
					SM_State = WAIT_TO_SLEEP;	
				}
			break;
			case RELEASE:		// motor bezi doku kontak nebo timeout			
				L9952_cr0.bit.rel1 = 1;
				L9952_cr0.bit.rel2 = 0;			
				L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 0;L9952_cr0.bit.HS20 = 1; // out2-LED-ON 
				L9952_cr0.bit.HS42 = 0;L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
				L9952_RefreshRegister(SPI_CR0);		// read out SR0
												
				if ( L9952_sr0.bit.WU4 == 1){
						if ( L9952_sr0.bit.WU3 == 0){
							// released - OK
							L9952_cr0.bit.rel1 = 0;
							L9952_cr0.bit.rel2 = 0;
							L9952_RefreshRegister(SPI_CR0);		// motor stop
							timeout = MOTOR_CCPT;					
							SM_State = WAIT;								
						}else{
							// oba kontakty jsou aktivni -  neznama poloha 
							SM_State = ERROR_UNSAFE;		
						}					
				}else	if ( timeout == 0){	// motor timeout expired
						if ((L9952_sr0.bit.WU3 == 0) && (L9952_sr0.bit.WU4 == 0)){
							// neznama poloha - 
							SM_State = ERROR_UNSAFE;								
						}else{
							// WU3 = 1, WU 4 = 0 - LOCKED - motor nebezi
							timeout2 = FS_INDICATION_TOUT;
							SM_State = ERROR_FS;			
						}
				}			
			break;
			case WAIT://////////////////////////////////////////////////////////////
					if ( timeout == 0){
							L9952_cr0.bit.HS42 = 0;L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
							L9952_cr0.bit.rel1 = 0;
							L9952_cr0.bit.rel2 = 1;
							L9952_RefreshRegister(SPI_CR0);		// motor bezi - zamyka
					
							timeout = MOTOR_TOUT_LOCK;					
							SM_State = LOCK;										
					}else{
							L9952_cr0.bit.rel1 = 0;
							L9952_cr0.bit.rel2 = 0;
							L9952_RefreshRegister(SPI_CR0);		// motor stop
					}
			break;
			case LOCK://////////////////////////////////////////////////////////////
				L9952_cr0.bit.rel1 = 0;
				L9952_cr0.bit.rel2 = 1;			
				L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 0;L9952_cr0.bit.HS20 = 1; // out2-LED-ON 
				L9952_cr0.bit.HS42 = L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
				L9952_RefreshRegister(SPI_CR0);		// read out SR0
							
				if (( L9952_sr0.bit.WU3 == 1)&& ( L9952_sr0.bit.WU4 == 0)){
							// lockes - OK
							L9952_cr0.bit.rel1 = 0;
							L9952_cr0.bit.rel2 = 0;
							L9952_RefreshRegister(SPI_CR0);		// motor stop														
							SM_State = WAIT_TO_SLEEP;								
				}else	if ( timeout == 0){	// motor timeout expired
						SM_State = ERROR_UNSAFE;								
						// WU3 = 0, WU4 = 0 - neznama poloha 
						// WU3 = 0, WU4 = 1 - motor nebezi, odemceno
						// WU3 = 1, WU4 = 1 - neznama poloha
				}							
			break;
			case WAIT_TO_SLEEP:
				L9952_cr0.bit.rel1 = 0;
				L9952_cr0.bit.rel2 = 0;			
				L9952_cr0.bit.HS42 = L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
				L9952_cr0.bit.HS32 = 0;L9952_cr0.bit.HS31 = 1;L9952_cr0.bit.HS30 = 0; // out 3 
				L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 0;L9952_cr0.bit.HS20 = 0; // out2-LED-OFF 
				L9952_RefreshRegister(SPI_CR0);	
				
				if ((L9952_sr0.bit.WU3 == 1) && (L9952_sr0.bit.WU4 == 0)){
					// locked
					if ((L9952_sr0.bit.WU1 == 1) && (L9952_sr0.bit.WU2 == 0)){
						timeout = SLEEP_TIMEOUT;
						SM_State = GO_TO_SLEEP;						
					}
				}else{
					SM_State = LOCK;
				}
				if ((L9952_sr0.bit.WU1 == 0) && (L9952_sr0.bit.WU2== 1)){
					
					L9952_cr0.bit.HS42 = 0;L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
					L9952_cr0.bit.rel1 = 1;
					L9952_cr0.bit.rel2 = 0;
					L9952_RefreshRegister(SPI_CR0);		// motor bezi
					
					timeout = MOTOR_TOUT;					
					SM_State = RELEASE;					
				}
			break;
			case GO_TO_SLEEP:
				L9952_cr0.bit.HS32 = 0;L9952_cr0.bit.HS31 = 0;L9952_cr0.bit.HS30 = 1; // out 3 
				L9952_RefreshRegister(SPI_CR0);	
				Delay(10);
				
				if ((L9952_sr0.bit.WU1 == 1) && (L9952_sr0.bit.WU2 == 0)){
					if (timeout ==0){
							L9952_cr0.bit.HS12 = 0;L9952_cr0.bit.HS11 = 0;L9952_cr0.bit.HS10 = 0; // out 1 off
							L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 0;L9952_cr0.bit.HS20 = 0; // out 2 off
							L9952_cr0.bit.HS32 = 0;L9952_cr0.bit.HS31 = 0;L9952_cr0.bit.HS30 = 0; // out 3 off 
							L9952_cr0.bit.HS42 = 0;L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 0; // out 4 off
							L9952_cr0.bit.rel1 = 0;
							L9952_cr0.bit.rel2 = 0;
							L9952_RefreshRegister(SPI_CR0);		// read out SR0
																					
							L9952_cr1.bit.W0 = 1;		// WU1 disabled as a wakeup source
							L9952_cr1.bit.W1 = 0;		// WU2 enabled as a wakeup source
							L9952_cr1.bit.W2 = 1;		// WU3 disabled as a wakeup source
							L9952_cr1.bit.W3 = 1;		// WU4 disabled as a wakeup source
							L9952_cr1.bit.W4 = 1;		// Out1 OLWU disabled as a wakeup source
							L9952_cr1.bit.W5 = 1;		// Out2 OLWU disabled as a wakeup source
							L9952_cr1.bit.W6 = 1;		// Out3 OLWU disabled as a wakeup source
							L9952_cr1.bit.W7 = 1;		// Out1 OLWU disabled as a wakeup source	
							L9952_cr1.bit.U0 = 1;		// PU at WU1
							L9952_cr1.bit.U1 = 0;		// PD at WU2
							L9952_cr1.bit.U2 = 0;		// PD at WU3
							L9952_cr1.bit.U3 = 0;		// PD at WU4	
							L9952_cr1.bit.Looping	= 0;		// DO3,4 = WU3,4
							L9952_cr1.bit.T20 = 0;	// timer 2  50ms/0.1 ms
							L9952_cr1.bit.clr = 1;	// !!! CLEAR STATUS FLAGS	
							L9952_RefreshRegister(SPI_CR1);		// read out SR1
											
							Delay(100);							
							L9952_cr0.bit.goVbat = 1;
							L9952_RefreshRegister(SPI_CR0);		// read out SR0
							while(1);
					}
				}else{
					SM_State = WAIT_TO_SLEEP;	
				}			
			break;
			case ERROR_UNSAFE:							
				L9952_cr1.bit.T12 = 0;L9952_cr1.bit.T11 = 0;L9952_cr1.bit.T10 = 0;	// timer 0.2ms
				L9952_cr1.bit.T13 = 1; // on time 20 ms
				L9952_cr1.bit.clr = 1;	// !!! CLEAR STATUS FLAGS	
				L9952_RefreshRegister(SPI_CR1);		// read out SR1
								
				if (( L9952_sr0.bit.WU3 == 1) && ( L9952_sr0.bit.WU4 == 0)){
					// locked - OK
					L9952_cr0.bit.rel1 = 0;
					L9952_cr0.bit.rel2 = 0;
					L9952_RefreshRegister(SPI_CR0);		// motor stop														
					SM_State = PON;								
									
				}
				if ((L9952_sr0.bit.WU2 == 1)&& (L9952_sr0.bit.WU1 == 0 )){  // tlacitko stisknute
						if ( safetyLock){
							if ( timeout == 0){								
								if ( safetyLockCounter < 2){
									SM_State = LOCK;
									timeout = MOTOR_TOUT_LOCK;
									safetyLock= false;
									++safetyLockCounter;								
								}
							}
						}else{// prvni beh po stisku tlacitka
							safetyLock= true;
							timeout = SAFETY_LOCK_TOUT;
						}								
				}else{
					timeout = 0;
					safetyLock= false;				
				}
				L9952_cr0.bit.rel1 = 0;				
				L9952_cr0.bit.rel2 = 0;						
				L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 1;L9952_cr0.bit.HS20 = 0; // out2-LED-ON_TMR1
				L9952_cr0.bit.HS42 = L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
				L9952_RefreshRegister(SPI_CR0);		// read out SR0
				
				if (L9952_sr0.bit.WU2 == 0){
					// forced sleep
							L9952_cr0.bit.HS12 = 0;L9952_cr0.bit.HS11 = 0;L9952_cr0.bit.HS10 = 0; // out 1 off
							L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 0;L9952_cr0.bit.HS20 = 0; // out 2 off
							L9952_cr0.bit.HS32 = 0;L9952_cr0.bit.HS31 = 0;L9952_cr0.bit.HS30 = 0; // out 3 off 
							L9952_cr0.bit.HS42 = 0;L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 0; // out 4 off
							L9952_cr0.bit.rel1 = 0;
							L9952_cr0.bit.rel2 = 0;
							L9952_RefreshRegister(SPI_CR0);		// read out SR0
																					
							L9952_cr1.bit.W0 = 1;		// WU1 disabled as a wakeup source
							L9952_cr1.bit.W1 = 0;		// WU2 enabled as a wakeup source
							L9952_cr1.bit.W2 = 1;		// WU3 disabled as a wakeup source
							L9952_cr1.bit.W3 = 1;		// WU4 disabled as a wakeup source
							L9952_cr1.bit.W4 = 1;		// Out1 OLWU disabled as a wakeup source
							L9952_cr1.bit.W5 = 1;		// Out2 OLWU disabled as a wakeup source
							L9952_cr1.bit.W6 = 1;		// Out3 OLWU disabled as a wakeup source
							L9952_cr1.bit.W7 = 1;		// Out1 OLWU disabled as a wakeup source	
							L9952_cr1.bit.U0 = 1;		// PU at WU1
							L9952_cr1.bit.U1 = 0;		// PD at WU2
							L9952_cr1.bit.U2 = 0;		// PD at WU3
							L9952_cr1.bit.U3 = 0;		// PD at WU4	
							L9952_cr1.bit.Looping	= 0;		// DO3,4 = WU3,4
							L9952_cr1.bit.T20 = 0;	// timer 2  50ms/0.1 ms
							L9952_cr1.bit.clr = 1;	// !!! CLEAR STATUS FLAGS	
							L9952_RefreshRegister(SPI_CR1);		// read out SR1
											
							Delay(100);							
							L9952_cr0.bit.goVbat = 1;
							L9952_RefreshRegister(SPI_CR0);		// read out SR0
							while(1);					
				}
			break;
			case ERROR_FS:
				L9952_cr0.bit.rel1 = 0;				
				L9952_cr0.bit.rel2 = 0;				
				L9952_cr0.bit.HS22 = 0;L9952_cr0.bit.HS21 = 1;L9952_cr0.bit.HS20 = 0; // out2-LED-ON_TMR1
				L9952_cr0.bit.HS42 = L9952_cr0.bit.HS41 = 0;L9952_cr0.bit.HS40 = 1; // out 4 ON
				L9952_RefreshRegister(SPI_CR0);		// read out SR0
				L9952_cr1.bit.T12 = 0;L9952_cr1.bit.T11 = 0;L9952_cr1.bit.T10 = 1;	// timer 0.2ms
				L9952_cr1.bit.T13 = 1; // on time 20 ms
				L9952_cr1.bit.clr = 1;	// !!! CLEAR STATUS FLAGS	
				L9952_RefreshRegister(SPI_CR1);		// read out SR1
				if (timeout2 == 0){
					SM_State = PON;
				}
			break;
			default:			
				SM_State = PON;
			break;			
		}// case
  } // while(1) loop                            
} // main loop

/*** (c) 2002  STMcroelectronics ****************** END OF FILE ***/
