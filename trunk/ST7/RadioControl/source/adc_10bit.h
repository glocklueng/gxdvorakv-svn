/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/adc_10bit.h,v 1.2.6.1 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.2.6.1 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: adc_10bit.h,v $
	Revision 1.2.6.1  2009/05/22 06:37:55  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.2  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/

#ifndef ADC10_H
#define ADC10_H

#include "std_types.h"

/*---FUNCTIONS---*/

void ADC_Init(void);
uint16 ADC_convert(uint8 channel);  




/*---CONSTANTS---*/
                   
/*---VARIABLES---*/                   


#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

