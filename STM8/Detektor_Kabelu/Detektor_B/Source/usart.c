/******************** (c) 2008 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.2 $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
******************************************************************************/

  										
#include <stm8_map.h>
#include "usart.h"     
//#include "string.h"     

/*---CONSTANTS---*/
#define USART_RX_BUF_COUNT 75  
#define USART_TX_BUF_COUNT 75


/**
 *		Buffers for serial line
*/ 
volatile u8 rx_data[USART_RX_BUF_COUNT];       
volatile u8 tx_data[USART_TX_BUF_COUNT];


/**
 *		Pointer for the serial RX buffer for writing
 */	
volatile s16 rx_write_pointer;  

/**
 *		Pointer for the serial RX buffer for reading
 */	
volatile s16 rx_read_pointer;       

/** 
 *
 */
volatile s16 tx_write_pointer;

/**
 *
 */
volatile s16 tx_read_pointer;

/**                     
 *			0  - waiting
 * 	    1  - 1st byte - action identifier received, storing 2nd byte
 *			2	- 2nd byte - reg. adr/ command received
 *			3	- 3rd byte - reg. adr/ command received 
 *			4	- 4th byte - data Hi byte received, storing the 5th byte - (data Lo byte) 
 *					when data are stored	to buffer, the status 4 is changed to 0
 */
typedef enum {WAIT = 0, BYTE_1, BYTE_2, BYTE_3, BYTE_4} USART_RX_STATUS_TYPE;

volatile USART_RX_STATUS_TYPE rxStatus;
 
volatile u8 rxTimeout;
/**
 *    true, if any complete command is in the serial buffer ready to read
 */ 
volatile bool dataReady;  

/**
 *     true if any data are in the tx buffer ready to send
 */
volatile bool sending; 

/**
 *
 */
volatile bool txJam;
/**
 *    available command codes list
 */                               
const u8 commandsCodes[]={	
														STM8A_CMD,
														CAN_SEND,
														CAN_SETUP,
														COMM_TEST,	 
														0};
                       
      
/*****************************************************************************
 * Name : 
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/

void USART_Init (void)
{
    
		USART->BRR2 = 0x00;
		USART->BRR1 = 0x1A;			// for 38400 @ 16MHz		
				
		/*USART->BRR2	= 0x0B;
		USART->BRR1 = 0x08;				// 115200 @16MHz*/
		
	//	USART->BRR2	= 0x00;
	//	USART->BRR1 = 0x0D;				// 115200 @24MHz
		
		USART->CR1 = 0x00;
		USART->CR2 = 0x00 | 	USART_CR2_TIEN | 
													USART_CR2_RIEN | 
													USART_CR2_TEN |
													USART_CR2_REN;
		USART->CR3 = 0x00;
		USART->CR4 = 0x00;
		USART->CR5 = 0x00;
		USART->PSCR = 0x00;
		
		GPIOA->DDR |= 0x20;
		GPIOA->DDR &= (u8)~0x10;
		GPIOA->CR1 |= 0x30;
		
		rx_write_pointer = 0;    
		rx_read_pointer = 0;    
		tx_write_pointer = 0;    
		tx_read_pointer = 0;    
		
		dataReady = FALSE; 
		sending = FALSE;
		txJam = FALSE;
		rxTimeout = 0;

}       


/*****************************************************************************
 * Name : 	   USART_RX_Interrupt
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/

@far @interrupt void USART_RX_Interrupt (void)
{  

	u8 status;
	status = USART->SR; 	
	if (status & USART_SR_OR || status & USART_SR_NF){
		USART->DR;
		rx_write_pointer -= (u8)rxStatus;
		if (rx_write_pointer < 0) rx_write_pointer = 0;
		
		
	}else if( status & USART_SR_RXNE ) {   
  	
			rx_data[rx_write_pointer] = USART->DR;	    
      switch (rxStatus){
      	case WAIT:         	
						if(testID( rx_data[rx_write_pointer]) ){		      	
		        	++rx_write_pointer;
             	rxStatus= BYTE_1;
						}      	
						rxTimeout = 0;
      		break;
      	case BYTE_1:      // 2,3,4 byte receiving
      	case BYTE_2: 
				case BYTE_3:       	
							++rx_write_pointer;
             	++rxStatus;
							rxTimeout = 0;
						break;      		    
      	case BYTE_4:      // 5 byte receiving
							++rx_write_pointer;
             	rxStatus= WAIT;
             	dataReady = TRUE;      					
							rxTimeout = 0;
						break;            	
      }
			if(rx_write_pointer >= USART_RX_BUF_COUNT){
				rx_write_pointer=0;
			}      
  }  
}
   

/*****************************************************************************
 * Name : 	   USART_TX_Interrupt
 * Input:
 * Output:  
 * Description :   
 *	Comments :
 *****************************************************************************/ 
