/******************** (c) 2009 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.1 $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
$log:$
******************************************************************************/



 										
#include <stm8_map.h>
#include "adc.h"
#include "common.h"


/*****************************************************************************
 * Name : 	ADC_Init
 * Input: 	
 * Output:
 * Description : Configure the A/D converter
 *	Comments :
 *****************************************************************************/
void ADC_Init(void)
{      
		ADC->CR1 = 0x00;
		ADC->CR2 = 0x00 | ADC_CR2_ALIGN; // right alignment  (16bit usage)
		ADC->CSR = 0x00;
		ADC->CR1 |= ADC_CR1_ADON;
}       


/*****************************************************************************
 * Name : 	ADC_GetValue
 * Input: 	
 * Output:
 * Description : Convert A/D value on slected chanel and Return 
 *	Comments :
 *****************************************************************************/
const u16 ADC_GetValue(const u8 chanel)
{
		u16 result = 0;
		/* Select the ADC channel*/
		ADC->CR2 |= ADC_CR2_ALIGN; // right alignment  (16bit usage)
		ADC->CSR &= (u8)(~0x0F);  
		ADC->CSR |= (u8)(chanel & 0x0F);  
		NOP();
		NOP();
		NOP();
		NOP();
		
		/* Start of conversion */
		ADC->CR1 |= ADC_CR1_ADON;
		/* Wait for End Of Conversion */
		while (!(ADC->CSR & ADC_CSR_EOC));
		result= ADC->DRL;
		result+= ((u16)ADC->DRH) <<8;
		ADC->CSR &= ~ADC_CSR_EOC;
		return result;
}


/*****************************************************************************
 * Name : 	ADC_GetValue
 * Input: 	
 * Output:
 * Description : Convert A/D value on slected chanel and Return 
 *	Comments :
 *****************************************************************************/
const u8 ADC_GetValue8b(const u8 chanel)
{
		u8 result = 0;
		/* Select the ADC channel*/
		ADC->CSR &= (u8)(~0x0F);  
		ADC->CSR |= (u8)(chanel & 0x0F);  
		ADC->CR2 &= ~ADC_CR2_ALIGN; // left alignment  (8bit usage)
		
		/* Start of conversion */
		//ADC->CR1 |= ADC_CR1_ADON;
		ADC->CR1 |= ADC_CR1_ADON;
		/* Wait for End Of Conversion */
		while (!(ADC->CSR & ADC_CSR_EOC));
		result= ADC->DRH;
		ADC->CSR &= ~ADC_CSR_EOC;
		return result;
}
/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/










