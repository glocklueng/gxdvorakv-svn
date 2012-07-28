/******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
* Project		: STM8A256k AppValidation
* File Name   	: can.c
* Author      	: Radek Pulpan
* Modified			:	Vaclav DVorak	
* Version		: 1.1
* Date			: 23.11.2010
* Processor		: STM8A256K
* Compilator	: Cosmic STM8 4.2.8
* Description 	: can routines
********************************************************************************
* History:
* 05.06.2009: Version 1.0
*******************************************************************************/
/*******************************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDERFOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 ******************************************************************************/

#include "common.h"
#include "stm8_can.h"

//-----------------------------------------------------------------------------

#define PAGE_TXMBOX0 0
#define PAGE_TXMBOX1 1
#define PAGE_ACCFILTER01 2
#define PAGE_ACCFILTER23 3
#define PAGE_ACCFILTER45 4
#define PAGE_TXMBOX2 5
#define PAGE_CONFIGDIAG 6
#define PAGE_RXFIFO 7

#define STOP_INTERRUPTSRVC 1
#define STOP_PROCESSRX 2
#define STOP_SELFTEST 3

#define CAN_MCSR    CAN->CP0
#define CAN_MDLCR   CAN->CP1
#define CAN_MIDR1   CAN->CP2
#define CAN_MIDR2   CAN->CP3
#define CAN_MIDR3   CAN->CP4
#define CAN_MIDR4   CAN->CP5
#define CAN_MDAR1   CAN->CP6
#define CAN_MDAR2   CAN->CP7
#define CAN_MDAR3   CAN->CP8
#define CAN_MDAR4   CAN->CP9
#define CAN_MDAR5   CAN->CPA
#define CAN_MDAR6   CAN->CPB
#define CAN_MDAR7   CAN->CPC
#define CAN_MDAR8   CAN->CPD
#define CAN_MTSRL   CAN->CPE
#define CAN_MTSRH   CAN->CPF

#define CAN_CESR    CAN->CP0
#define CAN_CEIER   CAN->CP1
#define CAN_CBTR0   CAN->CP4
#define CAN_CBTR1   CAN->CP5
#define CAN_CFMR0   CAN->CP8
#define CAN_CFMR1   CAN->CP9
#define CAN_CFCR0   CAN->CPA
#define CAN_CFCR1   CAN->CPB
#define CAN_CFCR2   CAN->CPC

#define CAN_CF0R0   CAN->CP0
#define CAN_CF1R0   CAN->CP8
#define CAN_CF2R0   CAN->CP0
#define CAN_CF3R0   CAN->CP8
#define CAN_CF4R0   CAN->CP0
#define CAN_CF5R0   CAN->CP8

#define ID_CONTROL 0
#define CONTROL_TESTDIS 0
#define CONTROL_TESTENA 1

//-----------------------------------------------------------------------------
#define REG_PAGE_SELECT(pgNr) do{ CAN->CPSR = (pgNr & 0x07); }while(0)

#define CTRL_MOD_NAME MOD_CAN

#define SEND_STATUS(status,info) do{CAN_CREATE_MSG(txBuff, 0x00000007, 3, CTRL_MOD_NAME,status,info,0,0,0,0,0); isTxPending = TRUE; }while(0)
#define SET_WRITERQ()        do{ isTxPending = TRUE; }while(0)
#define CLEAR_WRITERQ()      do{ isTxPending = FALSE; }while(0)
#define IS_WRITERQ_PENDING() isTxPending
//-----------------------------------------------------------------------------
static u8 GetFirstEmptyTxMBoxNr (u8 *pIDBox);
static u8 GetRxFifoStatus (void);
static void CAN_Error(u8 code);
static u8 CAN_Read(tCANMsg *pRxMsgBuff);
static tCANMsg 	TxMsgBuff;
static tCANMsg 	RxMsgBuff;
volatile tCANFlag 	Flags;


