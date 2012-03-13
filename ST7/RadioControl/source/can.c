/*
*******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : can.c
Group            : MicroController Group
Author           : MCD Application Team
Date First Issued: 25/11/03   

********************************Documentation**********************************
Purpose - This file contains the CAN driver source code. 
This file must not be changed by the application.

********************************RevisionHistory********************************
_______________________________________________________________________________
Date : 25/11/03                                                Release : Ver1.0
    
******************************************************************************/
//#include "can_hr.h"        

#include "std_types.h"
#include "debug.h"
#include "can.h"        
#include "user.h"

#define CanSavePg()     (Can_Page = CAN_CPSR)
#define CanRestorePg()  (CAN_CPSR = Can_Page)

volatile canuint8 Can_MailBox_Handle[NO_OF_TX_MAILBOX];
volatile canuint8 Can_Page;
volatile canuint8 *Rx_Ptr;
volatile canuint8 *Tx_Ptr;

/******************************************************************************
Can Driver Functions
******************************************************************************/

/******************************************************************************
Function Name     :  CaninitPowerOn
Input Parameters  :  None
Output Parameters :  None
Description       :  This service initialises the CAN driver internal variables.
Indication and Confirmation flags are reset. Tx/Rx buffers are cleared.  
Comments          : The function shall be called before any other service of 
the driver.
******************************************************************************/
void CanInitPowerOn( void)
{
	unsigned char idx,jdx;
	for(idx=0;idx<SIZE_OF_CONF_FLAGS;idx++)
		Can_Conf_Flags[idx] = 0x00;
 for(idx=0;idx<SIZE_OF_IND_FLAGS;idx++)
		Can_Ind_Flags[idx] = 0x00;
 for(idx=0;idx<SIZE_OF_OVF_FLAGS;idx++)
		Can_Ovf_Flags[idx] = 0x00;  
	for(idx=0;idx<NO_OF_TX_HANDLES;idx++)
	{
		for(jdx=0;jdx<Tx_Dlc[idx];jdx++) 
			Tx_Data_Ptr[idx][jdx]= 0;
	}
 for(idx=0;idx<NO_OF_RX_HANDLES;idx++)
	{
		for(jdx=0;jdx<Rx_Dlc[idx];jdx++) 
			Rx_Data_Ptr[idx][jdx]= 0;
	}
	Can_MailBox_Handle[0] = MAILBOXFREE;
	Can_MailBox_Handle[1] = MAILBOXFREE;
}

