/******************************************************************************/
/*! Project Name:   L9952 driver
    @file           Std_Types.h
    @version        $Revision: 1.2.6.2 $
    @date           $Date: 2009/05/22 06:37:55 $
    @author         David Trojek
    @author         Vaclav Dvorak
    @brief          SW driver for ST L9952 device - Autosar compliant file.

    Company:        STMicroelectronics
                    Pobrezni 3
                    186 00 Praha 8, Czech Republic

    Processor:      any (ST7)
    
    Compiler:       any (Cosmic)

    Copyright (c) 2005 STMicroelectronics.

    THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
    EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTY
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK
    AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE
    PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
    REPAIR OR CORRECTION.

*******************************************************************************/

/****************************** Revision History *******************************
    
    Date        Name            Description
    
*******************************************************************************/

#ifndef STDTYPES_HEADER
#define STDTYPES_HEADER

/*
  File version information
*/
#define STDTYPES_H_MAJOR_VERSION  1
#define STDTYPES_H_MINOR_VERSION  0
#define STDTYPES_H_PATCH_VERSION  0
#define STDTYPES_H_BUILD_REVISION "$Revision: 1.2.6.2 $"


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Platform_Types.h"
#include "Compiler.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/**
*	ST7 Status message structure
*/
typedef union {
		struct ST7_ST{ 
				bool EN_CS_WU1;
				bool EN_CS_WU2;
				bool WU1_state;
				bool WU2_state;
				bool DRV_state;
				bool WK_LIN;
				bool WK_WU1;
				bool WK_WU2;
				
				uint8 DEV_State:2;	
				bool WDC_RefreshStarted;
				bool WDC_RefreshEnabled;				
				bool WDC_RefreshChanged;
				bool WDC_LOW_timing;
				bool WDC_LOW_fail;
				bool SPI_slow;				/* Slow mode of SPI enabled */
		}bit;
		uint8 byte[2];
}APP_STATUS;

typedef enum {		RUN,
						GO_V1, 
						GO_V1_AWU,
						NO_INFO
				} OP_MODE_TYPE;
				
/*typedef enumm {
					DISBALE,
					DRV,
				MON} DRV_MODE_TYPE;
				*/
				
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
void ST7_SendStatus(bool onlyIfChanged);
void SET_OP_Mode(OP_MODE_TYPE mode);
/*void SetDRVMode(DRV_MODE_TYPE mode);
DRV_MODE_TYPE GetDRVMode(void);*/


#endif