/******************************************************************************
* FUNCTION: 	CAN_TX_ISR
* PARAMETERS:	void
* DESCRIPTION:	Interrupt service routine for CAN for TX
* RETURNS:		void
*******************************************************************************/
@far @interrupt void CAN_TX_ISR (void)
{


}
/******************************************************************************
* FUNCTION: 	CAN_RX_ISR
* PARAMETERS:	void
* DESCRIPTION:	Interrupt service routine for CAN for RX
* RETURNS:		void
*******************************************************************************/
@far @interrupt void CAN_RX_ISR (void)
{
    if (GetRxFifoStatus() > 0)
    	CAN_Read(&RxMsgBuff);		// check if interrupt is from RX event
    // interrupt was generated by some can error flag as write interrupt
    // is disabled
    else
    	CAN_Error(STOP_INTERRUPTSRVC);
    return;
}
/******************************************************************************
* FUNCTION: 	Can_Init
* PARAMETERS:	void
* DESCRIPTION:	Initial function for CAN cell
* RETURNS:		void
*******************************************************************************/
void CAN_Init (void)
{
    Flags.RxBuffFull = FALSE;
    Flags.TxBuffFull = FALSE;
	DI();						// disable interrupts
    // CAN Master Control Register
    CAN->CMCR = 0x05;			// issue Initialization Mode entry request
    // wait for Initialization Mode entry (CMSR:INAK = 0)
    while (!(CAN->CMSR & 0x01));
    
		// KHG - Start
		CAN->CMCR = CAN->CMCR | 0x10;
		// KHG - Stop
		
		// enable 3. TX mailbox
    CAN->CDGR = BIN8(0,0,0,1, 0,0,0,0);

    // CAN Interrupt Enable Register (CIER)    
		CAN->CIER = BIN8(0,0,0,0, 1,0,1,0);  // FOVIE, FMPIE, TMEIE
    // CAN Error Interrupt Enable Register (CEIER)
    REG_PAGE_SELECT(PAGE_CONFIGDIAG);
		
		CAN_CEIER = BIN8(0,0,0,0, 0,0,0,0);		// KHG -> disable all errors
		//CAN_CEIER = BIN8(1,0,0,1, 0,1,1,1);

    // configure bitrate (CBTCR0 and CBTCR1)
    // nominal bit time = 1Tq (SYNC default), 4Tq (PROP_SEG+PHASE_SEG1),
    //                    3Tq (PHASE_SEG2) -> 9Tq in total
    CAN_CBTR1 = 0x20 | 0x03; // 3Tq + 4Tq
    // SJW = 1
    // 8MHz: 9 - 100k
    // 16MHz: 19 - 100k, 15 - 125k, 9 - 200k, 7 - 250k, 4 - 400k, 3 - 500k, 1 - 1M
    // 24MHz: 29 - 100k, 23 - 125k, 19 - 150k, 14 - 200k, 11 - 250k, 9 - 300k, 5 - 500k, 2 - 1M
    CAN_CBTR0 = 0x00 | 19;

    // configure Acceptance filters
    CAN_CFCR0 = 0x00; CAN_CFCR1 = 0x00; CAN_CFCR2 = 0x00; // deactivate all filter banks
    CAN_CFMR1 = BIN8(0,0,0,0, 0,0,0,0); // all banks in mask mode
    CAN_CFCR0 = BIN8(0,0,0,0, 0,1,1,0); // filter bank 0 as 32-bit filter
    REG_PAGE_SELECT(PAGE_ACCFILTER01);
    *((u8*)(&CAN_CF0R0 + 0)) = 0x00;
    *((u8*)(&CAN_CF0R0 + 1)) = 0x00;
    *((u8*)(&CAN_CF0R0 + 2)) = 0x00;
    *((u8*)(&CAN_CF0R0 + 3)) = 0x00;
    *((u8*)(&CAN_CF0R0 + 4)) = 0x00; // set bank 0 mask -> accept all messages
    *((u8*)(&CAN_CF0R0 + 5)) = 0x00;
    *((u8*)(&CAN_CF0R0 + 6)) = 0x00;
    *((u8*)(&CAN_CF0R0 + 7)) = 0x00;
    *((u8*)(&CAN_CF0R0 + 8)) = 0x00;
    REG_PAGE_SELECT(PAGE_CONFIGDIAG);
    // activate filter bank 0
    CAN_CFCR0 |= BIN8(0,0,0,0, 0,0,0,1);
    EI();
}


/******************************************************************************
* FUNCTION: 	CAN_Start
* PARAMETERS:	return status of the function
* DESCRIPTION:	start CAN cell
* RETURNS:		void
*******************************************************************************/
u8 CAN_Start(void)
{
    CAN->CMCR &=0xFE;		    		// issue Normal Mode entry request
    while (RDBIT8(CAN->CMSR, 0));		// wait for Normal Mode (CMSR:INAK = 0)
    return RET_OK;
}
/******************************************************************************
* FUNCTION: 	CAN_Stop
* PARAMETERS:	return status of the function
* DESCRIPTION:	stop CAN cell
* RETURNS:		void
*******************************************************************************/
u8 CAN_Stop (void)
{
    WRBIT8(CAN->CMCR, 1, 1);			// issue Sleep Mode entry request
    while (!RDBIT8(CAN->CMSR, 1));		// wait for Sleep Mode entry (CMSR:SLAK = 1)
    // should be better deinitialization (IRQ disabling, filters disabling, etc...)
    return RET_OK;
}

