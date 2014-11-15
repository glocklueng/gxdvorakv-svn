// ****************************************************************************
// Project Name:    	  AUTOSAR 
// Filename:            compiler.h 
// Processor:           ST7
// Compiler:            Cosmic 4.5
// Date(dd.mm.yyyy):    $Date: 2007/12/06 14:32:13 $
// Author(s):           
// ***************************** Revision History *****************************
// Date:          Name         Description 
//
// ****************************************************************************

/********************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING
 * CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER
 * FOR THEM TO SAVE TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT
 * BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES
 * WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE
 * AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED
 * HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************/

#ifndef COMPILER_H 
#define COMPILER_H  

/*******************************************************************************
**                      Include Section
*******************************************************************************/
#define   _COSMIC_
#include "ST7FLITEU0ICD.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/*
  File version information
*/
#define COMPILER_MAJOR_VERSION  4
#define COMPILER_MINOR_VERSION  5
#define COMPILER_PATCH_VERSION  0

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define ROM_MEM   const
#define _STATIC_  static

#ifndef NULL_PTR
 #define NULL_PTR  ((void *)0)                       
#endif                                

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#define Trap				  	{_asm ("TRAP");}    
#define Halt				  	{_asm ("HALT");}
#define EnableInterrupts   {_asm ("RIM");}
#define DisableInterrupts  {_asm ("SIM");}


#endif /* COMPILER_H */

