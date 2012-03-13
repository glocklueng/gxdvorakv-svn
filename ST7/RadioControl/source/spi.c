/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/spi.c,v 1.4.6.3 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.4.6.3 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: spi.c,v $
	Revision 1.4.6.3  2009/05/22 06:37:55  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.4.6.2  2007/12/06 14:32:13  vaclav dvorak
	- comments of files by new	

	

******************************************************************************/

#include "std_types.h"
#include "spi.h" 
#include "timer_16bit.h"

//volatile _Bool mirrorEnable;

volatile static bool slowMode;

/*****************************************************************************
 * Name : 	Init_SPI
 * Input: 	None
 * Output:
 * Description : Configure the SPI
 *	Comments :
 *****************************************************************************/
void SPI_Init(void)
{      
	SPICSR = 0x03;			// 00000011  
	SPICR = 0x72;			// 1-int    111 0010   0x72 - disable int.   
	slowMode = false;
	
}       



/*****************************************************************************
 * Name : 	SPI_Interrupt
 * Input: 	None
 * Output:
 * Description : 
 *	Comments :
 *****************************************************************************/
@interrupt void SPI_Interrupt(void)
{       
}


/*****************************************************************************
 * Name : 	SPI_SendSlowMode
 * Input: 	pointer to 3 byte filed to send via SPI
 * Output:        return the received data
 * Description : 	Send the SPI sequence in manual slow mode
 *	Comments :
 *****************************************************************************/   
bool SPI_SendSlowMode(uint8 *dataIn ,uint8 *dataOut){
	
	uint8 SPI_pointer;
	uint8	bit;
	uint8 byteOutTmp; // out to silicon
	uint8 byteInTmp;  // in from silicon
	
	CLK_LO;
	DATAOUT_LO;
	SPICR &= ~0x40;	// stop HW SPI
	TIMER16_SetTimeout(1);
	while (!TIMER16_IsTimeoutExpired());
	TIMER16_SetTimeout(1);
		
	Mirror_LO;
	Chipselect_LO;

	for (SPI_pointer=0;SPI_pointer<3;SPI_pointer++){
		byteOutTmp = dataIn[SPI_pointer];                    
		byteInTmp = 0;		
		while (!TIMER16_IsTimeoutExpired());
		TIMER16_SetTimeout(1);
//Trap;		
		CLK_LO;		
		for (bit = 0; bit <8;bit++){		
				if (byteOutTmp & 0x80){
					DATAOUT_HI;					
				}else {
					DATAOUT_LO;
				}				
				byteOutTmp <<= 1;
				
				while (!TIMER16_IsTimeoutExpired());
				TIMER16_SetTimeout(1);
//Trap;				
				CLK_HI;
				while (!TIMER16_IsTimeoutExpired());
				TIMER16_SetTimeout(1);
//Trap;
				CLK_LO;
				byteInTmp <<= 1;				
				if (IS_DATIN){
					byteInTmp |= 0x80;
				}
		}
		while (!TIMER16_IsTimeoutExpired());
		TIMER16_SetTimeout(3);	
//Trap;		
		dataOut[SPI_pointer]=byteInTmp;
	}
	Mirror_HI;
	Chipselect_HI;
	SPICR |= 0x40;		// start HW SPI*/
}


/*****************************************************************************
 * Name : 	SPI_send
 * Input: 	pointer to 3 byte filed to send via SPI
 * Output:  -      (for without interrupt mode return the received data)
 * Description : 	send the SPI sequence stored in dataIn parameter
 *	Comments :
 *****************************************************************************/   
bool SPI_Send(uint8 *dataIn ,uint8 *dataOut){
	uint8 SPI_pointer;
	
	if (slowMode){
		return SPI_SendSlowMode(dataIn ,dataOut);		
	}
	Mirror_LO;
	Chipselect_LO;
	
	for (SPI_pointer=0;SPI_pointer<3;SPI_pointer++){
		SPICSR;   		 
      SPIDR = dataIn[SPI_pointer];                    
		TIMER16_SetTimeout(200);
		while(!(SPICSR & SPIF)){
			if (TIMER16_IsTimeoutExpired()) return false;  
		}	
		dataOut[SPI_pointer]=SPIDR;    		          		
	}  
		
	Mirror_HI;
	Chipselect_HI;
	return true;
}


/*****************************************************************************
 * Name : 	ST_PI_SendSlowMode
 * Input: 	pointer to 2 byte filed to send via SPI and command byte
 * Output:        return the received data
 * Description : 	Send the SPI sequence in manual slow mode
 *	Comments :
 *****************************************************************************/   
