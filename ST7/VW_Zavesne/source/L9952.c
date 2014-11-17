/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Door Module Application Board

$Header: c:\CVS_REPOSITORY/DoorModuleAppBoard/ST7/source/L9952.c,v 1.7 2008/11/18 14:37:35 vaclav dvorak Exp $

MODULE	:				$Id: L9952.c,v 1.7 2008/11/18 14:37:35 vaclav dvorak Exp $
VERSION  : 				$Revision: 1.7 $

DATE 		: 				$Date: 2008/11/18 14:37:35 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: L9952.c,v $
	Revision 1.7  2008/11/18 14:37:35  vaclav dvorak
	 - merged DZ70 + main Trunk
	
	Revision 1.6.2.1  2007/09/13 12:50:17  vaclav dvorak
	anged header
	- corrected PWM2 control - current measurement d	
	Revision 1.6  2006/09/13 14:09:52  vaclav dvorak
	- corrected wakeu from V1 standby
	- added coldStart Signalisation
	- changed startup dequence CR2-CR1-CR0 for L9952
	
	Revision 1.5  2006/05/05 12:10:04  vaclav dvorak
	- changed header
	- corrected PWM2 control - current measurement didn't work on rev. 1.3.
	
        	
	2005-05-18	add sending of the power wondow current

******************************************************************************/

#include "std_types.h"
#include "lib.h"
#include "L9952.h"
#include "spi.h"   




/**
 * 	L9952 SPI frames definition
 */
volatile L9952_CR0_TYPE L9952_cr0;
volatile L9952_CR1_TYPE L9952_cr1;
volatile L9952_CR2_TYPE L9952_cr2;
volatile L9952_SR0_TYPE L9952_sr0;
volatile L9952_SR1_TYPE L9952_sr1;



/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/   
void L9952_RegInit(void){  
		uint8 i;
	for (i = 0U; i < 3U; i++){
        L9952_cr0.byte[i] = 0U;
        L9952_cr1.byte[i] = 0U;
        L9952_cr2.byte[i] = 0U;
        L9952_sr0.byte[i] = 0U;
        L9952_sr1.byte[i] = 0U;

	}
   L9952_cr1.byte[0] = (uint8)(0x01U << 6);
   L9952_cr2.byte[0] = (uint8)(0x02U << 6);
}	
	/*
	SPI_Send(L9952_cr2.byte ,L9952_sr0.byte,L9952);		
	if (L9952_sr0.bit.coldStart){		
		coldStart	= true;
	}else{ 
		coldStart = false;
	}
	
	SPI_Send(L9952_cr1.byte ,L9952_sr1.byte,L9952);
	L9952_cr0.bit.trig = L9952_sr1.bit.trig;
	//}else
	//L9952_cr0.bit.trig = 0;
 */

/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/    
void  L9952_RefreshWDC(void){
                                                              
	L9952_cr0.bit.trig ^= 0x01;  
	SPI_Send(L9952_cr0.byte, L9952_sr0.byte);  		

}


/*****************************************************************************
 * Name : 	 L9952_SetRegister  
 * Input:
 * Output:  
 * Description :   Set the L9952 register value and send it to the L9952 via SPI
 *	Comments :
 *****************************************************************************
void L9952_SetRegister(unsigned char regNumber ,unsigned char* value){
	_Bool trig;
   switch (regNumber){
   	case 0:  
   	//	Trap;
   		trig = L9952_cr0.bit.trig; 
   		if (L9952_cr0.bit.rel1 != (value[1]& 0x80)){
   		 	TIMER8_startPWindow();
   		}
   		if (L9952_cr0.bit.rel2 != (value[0]& 0x01)){
   		 	TIMER8_startPWindow();
   		}   		
	   	memcpy (&L9952_cr0.byte[0],value,3);
   		L9952_cr0.bit.trig = trig;
   		L9952_cr0.bit.adr = 0;   	
			
			SPI_Send(L9952_cr0.byte ,L9952_sr0.byte);				
			
	    break;
		case 1:
	  	  	memcpy (&L9952_cr1.byte[0],value,3);  
	  	   L9952_cr1.bit.adr = 1;
   		SPI_Send(L9952_cr1.byte ,L9952_sr1.byte);
	    	break;
	  	case 2:
			memcpy (&L9952_cr2.byte[0],value,3);
			L9952_cr2.bit.adr = 2;
   		SPI_Send(L9952_cr2.byte ,L9952_sr0.byte,L9952);			
	    	break;
	  	case 3:
	  		memcpy (&L9952_cr3.byte[0],value,3);
	  		L9952_cr3.bit.adr = 3;	
   		SPI_Send(L9952_cr3.byte,L9952_cr3.byte,L9952);	  		
	    	break;
	}
}*/
 
 
/*****************************************************************************
 * Name : 	 L9952_RefreshRegister  
 * Input:
 * Output:  
 * Description :   Set the L9952 register value and send it to the L9952 via SPI
 *	Comments :
 *****************************************************************************/    
void L9952_RefreshRegister(unsigned char regNumber){
 	switch (regNumber){
   	case SPI_CR0:  		
			SPI_Send(L9952_cr0.byte ,L9952_sr0.byte);						
	    break;
	  case SPI_CR1:		 
   		SPI_Send(L9952_cr1.byte ,L9952_sr1.byte);
	    break;
	  case SPI_CR2:
   		SPI_Send(L9952_cr2.byte ,L9952_sr0.byte);			
	   	break;
		default:
		return;
	} 
}   






/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : 
 *	Comments :
 *****************************************************************************/     
void L9952_SwitchToVbatSleep(void){
	
   L9952_cr0.bit.goVbat = 1;
 	SPI_Send(L9952_cr0.byte ,L9952_sr0.byte);
}



 

 
/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/