@far @interrupt void USART_TX_Interrupt (void)
{  
	
	u8 status;
	
	status = USART->SR;
	if (status & USART_SR_TXE){ 
      if((tx_read_pointer != tx_write_pointer ) || txJam ){
       		USART->DR = tx_data[tx_read_pointer++];
					txJam = FALSE;
					// test for the last byte
	       	if(tx_read_pointer == tx_write_pointer){
	        		USART->CR2 &= (u8)~USART_CR2_TIEN;	        	
							sending = FALSE;                	
	       	}else {
		        	sending = TRUE;        							
	       	}
          // test if the pointer is at the end of the buffer
       		if (tx_read_pointer >= USART_TX_BUF_COUNT){
        			tx_read_pointer=0;
       		}
			}else {    // this happen if only 1 byte was in queue
       		sending= FALSE;	
       		USART->CR2  &= (u8)~USART_CR2_TIEN;
       }
	}
	/*if (status USART_SR_TC){	
	//    switch to iddle mode
		
	}*/
}
 
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/
void USART_TimeoutHandler()
{
	if (rxStatus != WAIT){
			if (++ rxTimeout > 50){ // 50 ms gone and still waiting - clear RX buffer
				rxTimeout = 0;				
				rx_write_pointer -= (u8)rxStatus;
				if (rx_write_pointer < 0) rx_write_pointer = 0;
				rxStatus = WAIT;
				GPIOI->ODR |= 0x80;
			}		
	}else {
		GPIOI->ODR &= ~0x80;
	}	
}

  
/*****************************************************************************
 * Name : SCI_test
 * Input:
 * Output:  
 * Description :   Test if the command ID is in the available characters set
 *	Comments :
 *****************************************************************************/ 
@stack bool testID(u8 tmpId)
{
                             
	u8* codes = commandsCodes;
 	while(*codes!=0){
		if(tmpId == *codes++){
		 	return TRUE;
		}
   }
   return FALSE;
 //return true;   /** debug **/
 
}      
  
  
  
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/

@stack void putchar(u8 c){
	
	while (txJam);  // cekam na uvolneni fronty pro zapis dalsiho byte
	
	USART->CR2 &= (u8)~USART_CR2_TIEN;	    	// disble interrupt   
	
	if(sending){   			
		
		tx_data[tx_write_pointer++]=c;
		if(tx_write_pointer >= USART_TX_BUF_COUNT){
			tx_write_pointer = 0;
		}	
		// tx_write pointer o kolo dohnal tx_read ponter-> nastavuji overFill flag
		if (tx_write_pointer == tx_read_pointer) txJam = TRUE;
		
	}else {
		while (!(USART->SR & USART_SR_TXE));		
		USART->DR = c;	
		sending = TRUE;
		//USART->CR2  |= USART_CR2_TIEN;
	}	
	
	USART->CR2  |= USART_CR2_TIEN;				// enable interrupt
}
        
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/ 
bool USART_GetDataReady()
{
	 return dataReady;
}  

/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/
bool USART_IsTransmitFinished()
{
	
	if (!sending){
		 if (USART->SR & USART_SR_TC) return true;
			else return false;
			
	}else return false;	 
}  


/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/
bool USART_GetNextPacket(u8* data)
	{  
	s16 tmp = rx_read_pointer;
	u8 j;
 	if (!dataReady) return false;
	
	for (j=0; j<5 ; ++j){
 	  	 	if (tmp==rx_write_pointer){ 	  	 	
 	  	 		dataReady=FALSE;
					data[0]= 0;	// data will be ingnored in case not evaluate result code
 	  	 	 	return FALSE;
 	  	 	}
 	  	 	data[j]=rx_data[tmp];

 	  	 	if (++tmp >= USART_RX_BUF_COUNT){
 	  	 		tmp = 0;
 	  	 	}
  } 
	rx_read_pointer=tmp;
  if(tmp == rx_write_pointer){			
			dataReady= FALSE;	 	
	}
 	return TRUE;
}  
 
 
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/
bool USART_SendData(u8* stByte)
{

		putchar(*stByte++); 			
		putchar(*stByte++); 			
		putchar(*stByte++); 			
		putchar(*stByte++); 			
		putchar(*stByte++); 					
		return TRUE; 	     
}                  

/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/ 
bool USART_SendBytesMessage(u8 b0, u8 b1, u8 b2, u8 b3, u8 b4)
{

		putchar(b0); 			
		putchar(b1); 			
		putchar(b2); 			
		putchar(b3); 			
		putchar(b4); 					
		return TRUE; 	     
}       
/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/

