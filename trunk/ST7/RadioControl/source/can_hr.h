/*
*******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : can_hr.h
Group            : MicroController Group
Author           : MCD Application Team
Date First Issued: 25/11/03
********************************Documentation**********************************
Purpose - This file contains the #define statements for the driver functions. 
This file must not be changed by the user.
********************************RevisionHistory********************************
_______________________________________________________________________________
Date : 25/11/03                       Release : V1.0   
       	
******************************************************************************/   
#ifndef CAN_HR_H
#define CAN_HR_H    


/* CAN Hardware Registers */   
    @tiny volatile unsigned char CAN_CMCR @0x68; /* CAN Master Control Register*/
    @tiny volatile unsigned char CAN_CMSR @0x69; /* Master status Register     */
    @tiny volatile unsigned char CAN_CTSR @0x6A; /* Transmit Status Register   */
    @tiny volatile unsigned char CAN_CTPR @0x6B; /* Transmit Priority register */
    @tiny volatile unsigned char CAN_CRFR @0x6C; /* Receive FIFO Register      */
    @tiny volatile unsigned char CAN_CIER @0x6D; /* Interrupt Enable Register  */
    @tiny volatile unsigned char CAN_CDGR @0x6E; /* Diagnosis Register         */
    @tiny volatile unsigned char CAN_CPSR @0x6F; /* Page selection register    */

/*  Tx MailBox/Receive FIFO Registers */
    @tiny volatile unsigned char CAN_MCSR  	@0x70;   /* For Tx */
    @tiny volatile unsigned char CAN_MFMI  	@0x70;   /* For Receive FIFO */
    @tiny volatile unsigned char CAN_MDLC  	@0x71;
    @tiny volatile unsigned char CAN_MIDR0 	@0x72;
    @tiny volatile unsigned char CAN_MIDR1 	@0x73;
    @tiny volatile unsigned char CAN_MIDR2	@0x74;
    @tiny volatile unsigned char CAN_MIDR3 	@0x75;
    @tiny volatile unsigned char CAN_MDAR[8]    @0x76;
    @tiny volatile unsigned int  CAN_MDAW[4]	@0x76;
     
	
    @tiny volatile unsigned char CAN_MTSLR 	@0x7e;
    @tiny volatile unsigned char CAN_MTSHR 	@0x7f;
    
    @tiny volatile unsigned int  CAN_MIDR01 	@0x72;
    @tiny volatile unsigned int  CAN_MIDR23 	@0x74;

/*  Configuaration/Diagnosis Registers */    
    
    @tiny volatile unsigned char CAN_CESR  	@0x70;
    @tiny volatile unsigned char CAN_CEIER 	@0x71;
    @tiny volatile unsigned char CAN_TECR  	@0x72;
    @tiny volatile unsigned char CAN_RECR  	@0x73;
    @tiny volatile unsigned char CAN_CBTR0 	@0x74;
    @tiny volatile unsigned char CAN_CBTR1 	@0x75;
    @tiny volatile unsigned char CAN_unknown1 	@0x76;
    @tiny volatile unsigned char CAN_unknown2 	@0x77;
    @tiny volatile unsigned char CAN_CFMR0 	@0x78;
    @tiny volatile unsigned char CAN_CFMR1 	@0x79;
    @tiny volatile unsigned char CAN_CFCR0 	@0x7a;
    @tiny volatile unsigned char CAN_CFCR1 	@0x7b;
    @tiny volatile unsigned char CAN_CFCR2 	@0x7c;
    @tiny volatile unsigned char CAN_unknown3 	@0x7d;
    @tiny volatile unsigned char CAN_unknown4 	@0x7e;
    @tiny volatile unsigned char CAN_unknown5 	@0x7f;

/*  Acceptance Filter Registers*/

    @tiny volatile unsigned char CAN_CFxR0 @0x70;
    @tiny volatile unsigned char CAN_CFxR1 @0x71;
    @tiny volatile unsigned char CAN_CFxR2 @0x72;
    @tiny volatile unsigned char CAN_CFxR3 @0x73;
    @tiny volatile unsigned char CAN_CFxR4 @0x74;
    @tiny volatile unsigned char CAN_CFxR5 @0x75;
    @tiny volatile unsigned char CAN_CFxR6 @0x76;
    @tiny volatile unsigned char CAN_CFxR7 @0x77;

    @tiny volatile unsigned char CAN_CFyR0 @0x78;
    @tiny volatile unsigned char CAN_CFyR1 @0x79;
    @tiny volatile unsigned char CAN_CFyR2 @0x7a;
    @tiny volatile unsigned char CAN_CFyR3 @0x7b;
    @tiny volatile unsigned char CAN_CFyR4 @0x7c;
    @tiny volatile unsigned char CAN_CFyR5 @0x7d;
    @tiny volatile unsigned char CAN_CFyR6 @0x7e;
    @tiny volatile unsigned char CAN_CFyR7 @0x7f;

    @tiny volatile unsigned int CAN_CFxR01 @0x70;
    @tiny volatile unsigned int CAN_CFxR23 @0x72;
    @tiny volatile unsigned int CAN_CFxR45 @0x74;
    @tiny volatile unsigned int CAN_CFxR67 @0x76;

    @tiny volatile unsigned int CAN_CFyR01 @0x78;
    @tiny volatile unsigned int CAN_CFyR23 @0x7a;
    @tiny volatile unsigned int CAN_CFyR45 @0x7c;
    @tiny volatile unsigned int CAN_CFyR67 @0x7e;




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

#endif // CAN_HR_H


/********** (c) 2003   STMicroelectronics ********************* END OF FILE ***/