/******************************************************************************
* FUNCTION: 	CAN_Write
* PARAMETERS:	pointer to buffer and length
* DESCRIPTION:	write CAN message to the bus
* RETURNS:		status of the function
*******************************************************************************/
u8 CAN_Write (tCANMsg *pTxMsgBuff)
{
    u8 MsgBoxID, i;
    u8 pgRegTmp;
    // check if any tx mailbox is free
    if (GetFirstEmptyTxMBoxNr(&MsgBoxID) == RET_BUSY)
    	return RET_BUSY;

    // write frame
	// push page register (or disable interrupts if necessary)
	pgRegTmp = CAN->CPSR;

	// select tx mailbox registry page
	switch (MsgBoxID)
	{
	case 0: REG_PAGE_SELECT(PAGE_TXMBOX0); break;
	case 1: REG_PAGE_SELECT(PAGE_TXMBOX1); break;
	case 2: REG_PAGE_SELECT(PAGE_TXMBOX2); break;
	default: return RET_INVALID_ARGUMENT;
	}
/*	// check if the mailbox is really free
	if (!(CAN->CTPR &(MsgBoxID<<2)))
	{
		return RET_BUSY;
	}
*/
	// write tx mailbox data
	CAN_MDLCR = pTxMsgBuff->Length;
	CAN_MIDR1 = 0;					// set standard frame, data frame
	if(pTxMsgBuff->Xtd)
	{
		CAN_MIDR1 |= 0x40; 			// set extended frame
		CAN_MIDR1 |= (u8)((pTxMsgBuff->ID >>24) & 0x1F);// EXID28:24
		CAN_MIDR2 = (u8)(pTxMsgBuff->ID >>16);			// EXID23:16
		CAN_MIDR3 = (u8)(pTxMsgBuff->ID >>8);			// EXID15:8
		CAN_MIDR4 = (u8)(pTxMsgBuff->ID);				// EXID7:0

	}
	else							// standard frame
	{
		CAN_MIDR1 &= ~0x40;
		CAN_MIDR1 |= (pTxMsgBuff->ID >>6) & 0x1F;		// SID10:6
		CAN_MIDR2 = (pTxMsgBuff->ID <<2);				// SID5:0
	}
	for (i = 0; i < pTxMsgBuff->Length; i++)			// write data to TX mailbox
		*(&CAN_MDAR1+i) = pTxMsgBuff->Data[i];

	WRBIT8 (CAN_MCSR, 0, 1);							// request tx mailbox transmission
	// pop page register (or enable interrupts if necessary)
	CAN->CPSR = pgRegTmp;
	Flags.TxBuffFull = FALSE;
	return RET_OK;
}
/******************************************************************************
* FUNCTION: 	CAN_Read
* PARAMETERS:	pointer to buffer and length
* DESCRIPTION:	Read CAN message from CAN cell
* RETURNS:		status of the function
*******************************************************************************/
static u8 CAN_Read (tCANMsg *pRxMsgBuff)
{
    u8 i, pgRegTmp;

    // push page register (or disable interrupts if necessary)
    pgRegTmp = CAN->CPSR;
    REG_PAGE_SELECT (PAGE_RXFIFO);

    pRxMsgBuff->Length = CAN_MDLCR;			    // get data length
    pRxMsgBuff->Xtd = CAN_MIDR1 & 0x40;			// get frame ext. flag

    if (pRxMsgBuff->Xtd)						// get frame id
    {
    	pRxMsgBuff->ID = (u32)(CAN_MIDR1 << 24);// EXID28:24
    	pRxMsgBuff->ID |= (u32)(CAN_MIDR2 << 16);// EXID23:16
    	pRxMsgBuff->ID |= (u32)(CAN_MIDR3 << 8);// EXID15:8
    	pRxMsgBuff->ID |= (u32)(CAN_MIDR4);		// EXID7:0
    }
    else
    {
    	pRxMsgBuff->ID = (u32)(CAN_MIDR1 << 6);	// STID10:6
		pRxMsgBuff->ID |= (u32)(CAN_MIDR2 >> 2);// STID5:0
	}
    // get frame data
    if (!(CAN_MIDR1 & CAN_FLAG_RTR)) {
        for (i = 0; i < pRxMsgBuff->Length; i++)
        	pRxMsgBuff->Data[i] = *(&CAN_MDAR1+i);
    }
    WRBIT8(CAN->CRFR, 5, 1);     				// release RX mailbox
    // pop page register (or enable interrupts if necessary)
    CAN->CPSR = pgRegTmp;
    Flags.RxBuffFull = TRUE;
    return RET_OK;
}


