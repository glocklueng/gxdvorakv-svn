/*
*******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : user.h
Group            : MicroController Group
Author           : MCD Application Team
Date First Issued: 25/11/03   
********************************Documentation**********************************
Purpose - This file contains all user configuarable parameters. For example- size of Tx &
Rx buffers, Number of Tx & Rx messages, hardware registers initialization values etc. 
This file can be configured by the user depending on the application. 

********************************RevisionHistory********************************
_______________________________________________________________________________
Date : 25/11/03                                      Release : V1.0   	
*******************************************************************************/
#ifndef USER_H
#define USER_H

#include "can.h"
/*****************************User Configuarable Part *********************************************/

#define NO_OF_TX_HANDLES        0x05
#define NO_OF_RX_HANDLES        0x08
#define NO_OF_INIT_HANDLES      0x01

#define TX_MSG0_STDID           0x200
#define TX_MSG1_STDID           0x2f0
#define TX_MSG2_STDID           0x300
#define TX_MSG3_STDID           0x350
#define TX_MSG4_STDID           0x400

#define TX_MSG0_EXTID           0x000
#define TX_MSG1_EXTID           0x000
#define TX_MSG2_EXTID           0x000
#define TX_MSG3_EXTID           0x000
#define TX_MSG4_EXTID           0x7ac0

#define TX_MSG0_DLC             0x08
#define TX_MSG1_DLC             0x04
#define TX_MSG2_DLC             0x04
#define TX_MSG3_DLC             0x04
#define TX_MSG4_DLC             0x04

#define RX_MSG0_STDID           0x400
#define RX_MSG1_STDID           0x470
#define RX_MSG2_STDID           0x4f0
#define RX_MSG3_STDID           0x500
#define RX_MSG4_STDID           0x701
#define RX_MSG5_STDID           0x701
#define RX_MSG6_STDID           0x600
#define RX_MSG7_STDID           0x650

#define RX_MSG0_EXTID           0x000
#define RX_MSG1_EXTID           0x000
#define RX_MSG2_EXTID           0x000
#define RX_MSG3_EXTID           0x000
#define RX_MSG4_EXTID           0x7a00
#define RX_MSG5_EXTID           0xfa00
#define RX_MSG6_EXTID           0x000
#define RX_MSG7_EXTID           0x000

#define RX_MSG0_DLC             0x02
#define RX_MSG1_DLC             0x08
#define RX_MSG2_DLC             0x04
#define RX_MSG3_DLC             0x04
#define RX_MSG4_DLC             0x04
#define RX_MSG5_DLC             0x04
#define RX_MSG6_DLC             0x04
#define RX_MSG7_DLC             0x04

#define CBTR0_INIT0_VALUE       0x47 
#define CBTR1_INIT0_VALUE       0x25
	
#define CFMR0_INIT0_VALUE       0xcf     /* only filter2 into the mask mode */
#define CFMR1_INIT0_VALUE       0xff
	
#define CF0R0_INIT0_VALUE       0x80     /* 0x400 */  
#define CF0R1_INIT0_VALUE       0x00
#define CF0R2_INIT0_VALUE       0x8e     /* 0x470 */
#define CF0R3_INIT0_VALUE       0x00
#define CF0R4_INIT0_VALUE       0x9e     /* 0x4f0 */
#define CF0R5_INIT0_VALUE       0x00
#define CF0R6_INIT0_VALUE       0xa0     /* 0x500 */
#define CF0R7_INIT0_VALUE       0x00	

#define CF1R0_INIT0_VALUE       0xe0     /* 0x700:0x17a00 */ 
#define CF1R1_INIT0_VALUE       0x0a
#define CF1R2_INIT0_VALUE       0xf4
#define CF1R3_INIT0_VALUE       0x00
#define CF1R4_INIT0_VALUE       0xe0    /* 0x700:0x1fa00 */
#define CF1R5_INIT0_VALUE       0x0b
#define CF1R6_INIT0_VALUE       0xf4
#define CF1R7_INIT0_VALUE       0x00
	
