/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/clock_reset_supply.c,v 1.2 2006/10/06 13:04:02 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.2 $

DATE 		: 				$Date: 2006/10/06 13:04:02 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: clock_reset_supply.c,v $
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/

#include "std_types.h"
#include "debug.h"
#include "clock_reset_supply.h"


/*-----------------------------------------------------------------------------
ROUTINE NAME : CLOCK_Init
INPUT/OUTPUT : None

DESCRIPTION  : Configure the CLOCK , RESET and SUPPLY

COMMENTS     :
-----------------------------------------------------------------------------*/
void CRS_Init (void)
{

}       


#ifdef __HIWARE__				/* test for HIWARE Compiler */
#pragma TRAP_PROC SAVE_REGS		/* additional registers will be saved */
#else
#ifdef __CSMC__					/* test for Cosmic Compiler */
@interrupt						/* Cosmic interrupt handling */
#else
#error"Unsupported Compiler!"	/* Compiler Defines not found! */
#endif
#endif
/*-----------------------------------------------------------------------------
ROUTINE NAME : CSS_Interrupt
INPUT/OUTPUT : None

DESCRIPTION  : CSS Interrupt Routine

COMMENTS     : 
-----------------------------------------------------------------------------*/ 
void CSS_Interrupt (void)
{
}



/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

