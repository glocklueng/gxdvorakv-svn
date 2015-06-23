/******************** (C) COPYRIGHT 2008 STMicroelectronics *******************
* Project		: LIN Validation
* File Name   	: common.h
* Author      	: Radek Pulpan
* Version		: 1.0
* Date			: 17.03.2008
* Procesor		: STM8A
* Compilator	: Cosmic STM8 4.2.4
* Description 	: Common header for the project
********************************************************************************
* History:
* 17.03.2008: Version 1.0
*******************************************************************************/

#ifndef __COMMON_H__
	#define __COMMON_H__

	#include "stm8_map.h"

	#define DI() _asm("sim")
	#define EI() _asm("rim")
	#define NOP() _asm("nop")

	#define ATOMIC_SECTION(atomic_section_code) do{unsigned char tmpCC;tmpCC=(unsigned char)_asm("push cc \n pop a",tmpCC);_asm("sim");atomic_section_code;_asm("push a \n pop cc",tmpCC); }while(0)

	#define CPLBIT8(var,bPos) do{ var^=(unsigned char)(0x01<<bPos); }while(0)
	#define WRBIT8(var,bPos,bVal) do{ var=((unsigned char)(bVal?var|((unsigned char)0x01<<bPos):var&(~((unsigned char)0x01<<bPos)))); }while(0)
	#define RDBIT8(var,bPos) ((unsigned char)((var&((unsigned char)0x01<<bPos))?1:0))
	#define BIN8(b7,b6,b5,b4,b3,b2,b1,b0) ((unsigned char)(((b7&0x01)<<7)|((b6&0x01)<<6)|((b5&0x01)<<5)|((b4&0x01)<<4)|((b3&0x01)<<3)|((b2&0x01)<<2)|((b1&0x01)<<1)|((b0&0x01)<<0)))

	#define SET_ISP_LEVEL_1(vector) do{ (*(unsigned char*)(0x7F70+(vector>>2)))=(((*(unsigned char*)(0x7F70+(vector>>2)))&(~((unsigned char)0x03<<((vector&0x03)<<1))))|((unsigned char)0x01<<((vector&0x03)<<1))); }while(0)
	#define SET_ISP_LEVEL_2(vector) do{ (*(unsigned char*)(0x7F70+(vector>>2)))=(((*(unsigned char*)(0x7F70+(vector>>2)))&(~((unsigned char)0x03<<((vector&0x03)<<1))))|((unsigned char)0x00<<((vector&0x03)<<1))); }while(0)
	#define SET_ISP_LEVEL_3(vector) do{ (*(unsigned char*)(0x7F70+(vector>>2)))=(((*(unsigned char*)(0x7F70+(vector>>2)))&(~((unsigned char)0x03<<((vector&0x03)<<1))))|((unsigned char)0x03<<((vector&0x03)<<1))); }while(0)
	#define SET_ISP_LEVEL(level,vector) do{ const unsigned char mask[]={0x01,0x01,0x00,0x03}; (*(unsigned char*)(0x7F70+(vector>
	#define FALSE 	0
	#define TRUE	~FALSE
#define RET_OK		0x01
#define RET_ERR		0x00
#define RET_BUSY	0x0A
#define RET_INVALID_ARGUMENT 0x0B

#endif
