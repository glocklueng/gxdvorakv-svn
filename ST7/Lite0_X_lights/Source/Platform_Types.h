/******************************************************************************/
/*! Project Name:   
    @file           Platform_Types.h 
    @version        $Revision: 1.3.6.1 $
    @date           $Date: 2007/12/06 14:32:13 $
    @author         Vaclav Dvorak
    
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
typedef unsigned int        BitType;        /* for use in bit fields          */

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

#ifndef true                                             /* conditional check */
 #define true      (!false)
#endif

#ifndef false                                            /* conditional check */
 #define false     ((bool) 0)
#endif


#endif /* PLATFORM_TYPES_H */

