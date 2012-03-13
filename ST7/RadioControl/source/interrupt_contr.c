/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/interrupt_contr.c,v 1.3.2.1 2007/12/06 14:32:13 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.3.2.1 $

DATE 		: 				$Date: 2007/12/06 14:32:13 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: interrupt_contr.c,v $
	Revision 1.3.2.1  2007/12/06 14:32:13  vaclav dvorak
	empty log message ***
	@
	te	
	Revision 1.3  2007/10/25 06:56:50  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/

#include "std_types.h"
#include "interrupt_contr.h"

/*-----------------------------------------------------------------------------
ROUTINE NAME : ITC_Init
INPUT/OUTPUT : None

DESCRIPTION  : Configure the Interrupt Controller Module

COMMENTS     :
-----------------------------------------------------------------------------*/
void ITC_Init(void)
{           
	
	/*ITSPR0	= 0x55;		// 00 01 01 01
	ITSPR1	= 0x55; 
	ITSPR2	= 0x55;    // 01 11  00  01
	ITSPR3	= 0x55;
 */
	DisableInterrupts;
   EICR0 = 0x44; 			//  01 00 01 00    	
   EICR1 = 0x00;
	//*/
	EnableInterrupts;

}       


/*-----------------------------------------------------------------------------
ROUTINE NAME : NMI_Interrupt
INPUT/OUTPUT : None

DESCRIPTION  : NMI Interrupt Service Routine

COMMENTS     : 
-----------------------------------------------------------------------------*/ 
@interrupt void NMI_Interrupt(void)
{  
   
}  /* End of void void NMI_Interrupt(void) */

/******** (c) 2002  STMicroelectronics ****************** END OF FILE ********/