/******************************************************************************
Function Name     :  Caninit
Input Parameters  :  initObject - Selected Initialisation Mode.
Output Parameters :  None
Description       :  This service initialises the CAN Controller registers with
the values stored in the init table corresponding to the <initObject>. Pending
transmit requests within the CAN controller are deleted. Receive FIFO is 
released.   
Comments          : The function shall be called after CanInitPowerOn()
and before any other services of the driver.
******************************************************************************/
void CanInit(CanInitHandle init_handle)
{
	CanGlobalInterruptDisable();
	CanCanInterruptDisable();
	CanSavePg();
	
/* Abort the pending transmit requests */
	CAN_CPSR = CAN_TXMB0_PG;
	CAN_MCSR |= MCSR_ABRQ;	
	
	CAN_CPSR = CAN_TXMB1_PG;
	CAN_MCSR |= MCSR_ABRQ;

/* Release the Receive FIFO */
	while(CAN_CRFR & CRFR_FMP01)
	{
	  CAN_CRFR = CRFR_RFOM;
	}
	
	/* Leaving the sleep mode */
	CAN_CMCR &= (unsigned char)~CMCR_SLEEP;
	while(CAN_CMSR & CMSR_SLAK);
	
	/* Entering the initialization mode */
	CAN_CMCR |= CMCR_INRQ;
	while(!CAN_CMSR & CMSR_INAK);
	
	CAN_CMCR |= CMCR_TXFP | CMCR_RFLM;
	CAN_CMCR |= CMCR_NART;
  /* Deactivate all the filters */
	CAN_CPSR = CAN_CTRL_PG ; 
	CAN_CFCR0 = 0x00;
	CAN_CFCR1 = 0x00;
	CAN_CFCR2 = 0x00;
	
  /* CAN bit timing registers */
	CAN_CBTR0 = CBTR0_Init[init_handle];     /*CAN Bit timing registers*/
	CAN_CBTR1 = CBTR1_Init[init_handle];
	
	CAN_CFMR0 = CFMR0_Init[init_handle];     /*CAN filter Mode register */
	CAN_CFMR1 = CFMR1_Init[init_handle];
	
	CAN_CPSR = CAN_FILTER01_PG;              /*Select filter 0:1 Page */
	CAN_CFxR0 = CF0R0_Init[init_handle];  
	CAN_CFxR1 = CF0R1_Init[init_handle]; 	
	CAN_CFxR2 = CF0R2_Init[init_handle]; 
	CAN_CFxR3 = CF0R3_Init[init_handle]; 
	CAN_CFxR4 = CF0R4_Init[init_handle]; 
	CAN_CFxR5 = CF0R5_Init[init_handle]; 
	CAN_CFxR6 = CF0R6_Init[init_handle]; 
	CAN_CFxR7 = CF0R7_Init[init_handle]; 
	
	CAN_CFyR0 = CF1R0_Init[init_handle];  
	CAN_CFyR1 = CF1R1_Init[init_handle];
	CAN_CFyR2 = CF1R2_Init[init_handle];
	CAN_CFyR3 = CF1R3_Init[init_handle];
	CAN_CFyR4 = CF1R4_Init[init_handle];
	CAN_CFyR5 = CF1R5_Init[init_handle];
	CAN_CFyR6 = CF1R6_Init[init_handle];
	CAN_CFyR7 = CF1R7_Init[init_handle];
	
	CAN_CPSR = CAN_FILTER23_PG;            /* select filter 2:3 Page */
	CAN_CFxR0 = CF2R0_Init[init_handle];  
	CAN_CFxR1 = CF2R1_Init[init_handle]; 
	CAN_CFxR2 = CF2R2_Init[init_handle]; 
	CAN_CFxR3 = CF2R3_Init[init_handle]; 
	CAN_CFxR4 = CF2R4_Init[init_handle]; 
	CAN_CFxR5 = CF2R5_Init[init_handle]; 
	CAN_CFxR6 = CF2R6_Init[init_handle]; 
	CAN_CFxR7 = CF2R7_Init[init_handle]; 
	
	CAN_CFyR0 = CF3R0_Init[init_handle];  
	CAN_CFyR1 = CF3R1_Init[init_handle];
	CAN_CFyR2 = CF3R2_Init[init_handle];
	CAN_CFyR3 = CF3R3_Init[init_handle];
	CAN_CFyR4 = CF3R4_Init[init_handle];
	CAN_CFyR5 = CF3R5_Init[init_handle];
	CAN_CFyR6 = CF3R6_Init[init_handle];
	CAN_CFyR7 = CF3R7_Init[init_handle];
	
	CAN_CPSR = CAN_FILTER45_PG ;           /* select filter 4:5 Page */
	CAN_CFxR0 = CF4R0_Init[init_handle]; 
	CAN_CFxR1 = CF4R1_Init[init_handle]; 
	CAN_CFxR2 = CF4R2_Init[init_handle]; 
	CAN_CFxR3 = CF4R3_Init[init_handle]; 
	CAN_CFxR4 = CF4R4_Init[init_handle]; 
	CAN_CFxR5 = CF4R5_Init[init_handle]; 
	CAN_CFxR6 = CF4R6_Init[init_handle]; 
	CAN_CFxR7 = CF4R7_Init[init_handle]; 
	
	CAN_CFyR0 = CF5R0_Init[init_handle];  
	CAN_CFyR1 = CF5R1_Init[init_handle];
	CAN_CFyR2 = CF5R2_Init[init_handle];
	CAN_CFyR3 = CF5R3_Init[init_handle];
	CAN_CFyR4 = CF5R4_Init[init_handle];
	CAN_CFyR5 = CF5R5_Init[init_handle];
	CAN_CFyR6 = CF5R6_Init[init_handle];
	CAN_CFyR7 = CF5R7_Init[init_handle];
	
	CAN_CPSR = CAN_CTRL_PG ;              /* select config/diagnosis Page */
	
	CAN_CFCR0= CFCR0_Init[init_handle];   /* CAN filter config register */
	CAN_CFCR1= CFCR1_Init[init_handle]; 
	CAN_CFCR2= CFCR2_Init[init_handle]; 
	
	/* Leaving the init mode */
	do {
		CAN_CMCR &= (unsigned char)(~CMCR_INRQ);
		Trap;
	}while(CAN_CMSR & CMSR_INAK);
  
	CanRestorePg();
	CanCanInterruptRestore();
	CanGlobalInterruptRestore();
}