#define CF2R0_INIT0_VALUE       0xc0    /* 0x600 */ 
#define CF2R1_INIT0_VALUE       0x00
#define CF2R2_INIT0_VALUE       0xf8    /* mask for 0x600-0x63f */
#define CF2R3_INIT0_VALUE       0x00
#define CF2R4_INIT0_VALUE       0xca    /* 0x650 */
#define CF2R5_INIT0_VALUE       0x00
#define CF2R6_INIT0_VALUE       0xff    /* mask for 0x650-0x653 */
#define CF2R7_INIT0_VALUE       0x80
		
#define CF3R0_INIT0_VALUE       0x07
#define CF3R1_INIT0_VALUE       0xff
#define CF3R2_INIT0_VALUE       0x07
#define CF3R3_INIT0_VALUE       0xff
#define CF3R4_INIT0_VALUE       0x07
#define CF3R5_INIT0_VALUE       0xff
#define CF3R6_INIT0_VALUE       0x07
#define CF3R7_INIT0_VALUE       0xff


#define CF4R0_INIT0_VALUE       0x07
#define CF4R1_INIT0_VALUE       0xff
#define CF4R2_INIT0_VALUE       0x07
#define CF4R3_INIT0_VALUE       0xff
#define CF4R4_INIT0_VALUE       0x07
#define CF4R5_INIT0_VALUE       0xff
#define CF4R6_INIT0_VALUE       0x07
#define CF4R7_INIT0_VALUE       0xff
		
#define CF5R0_INIT0_VALUE       0x07
#define CF5R1_INIT0_VALUE       0xff
#define CF5R2_INIT0_VALUE       0x07
#define CF5R3_INIT0_VALUE       0xff
#define CF5R4_INIT0_VALUE       0x07
#define CF5R5_INIT0_VALUE       0xff
#define CF5R6_INIT0_VALUE       0x07
#define CF5R7_INIT0_VALUE       0xff
		
#define CFCR0_INIT0_VALUE       0x75    /* enable filter 0,1 filter0- 16bit, filter1- 32bit */
#define CFCR1_INIT0_VALUE       0x45    /* enable filter 2, filter2- 16bit */
#define CFCR2_INIT0_VALUE       0x44
/* *********************************End of User Configuarable Part**************************************/

/* ************************************Non-User Configuarable Part**************************************/
/* Return Status by the driver function */ 
#define KCANTXFAILED            0x00
#define KCANTXOK                0x01
#define KCANFAILED              0x00
#define KCANOK                  0x01
#define KCANHWISSLEEP           0x10
#define KCANHWISBUSOFF          0x20
#define KCANHWISPASSIVE         0x40
#define KCANHWISWARNING         0x80
#define KCANTXOFF               0x00
#define KCANTXON                0x01

#define SIZE_OF_CONF_FLAGS     ((NO_OF_TX_HANDLES+7)/8)
#define SIZE_OF_IND_FLAGS      ((NO_OF_RX_HANDLES+7)/8)
#define SIZE_OF_OVF_FLAGS      ((NO_OF_RX_HANDLES+7)/8)

#define EXT_ID_MASK            0x4000
#define MAKE_STD_ID(x)         (unsigned int)(x<<2)
#define MAKE_EXT_ID(x)         (unsigned int)((x) | (EXT_ID_MASK))

/*****************************End of Non-User Part *************************************************/

extern const canuint8 Conf_Mask[8];
extern const canuint8 Ind_Mask[8];
extern const canuint8 Ovf_Mask[8];

extern volatile canuint8 Can_Conf_Flags[SIZE_OF_CONF_FLAGS];
extern volatile canuint8 Can_Ind_Flags[SIZE_OF_IND_FLAGS];
extern volatile canuint8 Can_Ovf_Flags[SIZE_OF_OVF_FLAGS];

extern @near volatile canuint8 Msg0_Tx_Buffer[TX_MSG0_DLC];
extern @near volatile canuint8 Msg1_Tx_Buffer[TX_MSG1_DLC];
extern @near volatile canuint8 Msg2_Tx_Buffer[TX_MSG2_DLC];
extern @near volatile canuint8 Msg3_Tx_Buffer[TX_MSG3_DLC];
extern @near volatile canuint8 Msg4_Tx_Buffer[TX_MSG4_DLC];

