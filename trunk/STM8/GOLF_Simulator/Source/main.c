/******************** (c) 2009 STMicroelectronics ****************************
VERSION  : 				
DATE 		: 				
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak 

MODIFICATIONS :
/******************** (C) COPYRIGHT 2007 STMicroelectronics *******************
*
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STmicroelectronics SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
*******************************************************************************/


//#include <stdlib.h>
#include <stm8_map.h>


#include "gpio.h"
#include "stm8_can.h"
#include "timer4.h"
#include "timer1.h"
#include "adc.h"
#include "stm8_can.h"

#include "common.h"


typedef struct{
	u8 ID0:1;
	u8 ID1:1;
	u8 D0:1;
	u8 D1:1;
	u8 D2:1;	
} tCAN_MSG_REC;



tCANMsg CAN_TxMsg1;
tCAN_MSG_REC CAN_MsgRecStatus;
tCAN_FLTR_REC CAN_FilterRecStatus;
extern volatile tCANFlag 	Flags;


/**
*		Holds Board status 
*/
BOARD_STATUS_TYPE BoardStatus;

/***** FUNCTION PROTOTYPES ****************************************************/





/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : Conigure of master clock
 *	Comments :  
 *****************************************************************************/ 
void CLK_Init(CLK_TYPE target)
{
	const u8 CLK_DIVIDERS = 0x00;
	
	CLK->ECKR |=  0x01;
	CLK->CKDIVR = CLK_DIVIDERS;								// fCPU = fMASTER = 24 MHz
	if ( CLK->CMSR != target){
		CLK->SWCR = CLK_SWCR_SWEN;				// Enable CLK switch execution
		CLK->SWR = target;									// HSE selected as master CLK
		while (!(CLK->SWCR & CLK_SWCR_SWIF));
		if (CLK->CMSR != target	)			// check for CLK switch finished		
		{
			// error in switching -- reset
		}
	}
	
	CLK->CANCCR = 0x00;		// can divider
}




	
/**
*
*/
void main()
{
	u16 tmp;
	u8 tmp8, tmp8_A;
	static tCANMsg RxMsgBuff;

	CLK_Init(CLK_HSE);  
	disableInterrupts();
	GPIO_Init();	
	TIM4_Init();
//	TIM2_Init();
	TIM1_Init();
	ADC_Init();
	/* Configure CAN - Interface		*/
	
  CAN_Init();												// init CAN - interface
	
	enableInterrupts();	
	
	CAN_Start();
	
	CAN_TxMsg1.Length = 4;
	CAN_TxMsg1.Xtd = false;
	CAN_TxMsg1.rtr = false;
	CAN_TxMsg1.ID = 0x280;
	CAN_TxMsg1.Data[0] =0 ;
	CAN_TxMsg1.Data[1] =0;
	
	
	//PWM_SetFrequency(1);
	do{
		
			
		if (	IsCAN_MSG1_Send()){
				tmp = ADC_GetValue(ADC_REV_CHANEL);
				tmp = tmp *24;
				if ( tmp < 100 ){
					OIL_PRESS = false;
				}else{
					OIL_PRESS = true;
				}
				
				CAN_TxMsg1.Data[3] =(u8)(tmp >> 8) ;
				CAN_TxMsg1.Data[2] =(u8)(tmp & 0x00FF);
				CAN_Write(&CAN_TxMsg1);
		}
		
		if ( IsSpeedAdjustTime()){
				tmp = ADC_GetValue(ADC_SPEED_CHANEL);
				tmp = tmp * 10;
				tmp = tmp/ 34;
				PWM_SetFrequency(tmp);
				// 1023 = 300 Hz
		}
		
	/*	if(	CAN_GetMsg(&RxMsgBuff)== RET_OK){
			
			if (RxMsgBuff.Xtd ){		// EID
				tmp8 =  (u8)(RxMsgBuff.timeStamp >>3) & 0xE0U;
				if (RxMsgBuff.rtr) tmp8 |= 0x10;
				tmp8 |= (RxMsgBuff.Length & 0x0F);
				tmp8_A = (RxMsgBuff.ID>>24) & 0x001f;
				tmp8_A |= (RxMsgBuff.FilterID << 5);
				USART_SendBytesMessage (CAN_MSG_EXT_1, tmp8,(u8)((RxMsgBuff.timeStamp) & 0x00FF), tmp8_A ,(RxMsgBuff.ID>>16) & 0x00ffU);
				
				USART_SendBytesMessage (CAN_MSG_EXT_2, (RxMsgBuff.ID>>8) & 0x00ffU,RxMsgBuff.ID & 0x00ffU,RxMsgBuff.Data[0], RxMsgBuff.Data[1] );
				if (RxMsgBuff.Length > 2)
					USART_SendBytesMessage (CAN_MSG_EXT_3, RxMsgBuff.Data[2], RxMsgBuff.Data[3], RxMsgBuff.Data[4], RxMsgBuff.Data[5]);
				if (RxMsgBuff.Length > 6 )
					USART_SendBytesMessage (CAN_MSG_EXT_4, RxMsgBuff.Data[6], RxMsgBuff.Data[7],0,0);			
			}else{									// standard ID
				tmp8 =  (u8)(RxMsgBuff.timeStamp >>3) & 0xE0U;
				if (RxMsgBuff.rtr) tmp8 |= 0x10;
				tmp8 |= (RxMsgBuff.Length & 0x0F);
				tmp8_A = (RxMsgBuff.ID>>8) & 0x007f;
				tmp8_A |= (RxMsgBuff.FilterID << 3);
				USART_SendBytesMessage (CAN_MSG_STD_1, tmp8,(u8)((RxMsgBuff.timeStamp) & 0x00FF), tmp8_A ,RxMsgBuff.ID & 0x00ff);
				if (RxMsgBuff.Length > 0)
					USART_SendBytesMessage (CAN_MSG_STD_2, RxMsgBuff.Data[0], RxMsgBuff.Data[1], RxMsgBuff.Data[2], RxMsgBuff.Data[3]);
				if (RxMsgBuff.Length > 4 )
					USART_SendBytesMessage (CAN_MSG_STD_3, RxMsgBuff.Data[4], RxMsgBuff.Data[5], RxMsgBuff.Data[6], RxMsgBuff.Data[7]);
			}
		}*/
		
		
		/** LED Flashing **/
		if (GetLedState()){
			LED_ON;
		}else {
			LED_OFF;
		}
		
	} while (1);

}

/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/