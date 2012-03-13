/*
*******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : user.c
Group            : MicroController Group
Author           : MCD Application Team
Date First Issued: 25/11/03  
********************************Documentation**********************************
Purpose -  This file contains the Global data declaration which is used by both
driver as well as the application. For example - Tx & Rx buffers, Tx & Rx Id, 
Confirmation & Indication flags etc. This file can be configured by the user 
depending on the application.  
********************************RevisionHistory********************************
_______________________________________________________________________________
Date : 25/11/03                                                 Release :  V1.0
      
******************************************************************************/
//#include "lib.h" 
#include "user.h"

volatile canuint8 Can_Conf_Flags[SIZE_OF_CONF_FLAGS];
volatile canuint8 Can_Ind_Flags[SIZE_OF_IND_FLAGS];
volatile canuint8 Can_Ovf_Flags[SIZE_OF_OVF_FLAGS];

const canuint8 Conf_Mask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
const canuint8 Ind_Mask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
const canuint8 Ovf_Mask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

@near volatile canuint8 Msg0_Tx_Buffer[TX_MSG0_DLC];
@near volatile canuint8 Msg1_Tx_Buffer[TX_MSG1_DLC];
@near volatile canuint8 Msg2_Tx_Buffer[TX_MSG2_DLC];
@near volatile canuint8 Msg3_Tx_Buffer[TX_MSG3_DLC];
@near volatile canuint8 Msg4_Tx_Buffer[TX_MSG4_DLC];

const canuint16 Tx_Stdid[NO_OF_TX_HANDLES]= {MAKE_STD_ID(TX_MSG0_STDID),
																						 MAKE_STD_ID(TX_MSG1_STDID),
																						 MAKE_STD_ID(TX_MSG2_STDID),
																						 MAKE_STD_ID(TX_MSG3_STDID),
																						 ((MAKE_STD_ID(TX_MSG4_STDID))|(EXT_ID_MASK))
																						 };

const canuint16 Tx_Extid[NO_OF_TX_HANDLES]= {TX_MSG0_EXTID,
																						 TX_MSG1_EXTID,
																						 TX_MSG2_EXTID,
																						 TX_MSG3_EXTID,
																						 TX_MSG4_EXTID
																						 };

const canuint8  Tx_Dlc[NO_OF_TX_HANDLES]= 	{TX_MSG0_DLC,
																					 	 TX_MSG1_DLC,
																					 	 TX_MSG2_DLC,
																					 	 TX_MSG3_DLC,
																					 	 TX_MSG4_DLC
																						 };

volatile canuint8 *Tx_Data_Ptr[NO_OF_TX_HANDLES]= {Msg0_Tx_Buffer,
																						 Msg1_Tx_Buffer,
																						 Msg2_Tx_Buffer,
																						 Msg3_Tx_Buffer,
																						 Msg4_Tx_Buffer
																						 };																				  

@near volatile canuint8 Msg0_Rx_Buffer[RX_MSG0_DLC];
@near volatile canuint8 Msg1_Rx_Buffer[RX_MSG1_DLC];
@near volatile canuint8 Msg2_Rx_Buffer[RX_MSG2_DLC];
@near volatile canuint8 Msg3_Rx_Buffer[RX_MSG3_DLC];
@near volatile canuint8 Msg4_Rx_Buffer[RX_MSG4_DLC];
@near volatile canuint8 Msg5_Rx_Buffer[RX_MSG5_DLC];
@near volatile canuint8 Msg6_Rx_Buffer[RX_MSG6_DLC];
@near volatile canuint8 Msg7_Rx_Buffer[RX_MSG7_DLC];

@near volatile canuint16 Rx_Stdid[NO_OF_RX_HANDLES];
@near volatile canuint16 Rx_Extid[NO_OF_RX_HANDLES];