/******************************************************************************
* FUNCTION: 	GetFirstEmptyTxMBoxNr
* PARAMETERS:	void
* DESCRIPTION:	return first empty Tx Msgbox
* RETURNS:		status of the function
*******************************************************************************/
static u8 GetFirstEmptyTxMBoxNr (u8 *pIDBox)
{
    if (RDBIT8(CAN->CTPR, 2))
    {
    	*pIDBox = 0;
    	return RET_OK;
    }
    if (RDBIT8(CAN->CTPR, 3))
    {
		*pIDBox = 1;
		return RET_OK;
	}
    if (RDBIT8(CAN->CTPR, 4))
	{
		*pIDBox = 2;
		return RET_OK;
	}
    return RET_BUSY;
}
/******************************************************************************
* FUNCTION: 	GetRxFifoStatus
* PARAMETERS:	void
* DESCRIPTION:	return status of RX MsgBoxes
* RETURNS:		status of the function
*******************************************************************************/
static u8 GetRxFifoStatus (void)
{
    // CRFR:FMP1-0
    return CAN->CRFR & 0x03;
}

/******************************************************************************
* FUNCTION: 	CAN_Error
* PARAMETERS:	error status
* DESCRIPTION:	STOP CAN communication
* RETURNS:
*******************************************************************************/
static void CAN_Error(u8 code)
{
    CAN->CIER = 0;
    REG_PAGE_SELECT(PAGE_CONFIGDIAG);
    CAN_CEIER = 0;
	// set isr level to 0
	#asm
		push cc
		pop a
		and a,#0xD7
		or a,#0x20
		push a
		pop cc
	#endasm
    while (1)
    {
        //if (i > 0x3FFF) {CPLBIT8(GPIOB->ODR,0); i = 0;
    }
}

/******************************************************************************
* FUNCTION: 	CAN_GetMsg
* PARAMETERS:	pointer to buffer
* DESCRIPTION:	Return pointer CAN message buffer
* RETURNS:
*******************************************************************************/
u8 CAN_GetMsg(tCANMsg *pRxMsgBuff)
{
	if(Flags.RxBuffFull)
	{
		pRxMsgBuff = &RxMsgBuff;
		Flags.RxBuffFull = FALSE;
		return RET_OK;
	}
	else
		return RET_ERR;
}

/******************************************************************************
* FUNCTION: 	CAN_SetBaudRate
* PARAMETERS:	void
* DESCRIPTION:	Sets Bad Rate of CAN cell. Function switch CAN to INITIALISATION
*  							mode, to enter bact to normal mode call CAN_Start()
* RETURNS:		void
*******************************************************************************/
void CAN_SetBaudRate (u8 brp, u8 bs1, u8 bs2)
{
    Flags.RxBuffFull = FALSE;
    Flags.TxBuffFull = FALSE;
	DI();						// disable interrupts
    // CAN Master Control Register
	CAN->CMCR |= 0x01;			// issue Initialization Mode entry request
    // wait for Initialization Mode entry (CMSR:INAK = 0)
    while (!(CAN->CMSR & 0x01));
		
	  REG_PAGE_SELECT(PAGE_CONFIGDIAG);
		
		// configure bitrate (CBTCR0 and CBTCR1)
    // nominal bit time = 1Tq (SYNC default), 4Tq (PROP_SEG+PHASE_SEG1),
    //                    3Tq (PHASE_SEG2) -> 9Tq in total
    CAN_CBTR1 = bs1 | ((u8)( bs2 << 4)); // 3Tq + 4Tq
		
    // SJW = 1
    // 8MHz: 9 - 100k
    // 16MHz: 19 - 100k, 15 - 125k, 9 - 200k, 7 - 250k, 4 - 400k, 3 - 500k, 1 - 1M
    // 24MHz: 29 - 100k, 23 - 125k, 19 - 150k, 14 - 200k, 11 - 250k, 9 - 300k, 5 - 500k, 2 - 1M
    CAN_CBTR0 &= ~0x3FU	;
		CAN_CBTR0 |= brp	;
		
	EI();	
}
    
