/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/ports.c,v 1.5.2.5 2009/05/22 06:37:55 Vaclav dvorak Exp $

MODULE   :  			ports.c
VERSION  : 				$Revision: 1.5.2.5 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: ports.c,v $
	
******************************************************************************/
#include "std_types.h"
#include "debug.h"
#include "ports.h"  



/*****************************************************************************
 * Name : 			PORTS_Init  
 * Input:        	None
 * Output:       	None
 * Description : 	Configure the ports
 *	Comments :		1 = output, 0 = input
 *                   
 *****************************************************************************/   
void PORTS_Init(void)
{

	PADDR   = 0x00 | bit1;
	PAOR	 	= 0x00 | bit1;

  PBDDR		= 0x00;
	PBOR    = 0x00 | bit2;		//EI on INput A

  PCDDR   = 0x00 | bit7 |bit2 ;
	PCOR    = 0x00 | bit7 |bit2;
	
	PDDDR   = 0x00 | bit2 | bit1;		
	PDOR    = 0x00 | bit2 | bit1 | bit0; // EI on INput B
}


/*****************************************************************************
 * Name : 	  		PORTS_0_Interrupt 
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/ 
@interrupt void PORTS_0_Interrupt(void)
{

}

/*****************************************************************************
 * Name : 	   	PORTS_1_Interrupt
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/ 
@interrupt void PORTS_1_Interrupt(void)
{                    
 //do nothing on INterrupt, continue normal mode
}

/*****************************************************************************
 * Name : 	     	PORTS_2_Interrupt
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/ 
@interrupt void PORTS_2_Interrupt(void)
{  

}

/*****************************************************************************
 * Name : 	     	PORTS_3_Interrupt
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/ 
@interrupt void PORTS_3_Interrupt(void)
{    
 //do nothing on INterrupt, continue normal mode		
}


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/