extern const canuint16 Tx_Stdid[NO_OF_TX_HANDLES];
extern const canuint16 Tx_Extid[NO_OF_TX_HANDLES];
extern const canuint8  Tx_Dlc[NO_OF_TX_HANDLES];
extern volatile canuint8 *Tx_Data_Ptr[NO_OF_TX_HANDLES];

extern @near volatile canuint8 Msg0_Rx_Buffer[RX_MSG0_DLC];
extern @near volatile canuint8 Msg1_Rx_Buffer[RX_MSG1_DLC];
extern @near volatile canuint8 Msg2_Rx_Buffer[RX_MSG2_DLC];
extern @near volatile canuint8 Msg3_Rx_Buffer[RX_MSG3_DLC];
extern @near volatile canuint8 Msg4_Rx_Buffer[RX_MSG4_DLC];
extern @near volatile canuint8 Msg5_Rx_Buffer[RX_MSG5_DLC];
extern @near volatile canuint8 Msg6_Rx_Buffer[RX_MSG6_DLC];
extern @near volatile canuint8 Msg7_Rx_Buffer[RX_MSG7_DLC];

extern @near volatile canuint16 Rx_Stdid[NO_OF_RX_HANDLES];
extern @near volatile canuint16 Rx_Extid[NO_OF_RX_HANDLES];

extern const canuint8 Rx_Dlc[NO_OF_RX_HANDLES];
extern volatile canuint8 *Rx_Data_Ptr[NO_OF_RX_HANDLES];	

extern const canuint8 CBTR0_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CBTR1_Init[NO_OF_INIT_HANDLES];
	
extern const canuint8 CFMR0_Init[NO_OF_INIT_HANDLES]; /* only filter2 into the mask mode */
extern const canuint8 CFMR1_Init[NO_OF_INIT_HANDLES];
	
extern const canuint8 CF0R0_Init[NO_OF_INIT_HANDLES]; /* 0x400 */ 
extern const canuint8 CF0R1_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF0R2_Init[NO_OF_INIT_HANDLES]; /* 0x470 */
extern const canuint8 CF0R3_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF0R4_Init[NO_OF_INIT_HANDLES]; /* 0x4f0 */
extern const canuint8 CF0R5_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF0R6_Init[NO_OF_INIT_HANDLES]; /* 0x500 */
extern const canuint8 CF0R7_Init[NO_OF_INIT_HANDLES];
	
extern const canuint8 CF1R0_Init[NO_OF_INIT_HANDLES]; /* 0x700:0x17a00 */ 
extern const canuint8 CF1R1_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF1R2_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF1R3_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF1R4_Init[NO_OF_INIT_HANDLES];/* 0x700:0x1fa00 */
extern const canuint8 CF1R5_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF1R6_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF1R7_Init[NO_OF_INIT_HANDLES];
	


extern const canuint8 CF2R0_Init[NO_OF_INIT_HANDLES]; /* 0x600 */ 
extern const canuint8 CF2R1_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF2R2_Init[NO_OF_INIT_HANDLES]; /* mask for 0x600-0x63f */
extern const canuint8 CF2R3_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF2R4_Init[NO_OF_INIT_HANDLES]; /* 0x650 */
extern const canuint8 CF2R5_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF2R6_Init[NO_OF_INIT_HANDLES]; /* mask for 0x650-0x653 */
extern const canuint8 CF2R7_Init[NO_OF_INIT_HANDLES];
	
extern const canuint8 CF3R0_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF3R1_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF3R2_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF3R3_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF3R4_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF3R5_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF3R6_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF3R7_Init[NO_OF_INIT_HANDLES];

extern const canuint8 CF4R0_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF4R1_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF4R2_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF4R3_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF4R4_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF4R5_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF4R6_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF4R7_Init[NO_OF_INIT_HANDLES]; 

extern const canuint8 CF5R0_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF5R1_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF5R2_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF5R3_Init[NO_OF_INIT_HANDLES];
extern const canuint8 CF5R4_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF5R5_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF5R6_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CF5R7_Init[NO_OF_INIT_HANDLES]; 
		
extern const canuint8 CFCR0_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CFCR1_Init[NO_OF_INIT_HANDLES]; 
extern const canuint8 CFCR2_Init[NO_OF_INIT_HANDLES];
#endif //USER_H

/**********   (c) 2003  ST Microelectronics **************END OF FILE ********/
