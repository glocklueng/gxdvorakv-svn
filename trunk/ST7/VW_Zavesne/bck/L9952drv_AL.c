/******************************************************************************/
/*! Project Name:   L9952 driver
    @file           L9952drv_AL.C
    @version        $Revision: 1.3 $
    @date           $Date: 2008/09/15 14:48:36 $
    @author         David Trojek
    @author         Vaclav Dvorak
    @brief          SW driver for ST L9952 device - Adaptation Layer.

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
    05.02.2007  David Trojek    Original Issue

*******************************************************************************/

/*
  File version information
*/
#define L9952DRV_AL_C_MAJOR_VERSION  1
#define L9952DRV_AL_C_MINOR_VERSION  0
#define L9952DRV_AL_C_PATCH_VERSION  0
#define L9952DRV_AL_C_BUILD_REVISION "$Revision: 1.3 $"

/*
This file is originally dummy. It is prepared for implementation of adaptation
layer for arbitrary user SPI interface.
*/

#include "L9952drv_AL.h"

#if L9952DRV_AL_C_MAJOR_VERSION != L9952DRV_AL_H_MAJOR_VERSION
    #error "Wrong version of L9952drv_AL.h"
#endif


/******************************************************************************/
/*! @fn         void SPI_Send (uint8 *DataTX, uint8 *DataRX)
    @param[in]  DataTX  defines pointer to 3 byte data to be transmitted via SPI
    @param[out] DataRX  defines pointer to 3 byte data to be received via SPI
    @brief 
Generally the function should be included from some low level SPI driver. 
If such direct compatible function does not exist, the function should be
created in L9952drv_AL.c file. 
Number of transmitted data via SPI: 3 bytes (24bit). 
Data order for transmitting: First is send the first byte, than the second and
than the third one. MSB is always transmitted as the first bit from the byte
via SPI. Data order for received data is the same as for transmitted. 
This function is originally implemented as dummy function in L9952drv_AL.c file.
*/
/******************************************************************************/

/*void SPI_Send (uint8 *DataTX, uint8 *DataRX) {

    ;

}*/
