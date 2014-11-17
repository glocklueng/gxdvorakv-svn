/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				
VERSION  : 				$Revision: 1.4 $

DATE 		: 				$Date: 2007/01/15 14:08:36 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	

******************************************************************************/

#include "std_types.h"
#include "spi.h" 
#include "lib.h"


/*****************************************************************************
 * Name : 	Init_SPI
 * Input: 	None
 * Output:
 * Description : Configure the SPI
 *	Comments :
 *****************************************************************************/
void SPI_Init(void)
{      
	SPICSR = 0x03;			//      
	SPICR = 0x51;			// 1-int    0101 0001   0x72 - disable int.   
	
}       

/*****************************************************************************
 * Name : 	SPI_send
 * Input: 	pointer to 3 byte filed to send via SPI
 * Output:  -      (for without interrupt mode return the received data)
 * Description : 	send the SPI sequence stored in dataIn parameter
 *	Comments :
 *****************************************************************************/   
void SPI_Send(uint8 *dataIn ,uint8 *dataOut){	
	uint8 SPI_pointer;
	
	Chipselect_LO;
	
	for (SPI_pointer=0;SPI_pointer<3;SPI_pointer++){
		SPICSR;   		 
    SPIDR = dataIn[SPI_pointer];                    		
		while(!(SPICSR & SPICSR_SPIF_OR));
		dataOut[SPI_pointer]=SPIDR;    		          		
	}  		
	Chipselect_HI;
}

/*** (c) 2006  STMicroelectronics ****************** END OF FILE ***/










