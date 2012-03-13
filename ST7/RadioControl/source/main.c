/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				

$Header:  $

MODULE   :  			main.c
VERSION  : 				$Revision: 1.10.2.8 $

DATE 		: 				$Date: 2009/05/28 14:38:12 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: main.c,v $
	
	

******************************************************************************/
									

/* Include files */

#include "std_types.h"
//#include "lin_sci_2.h"
#include "ports.h"
#include "timer_16bit.h"
#include "timer_8bit.h"
//#include "SPI.h"
//#include "comm_commands.h"
//#include "pwm_ar_timer_8bit.h" 
#include "interrupt_contr.h"
#include "can.h" 
#include "user.h"
//#include "adc_10bit.h"

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
// *************************  C O N S T A N T S ********************************




// *************************  T Y P E S  ***************************************
/**
*	wdc parameters -- EEPROM record 0
*/


//-------------------------CAN------------------------------
typedef struct
{
  canuint16 stdid;
  canuint16 extid;
  canuint8  dlc;
  canuint8  data[8];
}data_buff;

data_buff user_rx_struct;     /* user receive structure */
tCanMsgOject user_tx_struct;  /* user transmmit structure using CanMsgTransmit()
                                 service */   




// *************************  V A R I A B L E S ********************************

uint8 CAN_Send_Light_ON(void){
	
	user_tx_struct.stdid = MAKE_STD_ID(0x635); //* fill the stdid part /
	user_tx_struct.extid = 0x0000;
	user_tx_struct.dlc =3; //* set the dlc 
	user_tx_struct.data[0]= 0x20;
	user_tx_struct.data[1]= 0x64;		
	user_tx_struct.data[2]= 0x00;	
	return CanMsgTransmit(&user_tx_struct);	
}	

uint8 CAN_Send_Light_OFF(void){
	
	user_tx_struct.stdid = MAKE_STD_ID(0x635); //* fill the stdid part /
	user_tx_struct.extid = 0x0000;
	user_tx_struct.dlc =3; //* set the dlc 
	user_tx_struct.data[0]= 0x0;
	user_tx_struct.data[1]= 0x0;		
	user_tx_struct.data[2]= 0x00;
	return CanMsgTransmit(&user_tx_struct);
}

uint8 CAN_Send_KL15_ON(void){
	
	user_tx_struct.stdid = MAKE_STD_ID(0x271); //* fill the stdid part /
	user_tx_struct.extid = 0x0000;
	user_tx_struct.dlc =1; //* set the dlc 
	user_tx_struct.data[0]= 0x07;		
	return CanMsgTransmit(&user_tx_struct);	
}

uint8 CAN_Send_KL15_OFF(void){
	
	user_tx_struct.stdid = MAKE_STD_ID(0x271); //* fill the stdid part /
	user_tx_struct.extid = 0x0000;
	user_tx_struct.dlc =1; //* set the dlc 
	user_tx_struct.data[0]= 0x10;		
	return CanMsgTransmit(&user_tx_struct);	
}

/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/ 
void main(void)
{  
//	uint8 txDataReset[]={0x02,0x01,0x01,0x00,FW_REVISION};	// reset packet
	
	uint8		 result[5];
	sint16 	 i;
	bool 			test ;
	uint8 		tmpValueA,tmpValueB;
	uint8 		contactA_SM_State;
	uint8 		contactA_Value;		// light
	uint8 		contactB_SM_State;
	uint8 		contactB_Value;		// KL15
	
	contactA_SM_State = 0;
	contactA_Value = false;
	contactB_SM_State = 0;
	contactB_Value = false;
	
	//Trap;
	DisableInterrupts;
	TIMER16_Init();
	PORTS_Init();
	ITC_Init();
		
	CAN_EN = 1;
	CAN_NSTB = 1;
	
	EnableInterrupts;  
	
	
	
	CanInitPowerOn();   	// 
	CanInit(0);             
	
	TIMER16_SetTime ( 1000);
	TIMER16_SetTimeout(65500);

	while(1) {   
	
		if (TIMER16_GetCntState()){
			switch (contactA_SM_State){
				case 0:				
				case 1:
				case 2:
					if (tmpValueA){		// ulozeno 1
						if (PBDR & bit2) { // cnt = 1
							++contactA_SM_State;						
						}
						else {
							tmpValueA = false;
							contactA_SM_State = 0;						
						}						
					}else{								// ulozeno 0
						if (!(PBDR & bit2)){
							++contactA_SM_State;
						}
						else{
							tmpValueA = true;
							contactA_SM_State = 0;													
						}
					}					
				break;
				case 3:
					if (tmpValueA){
						contactA_Value = true;
					}else {
						contactA_Value = false;
					}
					contactA_SM_State = 0;		
				break;
				default:
					contactA_SM_State = 0;		
				break;
			}
			
			switch (contactB_SM_State){
				case 0:				
				case 1:
				case 2:
					if (tmpValueB){		// ulozeno 1
						if (PDDR & bit0) { // cnt = 1
							++contactB_SM_State;						
						}
						else {
							tmpValueB = false;
							contactB_SM_State = 0;						
						}						
					}else{								// ulozeno 0
						if (!(PDDR & bit0)){
							++contactB_SM_State;
						}
						else{
							tmpValueB = true;
							contactB_SM_State = 0;													
						}
					}					
				break;
				case 3:
					if (tmpValueB){
						contactB_Value = true;
					}else {
						contactB_Value = false;
					}
					contactB_SM_State = 0;		
				break;
				default:
					contactB_SM_State = 0;		
				break;
			}			
		}
	
	
		if (TIMER16_IsTimeExpired()){
			TIMER16_SetTime ( 1000);
			if (contactA_Value){
				while (CAN_Send_Light_ON()== KCANTXFAILED );		
			}else {
				while (CAN_Send_Light_OFF()== KCANTXFAILED);	
			}
			if (contactB_Value){
				while (CAN_Send_KL15_ON()== KCANTXFAILED);		
			}else {
				while(CAN_Send_KL15_OFF()== KCANTXFAILED);	
			}			
		}
		
		if (contactA_Value || contactB_Value){
			TIMER16_SetTimeout(65500);
		}
	
		if (TIMER16_IsTimeoutExpired()){
				// goto HALT mode
				DisableInterrupts;	
				// ******************* SLEEP ********************
				LED_OFF;
				CAN_EN = 0;
				CAN_NSTB = 0;
				MCCSR &= ~0x02;   
				Halt; 
				///  WU from HALT by contact
				EnableInterrupts;
				LED_ON;
				CAN_EN = 1;
				CAN_NSTB = 1;
				TIMER16_SetTimeout(65500);
		}

	
		if (TIMER16_GetLEDState()){
			LED_ON;	
		}else {			
			LED_OFF;	
		}	
		
	}
}

/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/
void delay(uint16 aDelay){		
   	for (;aDelay>0;aDelay--){ 		 	
  		}
} 

/*** (c) 2006  STMcroelectronics ****************** END OF FILE ***/










