/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: C:/CVS_REPOSITORY/CompanionAppBoard/ST7/source/L9952.c,v 1.6 2007/10/25 06:56:50 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.6 $

DATE 		: 				$Date: 2007/10/25 06:56:50 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: L9952.c,v $
	Revision 1.6  2007/10/25 06:56:50  vaclav dvorak
	*** empty log message ***
	
	Revision 1.5  2007/04/05 13:46:49  vaclav dvorak
	- added Get global error status function
	
	Revision 1.4  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.3  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/05/05 12:07:08  vaclav dvorak
	- Changed Header
	- corrected PWM2 control - Current measuremen didn't work on rev. 1.3.
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/

#include "std_types.h"
#include "debug.h"    
#include "L9952.h"
#include "L9952drv.h"
#include "spi.h"  
#include "string.h"  
#include "lin_sci_2.h"
#include "comm_commands.h"
#include "timer_16bit.h"
#include "ports.h"  
#include "lib.h"        /* Predifined libraries working at bit level */
   

/**
/* 	check if WDC trigger alowed  - set by eeprom value in init procedure
*/
extern bool L9952WdcTriggerDisable;	
/**
*		int mode of L9952GXP
*/
extern bool L9952GXPIntMode;


/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/    
void  L9952_ChipInit(){
		L9952drv_StatusRegType tmp;
		
	/*	L9952drv_GetStatus1(&tmp);
		SCI_SendData_r(0x52,L9952_C_SR1,tmp);	
	*/	
		L9952drv_GetStatus0(&tmp);
		SCI_SendData_r(0x52,L9952_C_SR0,tmp);			
		
		L9952drv_GetStatus1(&tmp);
		SCI_SendData_r(0x52,L9952_C_SR1,tmp);	

}

/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/    
void  L9952_SendTestCmd(){
	
	L9952drv_StatusRegType tmp;
				
	L9952drv_ReadControl0(&tmp);
	L9952drv_WRControl0(&tmp);	
}


/*****************************************************************************
 * Name : 	 L9952_SetRegister  
 * Input:
 * Output:  
 * Description :   Set the L9952 register value and send it to the L9952 via SPI
 *	Comments :
 *****************************************************************************/    
void L9952_SetRegister(unsigned char regNumber ,unsigned char *value){

	L9952drv_StatusRegType reg;
	reg = (L9952drv_StatusRegType)((L9952drv_StatusRegType)value[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)value[1]<<8)
             + (L9952drv_StatusRegType)value[2];
				 
   switch (regNumber){
   	case CR0:  			
   		L9952drv_WRControl0(&reg);			
	    	break;
	  	case CR1:
	  	  	L9952drv_WRControl1(&reg);			
	    	break;
	  	case CR2:
			L9952drv_WRControl2(&reg);			
	    	break;	  	
	}
}
 

/*****************************************************************************
 * Name : 	 
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/    
void L9952_GOV1Standby(void){
	
	int delay;
	L9952drv_StatusRegType tmp;
	
	
	L9952drv_GetStatus1(&tmp);
	SCI_SendData_r(0x52,L9952_C_SR1,tmp);	
	
/*	if (!(tmp  && 0x00010000)){ 
		while (!TIMER16_IsWdWindowOpen());

		TIMER16_ResetWDC();
		if (!L9952WdcTriggerDisable){				
			L9952drv_WdgTrigger();				
		}
		L9952drv_GetStatus1(&tmp);
		SCI_SendData_r(0x52,L9952_C_SR1,tmp);	
		
	}else{
		while (!TIMER16_IsWdWindowOpen());

		TIMER16_ResetWDC();
		L9952drv_WdgTrigger();				
		L9952drv_GetStatus1(&tmp);
		SCI_SendData_r(0x52,L9952_C_SR1,tmp);	
		
		while (!TIMER16_IsWdWindowOpen());

		TIMER16_ResetWDC();
		L9952drv_WdgTrigger();				
		L9952drv_GetStatus1(&tmp);
		SCI_SendData_r(0x52,L9952_C_SR1,tmp);	
	
		
	}*/
	while (!TIMER16_IsWdWindowOpen());

	TIMER16_ResetWDC();
	L9952drv_WdgTrigger();				
	
	LED_OFF;
	SCI_SendData_b(0x02,0x03,0x01,0,0);	// message - V1 standby mode
	L9952drv_SetStandbyMode(L9952DRV_STANDBYMODE_V1);	
	for (delay = 0 ;delay<1000;delay++){ 		 	
	}	
	
	LED_5V1_ON;
	
	
	
//	SCI1CR2 &= ~RIE;      
//	SCI1CR2 &= ~(TE | RE);
		
	ADCCSR &= ~ADON;  	// ADC OFF
	
	PWMCR	=	0x00; // PWM OFF
//	PADDR|= 0x1E;
//	PAOR |= 0x1E;			// PWM outs to push-pull
//	PAOR &= ~0x1E;			// set 0 to all PWM outs	
	
	PDOR |= bit1;        // interrupt on LIN RX enable	
	
	if (L9952GXPIntMode) PCOR |= bit2;
		else (PCOR &= ~bit2);
	
	DisableInterrupts;	
	//Chipselect_LO;
	// ******************* SLEEP ********************
	MCCSR &= ~0x02;   
	
   Halt; 
	
	// ******************  wakeup ********************
//	Chipselect_LO;
	PCOR &= ~bit2;
	PDOR &= ~bit1;        // interrupt on LIN RX disable	
//	ITC_Init();
	
	EnableInterrupts;	
	LED_ON;	
	LED_5V1_OFF;
	
	TIMER16_ResetWDC();
	// adc ON  -  not used ADC
	SCI_SendData_b(0x02,0x03,0x00,0,0); // message RUN mode
	

	// diagnostics info
		
	L9952drv_GetStatus0(&tmp);
	SCI_SendData_r(0x52,L9952_C_SR0,tmp);			
	
	L9952drv_GetStatus1(&tmp);
	SCI_SendData_r(0x52,L9952_C_SR1,tmp);	

	
	
}
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/    
void L9952_SetVReg1CurrentMonitor(uint8 value){
	
	L9952drv_StatusRegType reg;
	L9952drv_ReadControl2(&reg);
	
	if (value == 1 ){
		reg |= 0x100000;
	}else{
		reg &= ~ 0x100000;
	}
	
	L9952drv_WRControl2(&reg);		
}
	
 
/*** (c) 2006  STMicroelectronics ****************** END OF FILE ***/