/******************************************************************************
Function Name     :  CanGetStatus
Input Parameters  :  None
Output Parameters :  KCANHWISSLEEP - CAN controller is in sleep mode
                     KCANHWISBUSOFF - CAN controller entered BusOff state
                     KCANHWISPASSIVE - Error Passive limit has been reached
                     KCANHWISWARNING - Error Warning limit has been reached 
Description       :  This service returns the current status of the CAN 
                     controller.  
******************************************************************************/
canuint8 CanGetStatus( void)
{
	unsigned char status;
	CanSavePg();
	CAN_CPSR = CAN_CTRL_PG;
	if(CAN_CMSR & CMSR_SLAK)
 {
  CanRestorePg();
		return((canuint8)(KCANHWISSLEEP));
 } 
	else if(CAN_CESR & CESR_BOFF)
 {
		CanRestorePg();
  return((canuint8)(KCANHWISBUSOFF));
 } 
	else if(CAN_CESR & CESR_EPVF)
 {
		CanRestorePg();
  return((canuint8)(KCANHWISPASSIVE));
 }
	else if(CAN_CESR & CESR_EWGF)
 {
		CanRestorePg();
  return((canuint8)(KCANHWISWARNING));
 }
	else
 { 
		CanRestorePg();
  return(0);
 }
}

/******************************************************************************
Function Name     :  CanSleep
Input Parameters  :  None
Output Parameters :  KCANFAILED - If Sleep mode not entered
                     KCANOK - If Sleep mode entered
Description       :  This service puts the controller into the sleep mode. 
                     This reduces the power consumption of the CAN controller. 
******************************************************************************/
canuint8 CanSleep( void)
{
	if((CAN_CTPR) & (CTPR_TME0 | CTPR_TME1))
	{
		CAN_CMCR |= CMCR_AWUM;
		CAN_CMCR |= CMCR_SLEEP;
		while( !(CAN_CMSR & CMSR_SLAK));
		return((canuint8)(KCANOK));
	}
	else 
		return((canuint8)(KCANFAILED));
}

/******************************************************************************
Function Name     :  CanWakeup
Input Parameters  :  None
Output Parameters :  KCANOK - Sleep Mode left
Description       :  This service puts the CAN controller into the normal 
                     operating mode. 
******************************************************************************/
canuint8 CanWakeup( void)
{
	CAN_CMCR &= (canuint8)(~CMCR_SLEEP);
	while( CAN_CMSR & CMSR_SLAK);
	return( KCANOK);
}

/******************************************************************************
Function Name     :  CanGlobalInterruptDisable
Input Parameters  :  None
Output Parameters :  None
Description       :  This service disables the interrupt by setting the global 
                     interrupt flag of the microcontroller. 
******************************************************************************/
void CanGlobalInterruptDisable( void)
{
	DisableInterrupts;
}

/******************************************************************************
Function Name     :  CanGlobalInterruptRestore
Input Parameters  :  None
Output Parameters :  None
Description       :  This service enables the interrupt by clearing the global 
                     interrupt flag of the microcontroller.
******************************************************************************/
void CanGlobalInterruptRestore( void)
{
	EnableInterrupts;
}

/******************************************************************************
Function Name     :  CanCanInterruptDisable
Input Parameters  :  None
Output Parameters :  None
Description       :  This service disables all CAN interrupts by changing the 
                     CAN interrupt control flags.
******************************************************************************/
void CanCanInterruptDisable( void)
{
	CanSavePg();
	{
		CAN_CIER = 0x00; 
		CAN_CPSR = CAN_CTRL_PG; 		
		CAN_CEIER = 0x00;
	}
	CanRestorePg();
}

/******************************************************************************
Function Name     :  CanCanInterruptRestore
Input Parameters  :  None
Output Parameters :  None
Description       :  This service enables all CAN interrupts by changing the 
                     CAN interrupt control flags
******************************************************************************/
void CanCanInterruptRestore( void)
{
	CanSavePg();
	{
		CAN_CIER = CIER_WKUIE | CIER_FOVIE | CIER_FFIE | CIER_FMPIE | CIER_TMEIE;
		CAN_CPSR = CAN_CTRL_PG;
		CAN_CEIER = CEIER_ERRIE | CEIER_LECIE | CEIER_BOFIE |CEIER_EPVIE|CEIER_EWGIE;
	} 
	CanRestorePg();
}