bool ST_SPI_SendSlowMode(	uint8 	commandByte, 	uint8* 	dataIn, 
									uint8* 	globalStatus, 	uint8* 	dataOut, uint8 dataLength){
							
	sint8 SPI_pointer;
	uint8	bit;
	uint8 byteOutTmp; // out to silicon
	uint8 byteInTmp;  // in from silicon
	
	
	CLK_LO;
	DATAOUT_LO;
	SPICR &= ~0x40;	// stop HW SPI

	TIMER16_SetTimeout(1);
	while (!TIMER16_IsTimeoutExpired());
	TIMER16_SetTimeout(1);
		
	Mirror_LO;
	Chipselect_LO;
	// command byte 
	byteOutTmp = commandByte;
	byteInTmp = 0;		
	while (!TIMER16_IsTimeoutExpired());
	TIMER16_SetTimeout(1);
	CLK_LO;		
	for (bit = 0; bit <8;bit++){		
		if (byteOutTmp & 0x80){
			DATAOUT_HI;					
		}else {
			DATAOUT_LO;
		}				
		byteOutTmp <<= 1;
		while (!TIMER16_IsTimeoutExpired());
		TIMER16_SetTimeout(1);

		CLK_HI;				
		while (!TIMER16_IsTimeoutExpired());
		TIMER16_SetTimeout(1);
		CLK_LO;
		byteInTmp <<= 1;				
		if (IS_DATIN){
			byteInTmp |= 0x80;
		}
	}	
	while (!TIMER16_IsTimeoutExpired());
	TIMER16_SetTimeout(3);	
	*globalStatus = byteInTmp;
	// data bytes
		for (SPI_pointer=dataLength-1;SPI_pointer>=0;--SPI_pointer){
		
		byteOutTmp = dataIn[SPI_pointer];                    
		byteInTmp = 0;		
		while (!TIMER16_IsTimeoutExpired());
		TIMER16_SetTimeout(1);
		CLK_LO;		
		for (bit = 0; bit <8;bit++){		
				if (byteOutTmp & 0x80){
					DATAOUT_HI;					
				}else {
					DATAOUT_LO;
				}				
				byteOutTmp <<= 1;
				while (!TIMER16_IsTimeoutExpired());
				TIMER16_SetTimeout(1);
				CLK_HI;
				while (!TIMER16_IsTimeoutExpired());
				TIMER16_SetTimeout(1);
				CLK_LO;
				byteInTmp <<= 1;				
				if (IS_DATIN){
					byteInTmp |= 0x80;
				}			
		}				
		while (!TIMER16_IsTimeoutExpired());
		TIMER16_SetTimeout(3);	
		dataOut[SPI_pointer]=byteInTmp;
	}	
	Mirror_HI;
	Chipselect_HI;
	SPICR |= 0x40;		// start HW SPI*/
}

/*****************************************************************************
 * Name : 	ST_SPI_send
 * Input: 	command byte,pointer to x byte filed to send via SPI, number of the chip
 * Output:  -     
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool ST_SPI_Send(	uint8 	commandByte, 	uint8* 	dataIn, 
						uint8* 	globalStatus, 	uint8* 	dataOut, uint8 dataLength){
	sint8 SPI_pointer;
	if (slowMode){
		return ST_SPI_SendSlowMode(commandByte, dataIn, globalStatus, dataOut, dataLength);		
	}
	Mirror_LO;
	Chipselect_LO;
	//Trap;
	SPICSR;   		 
	SPIDR = commandByte;                    
	TIMER16_SetTimeout(200);
	while(!(SPICSR & SPIF)){
		if (TIMER16_IsTimeoutExpired()) return false;  
	}	
	*globalStatus=SPIDR;    		          		

	for (SPI_pointer= dataLength-1; SPI_pointer >=0 ; --SPI_pointer){
		SPICSR;   		 
		SPIDR = dataIn[SPI_pointer];                    
		TIMER16_SetTimeout(200);
				
		while(!(SPICSR & SPIF)){
			if (TIMER16_IsTimeoutExpired()) return false;  
		}	
		dataOut[SPI_pointer]=SPIDR;   
	}  
	Mirror_HI;
	Chipselect_HI;
	return true;
}

/*****************************************************************************
 * Name : 	ST_SPI_Send_8
 * Input: 	command byte,pointer to 1 byte filed to send via SPI
 * Output:  -     
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool ST_SPI_Send_8(	uint8 	commandByte, 	uint8* 	dataIn, 
							uint8* 	globalStatus, 	uint8* 	dataOut)
{
	return ST_SPI_Send(	commandByte, dataIn, globalStatus,	dataOut, 1U);
}
/*****************************************************************************
 * Name : 	ST_SPI_Send_8
 * Input: 	command byte,pointer to 2 byte filed to send via SPI
 * Output:  -     
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool ST_SPI_Send_16(	uint8 	commandByte, 	uint8* 	dataIn, 
							uint8* 	globalStatus, 	uint8* 	dataOut)
{
	return ST_SPI_Send(	commandByte, dataIn, globalStatus,	dataOut, 2U);
}

/*****************************************************************************
 * Name : 	
 * Input: 	command byte,pointer to 3 byte filed to send via SPI, number of the chip
 * Output:  -     
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool ST_SPI_ReadDevInfo(uint8 address, uint8* globalStatus, uint8*	dataOut){
		
	Mirror_LO;
	Chipselect_LO;

	SPICSR;   		 
	SPIDR = address | 0xC0;;                    
	TIMER16_SetTimeout(200);
	while(!(SPICSR & SPIF)){
		if (TIMER16_IsTimeoutExpired()) return false;  
	}		
	(*globalStatus)=SPIDR;    		          				
	SPICSR;   		 
	SPIDR = 0x00;                    
	TIMER16_SetTimeout(200);
	while(!(SPICSR & SPIF)){
		if (TIMER16_IsTimeoutExpired()) return false;  
	}	
	(*dataOut)=SPIDR;    		          		
	Mirror_HI;
	Chipselect_HI;
}


/*****************************************************************************
 * Name : 	SPI_SetSlowMode
 * Input: 	None
 * Output:
 * Description : Set the slow mode of the SPI for the shortcut test. The SPI 
 *					  sequence will take aprox.5 ms
 *	Comments :
 *****************************************************************************/
void SPI_SetSlowMode(_Bool status){
	if (status){
		slowMode = true;
	}else{
		slowMode = false;
	}	

}

/*****************************************************************************
 * Name : 	SPI_GetMode
 * Input: 	None
 * Output:
 * Description : 		true = slow mode;   false =  fast mode
 *	Comments :
 *****************************************************************************/
bool SPI_GetMode(void){
	if (slowMode){
		return true;
	}else{
		return false;
	}	

}
/*** (c) 2006  STMicroelectronics ****************** END OF FILE ***/










