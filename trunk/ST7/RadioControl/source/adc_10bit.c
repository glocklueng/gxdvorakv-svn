/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/adc_10bit.c,v 1.2.6.1 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.2.6.1 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: adc_10bit.c,v $
	Revision 1.2.6.1  2009/05/22 06:37:55  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/


#include "std_types.h"
#include "debug.h"
#include "adc_10bit.h"
     
   

/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   
void ADC_Init(void)
{
	ADCCSR = 0x10;				// slow mode

}       

/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   
uint16 ADC_convert(uint8 channel){
		uint16 result = 0;
   	ADCCSR &= ~0x5f;
   	ADCCSR |= (channel & 0x0f);
   	ADCCSR |= ADON;
   	while (!(ADCCSR & EOC));  
   	result = ADCDRL & 0x03;
   	result |= (((uint16)ADCDRH <<2)&0x03fc) ;
   	ADCCSR &= ~ADON;
		return result;
}



/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

