/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/lin_sci_1.c,v 1.2 2006/10/06 13:04:02 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.2 $

DATE 		: 				$Date: 2006/10/06 13:04:02 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: lin_sci_1.c,v $
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/

#include "std_types.h"
#include "debug.h"
#include "lin_sci_1.h"     

      
/*****************************************************************************
 * Name : SCI_Init	
 * Input:
 * Output:  
 * Description :   Configure the SCI
 *	Comments :
 *****************************************************************************/   

void LIN_SCI_1_Init (void){
     	 //CONTROL REGISTER 1:
		SCI1CR1	= 0x00;		//  OK     
		//BAUD RATE REGISTER:           	
		SCI1BRR	= 0xd2;		//11 010 010     11 00 0000     
		//RECEIVE PRESCALER REGISTER:
		SCI1ERPR = 0x00;		//disabled
		//TRANSMIT PRESCALER REGISTER:
		SCI1ETPR = 0x00;		//disabled     
		//CONTROL REGISTER 2:
		SCI1CR2	= 0x00;		//  1110 1100    00001100
		//CONTROL REGISTER 3:
		SCI1CR3	= 0x00;
	
		SCI1SR;
		SCI1DR;	                
	
}       


/*****************************************************************************
 * Name : 	   LINSCI_1_Interrupt
 * Input:
 * Output:  
 * Description :   SCI Interrupt Routine
 *	Comments :
 *****************************************************************************/   

@interrupt void LINSCI_1_Interrupt (void){  

	unsigned char status;
//	unsigned char data;                        	
	
	status = SCI1SR;
	
   
	if( status & RDRF ) {   
	}

}
  
/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/