const canuint8 Rx_Dlc[NO_OF_RX_HANDLES]= 	{RX_MSG0_DLC,
													 	 RX_MSG1_DLC,
													 	 RX_MSG2_DLC,
														 RX_MSG3_DLC,
														 RX_MSG4_DLC,
														 RX_MSG5_DLC,
														 RX_MSG6_DLC,
														 RX_MSG7_DLC
														};
volatile canuint8 *Rx_Data_Ptr[NO_OF_RX_HANDLES]= {Msg0_Rx_Buffer,
																								Msg1_Rx_Buffer,
																								Msg2_Rx_Buffer,
																								Msg3_Rx_Buffer,
																								Msg4_Rx_Buffer,
																								Msg5_Rx_Buffer,
																								Msg6_Rx_Buffer,
																								Msg7_Rx_Buffer
																								};
																								
const canuint8 CBTR0_Init[NO_OF_INIT_HANDLES]= {CBTR0_INIT0_VALUE}; 
const canuint8	CBTR1_Init[NO_OF_INIT_HANDLES]= {CBTR1_INIT0_VALUE};
	
const canuint8	CFMR0_Init[NO_OF_INIT_HANDLES] = {CFMR0_INIT0_VALUE}; 
const canuint8	CFMR1_Init[NO_OF_INIT_HANDLES] = {CFMR1_INIT0_VALUE};
	
const canuint8	CF0R0_Init[NO_OF_INIT_HANDLES] = {CF0R0_INIT0_VALUE};  
const canuint8	CF0R1_Init[NO_OF_INIT_HANDLES] = {CF0R1_INIT0_VALUE};
const canuint8	CF0R2_Init[NO_OF_INIT_HANDLES] = {CF0R2_INIT0_VALUE}; 
const canuint8	CF0R3_Init[NO_OF_INIT_HANDLES] = {CF0R3_INIT0_VALUE};
const canuint8	CF0R4_Init[NO_OF_INIT_HANDLES] = {CF0R4_INIT0_VALUE}; 
const canuint8	CF0R5_Init[NO_OF_INIT_HANDLES] = {CF0R5_INIT0_VALUE};
const canuint8	CF0R6_Init[NO_OF_INIT_HANDLES] = {CF0R6_INIT0_VALUE}; 
const canuint8	CF0R7_Init[NO_OF_INIT_HANDLES] = {CF0R7_INIT0_VALUE };
	
const canuint8	CF1R0_Init[NO_OF_INIT_HANDLES] = {CF1R0_INIT0_VALUE};  
const canuint8	CF1R1_Init[NO_OF_INIT_HANDLES] = {CF1R1_INIT0_VALUE};
const canuint8	CF1R2_Init[NO_OF_INIT_HANDLES] = {CF1R2_INIT0_VALUE};
const canuint8	CF1R3_Init[NO_OF_INIT_HANDLES] = {CF1R3_INIT0_VALUE};
const canuint8	CF1R4_Init[NO_OF_INIT_HANDLES] = {CF1R4_INIT0_VALUE};
const canuint8	CF1R5_Init[NO_OF_INIT_HANDLES] = {CF1R5_INIT0_VALUE};
const canuint8	CF1R6_Init[NO_OF_INIT_HANDLES] = {CF1R6_INIT0_VALUE};
const canuint8	CF1R7_Init[NO_OF_INIT_HANDLES] = {CF1R7_INIT0_VALUE};
	


const canuint8	CF2R0_Init[NO_OF_INIT_HANDLES] = {CF2R0_INIT0_VALUE}; 
const canuint8	CF2R1_Init[NO_OF_INIT_HANDLES] = {CF2R1_INIT0_VALUE};
const canuint8	CF2R2_Init[NO_OF_INIT_HANDLES] = {CF2R2_INIT0_VALUE}; 
const canuint8	CF2R3_Init[NO_OF_INIT_HANDLES] = {CF2R3_INIT0_VALUE};
const canuint8	CF2R4_Init[NO_OF_INIT_HANDLES] = {CF2R4_INIT0_VALUE}; 
const canuint8	CF2R5_Init[NO_OF_INIT_HANDLES] = {CF2R5_INIT0_VALUE};
const canuint8	CF2R6_Init[NO_OF_INIT_HANDLES] = {CF2R6_INIT0_VALUE}; 
const canuint8	CF2R7_Init[NO_OF_INIT_HANDLES] = {CF2R7_INIT0_VALUE};
	
