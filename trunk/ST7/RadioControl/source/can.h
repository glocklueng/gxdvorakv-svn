/*
*******************************************************************************
COPYRIGHT 2002 STMicroelectronics
Source File Name : can.h
Group            : IPSW,CMG-IPDF.
Author           : MCD Application Team
Date First Issued:    
********************************Documentation**********************************
General Purpose - This file contains the function prototypes for the driver fun
-ctions and the Data Types.
********************************RevisionHistory********************************
_______________________________________________________________________________
Date :  25/11/03                       Release : V1.0
*******************************************************************************/

#ifndef CAN_H
#define CAN_H

//#include "lib.h"

typedef unsigned char canuint8;
typedef unsigned int  canuint16;
typedef unsigned char CanTransmitHandle;
typedef unsigned char CanInitHandle;

typedef volatile struct
{
	canuint16  stdid;
	canuint16  extid;
	canuint8	 dlc;
	canuint8   data[8];
} tCanMsgOject;

// Function Prototypes
void CanInitPowerOn( void);
void CanInit(CanInitHandle init_handle);
void CanGlobalInterruptDisable( void);
void CanGlobalInterruptRestore( void);
void CanCanInterruptDisable( void);
void CanCanInterruptRestore( void);
void CanTxTask(void);
canuint8 CanSleep( void);
canuint8 CanGetStatus( void);
canuint8 CanWakeup( void);


canuint8 CanTransmit( CanTransmitHandle tx_handle);
canuint8 CanMsgTransmit(tCanMsgOject *txData);
canuint8 CanWriteBuffer(canuint8 handle,canuint8 *data);





#define CAN_TXMB0_PG       ((unsigned char) 0) /* CAN TX mailbox 0 reg page */
#define CAN_TXMB1_PG       ((unsigned char) 1) /* CAN TX mailbox 1 reg page */
#define CAN_FILTER01_PG    ((unsigned char) 2) /* CAN Filters 0 & 1 reg page*/
#define CAN_FILTER23_PG    ((unsigned char) 3) /* CAN Filters 2 & 3 reg page*/
#define CAN_FILTER45_PG    ((unsigned char) 4) /* CAN Filters 4 & 5 reg page*/
#define CAN_CTRL_PG        ((unsigned char) 6) /* CAN control/status reg page*/
#define CAN_FIFO_PG        ((unsigned char) 7) /* CAN FIFO registers page */

#define MCSR_ABRQ					     ((unsigned char)0x40)
#define MCSR_TXRQ					     ((unsigned char)0x01)

#define CMCR_TTCN					     ((unsigned char)0x80)
#define CMCR_ABOM					     ((unsigned char)0x40)
#define CMCR_AWUM					     ((unsigned char)0x20)
#define CMCR_NART					     ((unsigned char)0x10)
#define CMCR_RFLM					     ((unsigned char)0x08)
#define CMCR_TXFP					     ((unsigned char)0x04)
#define CMCR_SLEEP				     ((unsigned char)0x02)
#define CMCR_INRQ					     ((unsigned char)0x01)

#define CMSR_SLAK					     ((unsigned char)0x02)
#define CMSR_INAK					     ((unsigned char)0x01)
#define CMSR_ERRI					     ((unsigned char)0x04)
#define CMSR_WKUI					     ((unsigned char)0x08)

#define CTSR_RQCP0				     ((unsigned char)0x01)
#define CTSR_RQCP1				     ((unsigned char)0x02)
#define CTSR_TXOK0				     ((unsigned char)0x10)
#define CTSR_TXOK1				     ((unsigned char)0x20)

#define CTPR_TME0					     ((unsigned char)0x04)
#define CTPR_TME1					     ((unsigned char)0x08)

#define CRFR_RFOM          ((unsigned char)0x20)
#define CRFR_FOVR					     ((unsigned char)0x10)
#define CRFR_FULL          ((unsigned char)0x08)
#define CRFR_FMP01         ((unsigned char)0x03)

#define CESR_BOFF					     ((unsigned char)0x04)
#define CESR_EPVF					     ((unsigned char)0x02)
#define CESR_EWGF					     ((unsigned char)0x01)

#define CIER_WKUIE				     ((unsigned char)0x80)
#define CIER_FOVIE				     ((unsigned char)0x08)
#define CIER_FFIE					     ((unsigned char)0x04)
#define CIER_FMPIE				     ((unsigned char)0x02)
#define CIER_TMEIE				     ((unsigned char)0x01)

#define CEIER_ERRIE				    ((unsigned char)0x80)
#define CEIER_LECIE				    ((unsigned char)0x10)
#define CEIER_BOFIE				    ((unsigned char)0x04)
#define CEIER_EPVIE				    ((unsigned char)0x02)
#define CEIER_EWGIE				    ((unsigned char)0x01)

#define MAILBOXFREE				    0xff
#define CANMSGCANCEL	 		   0xfe
#define CANMSGTRANSMIT 		  0xfc

#define EXT_ID_MASK				    0x4000
#define MAX_DLC_LEN				    0x08
#define NO_OF_TX_MAILBOX	  0x02


#endif //CAN_H



/**********(c) 2002  ST Microelectronics **************END OF FILE ********/
