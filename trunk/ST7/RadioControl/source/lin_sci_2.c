/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/lin_sci_2.c,v 1.4.6.2 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.4.6.2 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: lin_sci_2.c,v $

******************************************************************************/

  										
#include "std_types.h"
#include "debug.h"
#include "lin_sci_2.h"     
//#include "string.h"     


/**
 *		Buffers for serial line
 */                                                                                                      
unsigned char rx_data[SCI2_RX_BUF_COUNT];       
unsigned char tx_data[SCI2_TX_BUF_COUNT];


/**
 *		Pointer for the serial RX buffer for writing
 */	
int rx_write_pointer;  

/**
 *		Pointer for the serial RX buffer for reading
 */	
int rx_read_pointer;       

/** 
 *
 */
int tx_write_pointer;

/**
 *
 */
int tx_read_pointer;

/**                     
 *			0  - waiting
 * 	   1  - 1st byte - action identifier received, storing 2nd byte
 *			2	- 2nd byte - reg. adr/ command received
*			3	- 3rd byte - reg. adr/ command received 
 *			4	- 4th byte - data Hi byte received, storing the 5th byte - (data Lo byte) 
 *					when data are stored	to buffer, the status 4 is changed to 0
 */
volatile unsigned char sciStatus;
 
/**
 *    true, if any complete command is in the serial buffer ready to read
 */ 
bool dataReady;  

/**
 *     true if any data are in the tx buffer ready to send
 */
volatile bool sending; 

/**
 *    available command codes list
 */                               
const unsigned char commandsCodes[]={				0x21,
													0x22,
													0x02,
													0x07,
													0x62,
													0x60,
													0x7f,
                                       0};
                       
      
/*****************************************************************************
 * Name : SCI_Init	
 * Input:
 * Output:  
 * Description :   Configure the SCI
 *	Comments :
 *****************************************************************************/   

void LIN_SCI_2_Init (void){
     	 //CONTROL REGISTER 1:
		SCI2CR1	= 0x00;		//  OK     
		//BAUD RATE REGISTER:           	
		SCI2BRR	= 0xC0;		//11 000 000     11 00 0000     
		//RECEIVE PRESCALER REGISTER:
		SCI2ERPR = 0x00;		//disabled
		//TRANSMIT PRESCALER REGISTER:
		SCI2ETPR = 0x00;		//disabled     
		//CONTROL REGISTER 2:
		SCI2CR2	= 0x2C;		//  0010 1100
		//CONTROL REGISTER 3:
		SCI2CR3	= 0x00;
	
		SCI2SR;
		SCI2DR;	                
		rx_write_pointer = 0;    
		rx_read_pointer = 0;    
		tx_write_pointer = 0;    
		tx_read_pointer = 0;    
		
		dataReady = false; 
		sending = false;

}       


/*****************************************************************************
 * Name : 	   LINSCI_2_Interrupt
 * Input:
 * Output:  
 * Description :   SCI Interrupt Routine
 *	Comments :
 *****************************************************************************/

@interrupt void LINSCI_2_Interrupt (void){  

	unsigned char status;
	status = SCI2SR; 
	if( status & RDRF ) {   
  		if(rx_write_pointer >= SCI2_RX_BUF_COUNT){
			rx_write_pointer=0;
		}
		//	data = SCI1DR;                    		
      rx_data[rx_write_pointer] = SCI2DR;	
    //  Trap;
      switch (sciStatus){
      	case 0:   
      	//	Trap;
		      if(testID( rx_data[rx_write_pointer]) ){		      	
		        	rx_write_pointer++;
             	sciStatus=1;
	      	}      	
      		break;
      	case 1:      // 2,3,4 byte receiving
      	case 2: 
			case 3:       	
				  	rx_write_pointer++;
             	sciStatus++;
             	break;      		    
      	case 4:      // 5 byte receiving
              	rx_write_pointer++;
             	sciStatus=0;
             	dataReady = true;      					
      		break;            	
      }      
   }                          
   
//-----------------------------------------------------   
   if (status & TDRE){ 
   //	Trap;
        if(tx_read_pointer != tx_write_pointer){
        		SCI2DR = tx_data[tx_read_pointer++];
	  			// test for the last byte
	        	if(tx_read_pointer == tx_write_pointer){
	        		SCI2CR2  &= ~TCIE;	        	
					sending = false;                	
	        	}else {
		        	sending = true;        
	        	}
            // test if the pointer is at the end of the buffer
        		if (tx_read_pointer >= SCI2_TX_BUF_COUNT){
        			tx_read_pointer=0;
        		}
        }else {    // this can never be
        		sending= false;	
        		SCI2CR2  &= ~TCIE;
        }
   }
}
  
  
/*****************************************************************************
 * Name : SCI_test
 * Input:
 * Output:  
 * Description :   Test if the command ID is in the available characters set
 *	Comments :
 *****************************************************************************/        
@stack bool testID(uint8 tmpId){
                             
	unsigned char* codes = commandsCodes;
 	while(*codes!=0){
		if(tmpId == *codes++){
		 	return true;
		}
   }
   return false;
 //return true;   /** debug **/
 
}      
  
  
  
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   

@stack void putchar(uint8 c){
 
	if(sending){   
   	SCI2CR2  |= TCIE;
		tx_data[tx_write_pointer++]=c;
		if(tx_write_pointer >= SCI2_TX_BUF_COUNT){
			tx_write_pointer = 0;
		}
	}else {
		while (!(SCI2SR & TDRE));		
		SCI2DR = c;	
		sending = true;
	}	
}
        
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool SCI_GetDataReady(){
	 return dataReady;
}  

/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool SCI_IsTransmitFinished(){
	 return sending;
}  


/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool SCI_GetNextPacket(uint8* data){  
	int tmp = rx_read_pointer;
	unsigned char j;
//	Trap;
 	while(!testID(rx_data[tmp])){ 	   	  		
		if (tmp != rx_write_pointer ){
			   if (tmp++ >= SCI2_RX_BUF_COUNT)
			   	tmp = 0;
		}else{   
			//	rx_read_pointer=rx_write_pointer=0;
				return false;
		}
 	}      	
//	Trap;
  	for (j=0;j<5;j++){
 	  	 	if (tmp==rx_write_pointer){
 	  	 		 //rx_read_pointer=rx_write_pointer;   
 	  	 		dataReady=false;
 	  	 	 	return false;
 	  	 	}else{
 	  	 		dataReady=true;
 	  	 	}
 	  	 	data[j]=rx_data[tmp];

 	  	 	if (++tmp >= SCI2_RX_BUF_COUNT){
 	  	 		tmp = 0;
 	  	 	}
  	} 
  	if(tmp == rx_write_pointer){
		rx_write_pointer=rx_read_pointer;//=0;
		dataReady= false;	 	
	}else{
	 	rx_read_pointer=tmp; 
 		dataReady=true;
	}
 	return true;
}  
 
 
/*****************************************************************************
 * Name : 	
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   
bool SCI_SendData(uint8* stByte){

		putchar(*stByte++); 			
		putchar(*stByte++); 			
		putchar(*stByte++); 			
		putchar(*stByte++); 			
		putchar(*stByte++); 					
		return true; 	     
}                  

bool SCI_SendData_b(uint8 byte0,uint8 byte1,uint8 byte2,uint8 byte3,uint8 byte4){

		putchar(byte0); 			
		putchar(byte1); 			
		putchar(byte2); 			
		putchar(byte3); 			
		putchar(byte4); 					
		return true; 	     
}                  

/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

