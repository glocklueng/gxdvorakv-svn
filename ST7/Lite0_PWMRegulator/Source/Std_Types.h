/******************************************************************************/
/*! Project Name:   L9952 driver
    @file           Std_Types.h
    @version        $Revision: 1.2.6.1 $
    @date           $Date: 2007/12/06 14:32:13 $
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
#define STDTYPES_H_BUILD_REVISION "$Revision: 1.2.6.1 $"


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

typedef uint8 Std_ReturnType;

#ifndef STATUSTYPEDEFINED
    #define STATUSTYPEDEFINED
    #define E_OK 0
    typedef unsigned char StatusType; /* OSEK compliance */
#endif

#define E_NOT_OK 1
#define STD_HIGH 1
#define STD_LOW  0
#define ON       1
#define OFF      0

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/


#endif