/******************************************************************************
Function Name     :  CanTransmit
Input Parameters  :  tx_handle - Selected transmit Handle
Output Parameters :  KCANTXOK - If the transmit request is accepted by the CAN 
                     driver.
                     KCANTXFAILED- If the transmit request is not accepted by 
                     the CAN driver.
Description       :  This service initiates the transmission within the CAN 
                     controller for the CAN message referenced by <tx_handle>. 
Comments          :  This service shall not be called when the CAN driver is in
                     stop or sleep mode.
******************************************************************************/
canuint8 CanTransmit( CanTransmitHandle tx_handle)
{  
 canuint8 idx;
 
	CanGlobalInterruptDisable();
	CanSavePg();
	if(tx_handle < NO_OF_TX_HANDLES){
		
		if(CAN_CTPR & CTPR_TME0) {
			Can_MailBox_Handle[0] = tx_handle;
			CAN_CPSR = CAN_TXMB0_PG;
		} else if(CAN_CTPR & CTPR_TME1){
			Can_MailBox_Handle[1] = tx_handle;
			CAN_CPSR = CAN_TXMB1_PG;
		}else	{
			CanRestorePg();
			CanGlobalInterruptRestore();
			return(KCANTXFAILED);
		}
	 
		CAN_MDLC = Tx_Dlc[tx_handle];
		if(CAN_MDLC <= MAX_DLC_LEN){
			CAN_MIDR01 = Tx_Stdid[tx_handle];
			if(CAN_MIDR01 & EXT_ID_MASK){
				CAN_MIDR23 = Tx_Extid[tx_handle];
			} 
			Tx_Ptr = Tx_Data_Ptr[tx_handle];
			for(idx=0;idx<CAN_MDLC;idx++)	{
				CAN_MDAR[idx] = Tx_Ptr[idx];
			}
			CAN_MCSR |= MCSR_TXRQ;                   /* Transmit Request */
			CanRestorePg();
			CanGlobalInterruptRestore(); 
			return(KCANTXOK);
		}
	}
	CanRestorePg();
	CanGlobalInterruptRestore();
	return(KCANFAILED);
} 

/******************************************************************************
Function Name     :  CanCancelTransmit
Input Parameters  :  tx_handle - Selected transmit Handle
Output Parameters :  None
Description       :  This service cancels a transmit request by making an Abort
                     Request. 
*******************************************************************************/
void CanCancelTransmit(CanTransmitHandle tx_handle)
{
	CanGlobalInterruptDisable();
	CanSavePg();
	if(Can_MailBox_Handle[0] == tx_handle) 
	{
		Can_MailBox_Handle[0] == CANMSGCANCEL;
		CAN_CPSR = CAN_TXMB0_PG;
		CAN_MCSR |= MCSR_ABRQ;                      /* make abort request */
	}
	else if( Can_MailBox_Handle[1] == tx_handle)
	{
		Can_MailBox_Handle[1] == CANMSGCANCEL;
		CAN_CPSR = CAN_TXMB1_PG;
		CAN_MCSR |= MCSR_ABRQ;
	}
	CanRestorePg();
	CanGlobalInterruptRestore();
}

/******************************************************************************
Function Name     :  CanMsgTransmit
Input Parameters  :  txData - Pointer to structure which contains about CAN-Id,
                     CAN-DLC,CAN-Frame Data.
Output Parameters :  KCANTXOK - Request is accepted by CAN driver.
                     KCANTXFAILED - Request is not accepted by CAN driver. 
Description       :  This service initiates the transmission for the message 
                     referenced by <txData>.
Comments          :  This service shall not be called when the CAN driver is in
                     stop or sleep mode.
******************************************************************************/
canuint8 CanMsgTransmit(tCanMsgOject *txData)
{
 canuint8 idx;
	CanGlobalInterruptDisable();
	CanSavePg();
	if(CAN_CTPR & CTPR_TME0){
		Can_MailBox_Handle[0] = CANMSGTRANSMIT;
		CAN_CPSR = CAN_TXMB0_PG;
	}else	{
		CanRestorePg();
		CanGlobalInterruptRestore();
		return(KCANTXFAILED);
	}
	
	CAN_MDLC = txData->dlc;
	if(CAN_MDLC <= MAX_DLC_LEN){
		CAN_MIDR01 = txData->stdid; 
		if(CAN_MIDR01 & EXT_ID_MASK)
			CAN_MIDR23 = txData->extid;
		for(idx=0;idx<CAN_MDLC;idx++)
			CAN_MDAR[idx] = txData->data[idx];
		CAN_MCSR |= MCSR_TXRQ;                   /* Transmit Request */
	} else	{
		CanRestorePg();
		CanGlobalInterruptRestore();
		return(KCANTXFAILED);
	}
	CanRestorePg();
	CanGlobalInterruptRestore(); 
	return(KCANTXOK); 
} 

