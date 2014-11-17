/**************** (c) 2002 STMicroelectronics **********************

PROJECT  :    
COMPILER : 

MODULE  :  lib.h
VERSION : 

CREATION DATE : 01.2001

AUTHOR : CMG 8-bit Micro Application Team 

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

DESCRIPTION : 

 ******************************************************************************
 THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. ST MICROELECTRONICS
 SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES
 WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.
 *****************************************************************************/

/* PUBLIC DECLARATIONS *******************************************************/

#ifndef LIB_H
#define LIB_H
            
/*--------------------------STANDARD TYPE DEFINITION-------------------------*/
typedef unsigned char u8;  				/* unsigned 8 bit type definition */
typedef signed char	  s8;  				/* signed 8 bit type definition */
typedef unsigned int  u16; 				/* unsigned 16 bit type definition */
typedef signed int	  s16; 				/* signed 16 bit type definition */
typedef unsigned long u32; 				/* unsigned 32 bit type definition */
typedef signed long	  s32; 				/* signed 32 bit type definition */
                                       
typedef union {							/* unsigned 16 bit type for 8 & 16 */
          u16 w_form;					/* bit accesses: 16> var.w_form    */
          struct {						/* 8> var.b_form.high/low          */
                  u8 high, low;
          } b_form;
  } TwoBytes;

/*--------------------------------BIT ACCESSES-------------------------------*/
#define SetBit(VAR,Place)         ( VAR |= (1<<Place) )
#define ClrBit(VAR,Place)         ( VAR &= ((1<<Place)^255) )
#define AffBit(VAR,Place,Value)   ((Value) ? \
                                   (VAR |= (1<<Place)) : \
                                   (VAR &= ((1<<Place)^255)))
#define MskBit(Dest,Msk,Src)      ( Dest = (Msk & Src) | ((~Msk) & Dest) )

#define ValBit(VAR,Place)         (VAR & (1<<Place))

/*--------------------------------BYTE ACCESSES-------------------------------*/
#ifdef __HIWARE__
 #define EnableInterrupts   {__asm RIM;}
 #define DisableInterrupts  {__asm SIM;}
#else
 #ifdef __CSMC__
  #define EnableInterrupts   {_asm ("RIM");}
  #define DisableInterrupts  {_asm ("SIM");}
 #else
  #error"Unsupported Compiler!"	/* Compiler Defines not found! */
 #endif
#endif

#endif
/*** (c) 2002 STMicroelectronics ****************** END OF FILE ***/
