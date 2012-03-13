/******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
* Project		: STM8A256k AppValidation
* File Name   	: can.h
* Modified			:	Vaclav DVorak	
* Version		: 1.1
* Date			: 23.11.2010
* Processor		: STM8A256K
* Compilator	: Cosmic STM8 4.2.8
* Description 	: header file for can routines
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

#ifndef __MODULE_CAN_H__
#define __MODULE_CAN_H__


// txMBoxImage format: [0]    data length
//                     [1:4]  can id (little endian)
//                     [5:12] data field
typedef struct
{
    u32	ID;
    u8	Xtd;
    u8	Length;
    u8	Data[8];
}tCANMsg;

typedef struct
{
    u8	TxBuffFull;
    u8	RxBuffFull;
}tCANFlag;

#define MSG_GSTATUS_OK 0x00
#define MSG_GSTATUS_WAR 0x01
#define MSG_GSTATUS_ERR 0x02
#define MSG_GSTATUS_FATAL 0x03

#define CAN_CREATE_MSG(buff,id,len,d0,d1,d2,d3,d4,d5,d6,d7) do{ buff[0]=len;cm_U32ToLEBuff(&buff[1],id);buff[5]=d0;buff[6]=d1;buff[7]=d2;buff[8]=d3;buff[9]=d4;buff[10]=d5;buff[11]=d6;buff[12]=d7; }while(0)

#define FRM_CTRL_CMD 0
#define FRM_CTRL_DATA 1

#define CAN_CTRLFRAME_DATA(module,idx) gModCanBuff[module].canData[FRM_CTRL_DATA+idx]
#define CAN_CTRLFRAME_CMD(module) gModCanBuff[module].canData[FRM_CTRL_CMD]
#define CAN_CTRLFRAME_ID(module) gModCanBuff[module].canID
#define CAN_CTRFRAME_IS_MSGBUFF_READY(module) (gModCanBuff[module].isEmpty?FALSE:TRUE)
#define CAN_CTRLFRAME_RELEASE_MSGBUFF(module) do{ gModCanBuff[module].isEmpty = TRUE; }while(0)

#define CF_DATA(idx)        CAN_CTRLFRAME_DATA(CTRL_MOD_NAME,idx)
#define CF_CMD()            CAN_CTRLFRAME_CMD(CTRL_MOD_NAME)
#define CF_ID()             CAN_CTRLFRAME_ID(CTRL_MOD_NAME)
#define CF_ISMSG()          CAN_CTRFRAME_IS_MSGBUFF_READY(CTRL_MOD_NAME)
#define CF_RELEASE_MSG()    CAN_CTRLFRAME_RELEASE_MSGBUFF(CTRL_MOD_NAME)

#define CAN_FLAG_EXTID 0x40
#define CAN_FLAG_RTR 0x20
#define CAN_FLAG_STD 0x00

#define CAN_FRM_DLEN 0
#define CAN_FRM_ID 1
#define CAN_FRM_DATA 5


void CAN_Init(void);
u8 CAN_Start(void);
u8 CAN_Stop (void);
u8 CAN_Write(tCANMsg *pTxMsgBuff);
u8 CAN_GetMsg(tCANMsg *pRxMsgBuff);
void CAN_SetBaudRate (u8 brp, u8 bs1, u8 bs2);


typedef struct
{
  u8 CMCR;
  u8 CMSR;
  u8 CTSR;
  u8 CTPR;
  u8 CRFR;
  u8 CIER;
  u8 CDGR;
  u8 CPSR;
  u8 CP0;
  u8 CP1;
  u8 CP2;
  u8 CP3;
  u8 CP4;
  u8 CP5;
  u8 CP6;
  u8 CP7;
  u8 CP8;
  u8 CP9;
  u8 CPA;
  u8 CPB;
  u8 CPC;
  u8 CPD;
  u8 CPE;
  u8 CPF;
} CAN_TypeDef;

#define CAN_BaseAddress     	0x5420
#define CAN ((CAN_TypeDef *) CAN_BaseAddress)

#endif