/******************************************************************************
Function Name     :  CanCancelMsgTransmit
Input Parameters  :  None
Output Parameters :  None
Description       :  This service cancels a transmit request requested by the 
                     service CanMsgTransmit( ). 
******************************************************************************/
void CanCancelMsgTransmit( void)
{
	CanGlobalInterruptDisable();
	CanSavePg();
	if(Can_MailBox_Handle[0] == CANMSGTRANSMIT) 
	{
		Can_MailBox_Handle[0] == CANMSGCANCEL;
		CAN_CPSR = CAN_TXMB0_PG;
		CAN_MCSR |= MCSR_ABRQ;
	}
	CanRestorePg();
	CanGlobalInterruptRestore();
}

/******************************************************************************
Function Name     :  CanRx_ISR
Input Parameters  :  None
Output Parameters :  None
Description       :  This service handles the receive FIFO interrupt. Received 
                     message (CAN-ID, CAN-DATA) is copied into the Rx buffer 
                     corresponding to the message received.  
******************************************************************************/
@interrupt void CanRx_ISR(void)
{
	static canuint8 filter_match_index,data_len=0;
	canuint8 idx;
 
	CanGlobalInterruptDisable();
	CanSavePg();	
	if(CAN_CRFR & CRFR_FOVR)
	 CAN_CRFR |= CRFR_FOVR;                /* clear the FIFO FOVR bit */
	else if(CAN_CRFR & CRFR_FULL)
		CAN_CRFR |= CRFR_FULL;                /* clear the FIFO FULL bit */
	while(CAN_CRFR & CRFR_FMP01)
	{
	 CAN_CPSR = CAN_FIFO_PG;               /* Select Rx_FIFO page */
	 //Trap;
		filter_match_index = CAN_MFMI;
		if(filter_match_index != 0){
				Trap;
		}
		if(filter_match_index < NO_OF_RX_HANDLES)
		{
		 if((Can_Ind_Flags[filter_match_index/8])&(Ind_Mask[filter_match_index % 8]))
			{
    Can_Ovf_Flags[filter_match_index/8] |= Ovf_Mask[filter_match_index%8]; 
   }
			data_len = CAN_MDLC;
			if((data_len == Rx_Dlc[filter_match_index]) && (data_len != 0))
			{
				Rx_Stdid[filter_match_index] = CAN_MIDR01;
				Rx_Extid[filter_match_index] = CAN_MIDR23;
				Can_Ind_Flags[filter_match_index/8] |= Ind_Mask[filter_match_index%8];
				Rx_Ptr = Rx_Data_Ptr[filter_match_index];
				for(idx=0;idx<data_len;idx++)
				{
					Rx_Ptr[idx]= CAN_MDAR[idx];
				}
			}
			CAN_CRFR |= CRFR_RFOM;
		}
	}
	CanRestorePg();
	CanGlobalInterruptRestore();
}

/******************************************************************************
Function Name     :  CanTx_ISR
Input Parameters  :  None
Output Parameters :  None
Description       :  This service handles the wakeup, error and transmit 
                     mailbox empty interrupts. 
******************************************************************************/
@interrupt void CanTx_ISR(void)
{
	canuint8 handle;
	if(CAN_CMSR & CMSR_ERRI)
		CAN_CMSR = CMSR_ERRI;
	if(CAN_CMSR & CMSR_WKUI)
		CAN_CMSR = CMSR_WKUI;
	if(CAN_CTSR & CTSR_TXOK0)
	{
		 CAN_CTSR |= CTSR_RQCP0;           /* clear the request completed 
                                        request for mailbox0 */
		 if((Can_MailBox_Handle[0] != CANMSGCANCEL) 
     && (Can_MailBox_Handle[0] != CANMSGTRANSMIT))
		 {
			 handle = Can_MailBox_Handle[0];
			 Can_Conf_Flags[handle/8] |= Conf_Mask[handle % 8];
		 }   
		 Can_MailBox_Handle[0] = MAILBOXFREE;
	 }
	 else if(CAN_CTSR & CTSR_TXOK1)
	 {
		 CAN_CTSR |= CTSR_RQCP1;	
		 if(Can_MailBox_Handle[1] != CANMSGCANCEL)
		 {
			 handle = Can_MailBox_Handle[1];
			 Can_Conf_Flags[handle/8] |= Conf_Mask[handle % 8];
		 }   
		 Can_MailBox_Handle[1] = MAILBOXFREE;
	 }
	 else if(CAN_CTSR & CTSR_RQCP0)
	 {
		 CAN_CTSR = CTSR_RQCP0;
		 Can_MailBox_Handle[0] = MAILBOXFREE;
	 } 
	 else if(CAN_CTSR & CTSR_RQCP1)
	 {
		 CAN_CTSR = CTSR_RQCP1;
		 Can_MailBox_Handle[1] = MAILBOXFREE;
	 } 
}
/************** (c) 2003  ST Microelectronics ****************** END OF FILE */