const canuint8	CF3R0_Init[NO_OF_INIT_HANDLES] = {CF3R0_INIT0_VALUE}; 
const canuint8	CF3R1_Init[NO_OF_INIT_HANDLES] = {CF3R1_INIT0_VALUE};
const canuint8	CF3R2_Init[NO_OF_INIT_HANDLES] = {CF3R2_INIT0_VALUE}; 
const canuint8	CF3R3_Init[NO_OF_INIT_HANDLES] = {CF3R3_INIT0_VALUE};
const canuint8	CF3R4_Init[NO_OF_INIT_HANDLES] = {CF3R4_INIT0_VALUE}; 
const canuint8	CF3R5_Init[NO_OF_INIT_HANDLES] = {CF3R5_INIT0_VALUE};
const canuint8	CF3R6_Init[NO_OF_INIT_HANDLES] = {CF3R6_INIT0_VALUE}; 
const canuint8	CF3R7_Init[NO_OF_INIT_HANDLES] = {CF3R7_INIT0_VALUE};

const canuint8	CF4R0_Init[NO_OF_INIT_HANDLES] = {CF4R0_INIT0_VALUE}; 
const canuint8	CF4R1_Init[NO_OF_INIT_HANDLES] = {CF4R1_INIT0_VALUE};
const canuint8	CF4R2_Init[NO_OF_INIT_HANDLES] = {CF4R2_INIT0_VALUE}; 
const canuint8	CF4R3_Init[NO_OF_INIT_HANDLES] = {CF4R3_INIT0_VALUE};
const canuint8	CF4R4_Init[NO_OF_INIT_HANDLES] = {CF4R4_INIT0_VALUE}; 
const canuint8	CF4R5_Init[NO_OF_INIT_HANDLES] = {CF4R5_INIT0_VALUE};
const canuint8	CF4R6_Init[NO_OF_INIT_HANDLES] = {CF4R6_INIT0_VALUE}; 
const canuint8	CF4R7_Init[NO_OF_INIT_HANDLES] = {CF4R7_INIT0_VALUE};

const canuint8	CF5R0_Init[NO_OF_INIT_HANDLES] = {CF5R0_INIT0_VALUE}; 
const canuint8	CF5R1_Init[NO_OF_INIT_HANDLES] = {CF5R1_INIT0_VALUE};
const canuint8	CF5R2_Init[NO_OF_INIT_HANDLES] = {CF5R2_INIT0_VALUE}; 
const canuint8	CF5R3_Init[NO_OF_INIT_HANDLES] = {CF5R3_INIT0_VALUE};
const canuint8	CF5R4_Init[NO_OF_INIT_HANDLES] = {CF5R4_INIT0_VALUE}; 
const canuint8	CF5R5_Init[NO_OF_INIT_HANDLES] = {CF5R5_INIT0_VALUE};
const canuint8	CF5R6_Init[NO_OF_INIT_HANDLES] = {CF5R6_INIT0_VALUE}; 
const canuint8	CF5R7_Init[NO_OF_INIT_HANDLES] = {CF5R7_INIT0_VALUE};
		
const canuint8	CFCR0_Init[NO_OF_INIT_HANDLES]= {CFCR0_INIT0_VALUE}; 
const canuint8	CFCR1_Init[NO_OF_INIT_HANDLES]= {CFCR1_INIT0_VALUE}; 
const canuint8	CFCR2_Init[NO_OF_INIT_HANDLES]= {CFCR2_INIT0_VALUE};				
/************** (c) 2003  ST Microelectronics ****************** END OF FILE **/
