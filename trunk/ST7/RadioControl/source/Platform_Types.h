/******************************************************************************/
/*! Project Name:   L9952 driver
    @file           Platform_Types.h 
    @version        $Revision: 1.3.6.2 $
    @date           $Date: 2009/05/22 06:37:55 $
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

#ifndef PLATFORM_TYPES_H 
#define PLATFORM_TYPES_H  

/*
  File version information
*/
#define PLATFORM_H_MAJOR_VERSION  1
#define PLATFORM_H_MINOR_VERSION  0
#define PLATFORM_H_PATCH_VERSION  0
#define PLATFORM_H_BUILD_REVISION "$Revision: 1.3.6.2 $"


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/


/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* 
  CPU register type width
*/
#define CPU_TYPE_8        8                        
#define CPU_TYPE_16       16                        
#define CPU_TYPE_32       32  

/* 
  Bit order definition
*/
#define MSB_FIRST         0                 /* Big endian bit ordering        */
#define LSB_FIRST         1                 /* Little endian bit ordering     */

/* 
  Byte order definition
*/
#define HIGH_BYTE_FIRST   0                 /* Big endian byte ordering       */
#define LOW_BYTE_FIRST    1                 /* Little endian byte ordering    */

/* 
  Word order definition
*/
#define HIGH_WORD_FIRST   0                 /* Big endian word ordering       */
#define LOW_WORD_FIRST    1                 /* Little endian word ordering    */


/*
  Platform type and endianess definitions for ST7
*/
#define CPU_TYPE            CPU_TYPE_8
#define CPU_BIT_ORDER       MSB_FIRST
#define CPU_BYTE_ORDER      HIGH_BYTE_FIRST  /* switchable to LOW_BYTE_FIRST  */
#define CPU_WORD_ORDER      HIGH_WORD_FIRST  /* switchable to LOW_WORD_FIRST  */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*
  AUTOSAR integer data types
*/
typedef signed char         sint8;          /*        -128 .. +127            */
typedef unsigned char       uint8;          /*           0 .. 255             */
typedef signed int          sint16;         /*      -32768 .. +32767          */
typedef unsigned int        uint16;         /*           0 .. 65535           */
typedef signed long         sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long       uint32;         /*           0 .. 4294967295      */
typedef float               float32;
typedef double              float64;

typedef unsigned int        uint8_least;    /* At least 8 bit                 */
typedef unsigned int        uint16_least;   /* At least 16 bit                */
typedef unsigned long int   uint32_least;   /* At least 32 bit                */
typedef signed int          sint8_least;    /* At least 7 bit + 1 bit sign    */
typedef signed int          sint16_least;   /* At least 15 bit + 1 bit sign   */
typedef signed long int     sint32_least;   /* At least 31 bit + 1 bit sign   */

typedef _Bool               bool;           /* for use with TRUE/FALSE        */
typedef unsigned char       BitType;        /* for use in bit fields          */
typedef struct
  {
   BitType b0 : 1;
   BitType b1 : 1;
   BitType b2 : 1;
   BitType b3 : 1;
   BitType b4 : 1;
   BitType b5 : 1;
   BitType b6 : 1;
   BitType b7 : 1;
  }								BitField8_Type;

/*
  Data type for use in bit fields
  Example:
  typedef struct
  {
    BitType b0 : 1;
    BitType b1 : 1;
    BitType b2 : 1;
    BitType b3 : 1;
    BitType b4 : 1;
    BitType b5 : 1;
    BitType b6 : 1;
    BitType b7 : 1;
  } BitField8_Type;
*/  

#ifndef TRUE                                             /* conditional check */
 #define TRUE      ((bool) !FALSE)
#endif

#ifndef FALSE                                            /* conditional check */
 #define FALSE     ((bool) 0)
#endif


#ifndef true                                             /* conditional check */
 #define true      ((bool)!false)
#endif

#ifndef false                                            /* conditional check */
 #define false     ((bool) 0)
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/


#endif /* PLATFORM_TYPES_H */

