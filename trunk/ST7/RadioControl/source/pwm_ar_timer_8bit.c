/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/pwm_ar_timer_8bit.c,v 1.3.6.2 2008/05/05 15:00:31 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.3.6.2 $

DATE 		: 				$Date: 2008/05/05 15:00:31 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: pwm_ar_timer_8bit.c,v $
	Revision 1.3.6.2  2008/05/05 15:00:31  vaclav dvorak
	- comments of files by new	
	Revision 1.3.6.1  2007/12/06 14:32:13  vaclav dvorak
	- comments of files by new	
	Revision 1.3  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/


#include "std_types.h"
#include "pwm_ar_timer_8bit.h" 
#include "timer_8bit.h" 
#include "pwm_timing.h"
#include "comm_commands.h"
                               
                               
/*****************************************************************************
 * Name : 	     ART_Init
 * Input:
 * Output:  
 * Description : Configure the PWM_BRM module
 *	Comments :
 *****************************************************************************/
void ART_Init(void)
{           
}       

  
/*****************************************************************************
 * Name : 	  		ART_Interrupt 
 * Input:
 * Output:  
 * Description :  Auto Reload Timer Interrupt Service Routine
 *	Comments :
 *****************************************************************************/   
@interrupt void ART_Interrupt(void)
{  
   
}  /* End of void void ART_Interrupt(void) */



/*****************************************************************************
 * Name : 	  		
 * Input:
 * Output:  
 * Description :  
 *	Comments :
 *****************************************************************************/   



/******** (c) 2005  STMicroelectronics ****************** END OF FILE ********/