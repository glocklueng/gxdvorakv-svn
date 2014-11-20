/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Door Module Application Board

$Header: c:\CVS_REPOSITORY/DoorModuleAppBoard/ST7/source/L9952.h,v 1.5 2008/11/18 14:37:35 vaclav dvorak Exp $

MODULE	:				$Id: L9952.h,v 1.5 2008/11/18 14:37:35 vaclav dvorak Exp $
VERSION  : 				$Revision: 1.5 $

DATE 		: 				$Date: 2008/11/18 14:37:35 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	
	
	Revision 1.4.2.1  2007/09/13 12:50:17  vaclav dvorak
	d support of the flash mode
	@
	text
	@d1 1
	a1 1
	/**************	
	Revision 1.4  2006/05/05 12:10:04  vaclav dvorak
	- changed header
	- corrected PWM2 control - current measurement didn't work on rev. 1.3.
	
        	      	
		21.3.2005	changed register type structure

******************************************************************************/    
                                                                            
#ifndef L9952_H
#define L9952_H    

#define SPI_CR0 0
#define SPI_CR1 1
#define SPI_CR2 2


/*---TYPES---*/
                     
typedef union {
		struct REG_0_WR_52{                   
	       	// byte 0	
					unsigned char  rel2:1;		
          unsigned char onV2:2;		          
         	unsigned char	 trig:1;		
					unsigned char  goVbat:1;		                           
	        unsigned char  goV1:1;		
					unsigned char adr:2;
					// byte 1		
					unsigned char HS32:1;
					unsigned char HS40:1;	
			 		unsigned char HS41:1;		
          unsigned char HS42:1;		
          unsigned char outHS0:1;		                           
          unsigned char outHS1:1;		
          unsigned char outHS2:1;		
          unsigned char rel1:1;
					// byte 2 
					unsigned char HS10:1;
					unsigned char HS11:1;          
		   		unsigned char HS12:1;
					unsigned char HS20:1;
					unsigned char HS21:1;
          unsigned char HS22:1;
					unsigned char HS30:1;
			    unsigned char HS31:1;		
		}bit; 
		unsigned char byte[3];  
	} L9952_CR0_TYPE;
      
	
typedef union {	
	struct REG_1_WR_52{                   
	       	// byte 0	
          unsigned char T11:1;		                           
         	unsigned char T12:1;		
          unsigned char T13:1;		                           
	        unsigned char T20:1;		
          unsigned char Int_en:1;		
					unsigned char clr:1;	
	        unsigned char adr:2;
					// byte 1		
					unsigned char U0:1;
					unsigned char U1:1;	
			 		unsigned char U2:1;		
          unsigned char U3:1;		
					unsigned char Looping:3;		                                     
          unsigned char T10:1;
					// byte 2
					unsigned char W0:1;          
		   		unsigned char W1:1;
					unsigned char W2:1;
					unsigned char W3:1;
					unsigned char W4:1;
					unsigned char W5:1;					
					unsigned char W6:1;
			    unsigned char W7:1;		
		}bit; 
		unsigned char byte[3];  
	} L9952_CR1_TYPE;
 
typedef union {	
		struct REG_2_WR_52{                   
	       	// byte 0	               
         	unsigned char IC4:2;		          
	        unsigned char LINslope:1;		
          unsigned char LSOVUV:1;		
          unsigned char _res:2;
	        unsigned char adr:2;				
					// byte 1		
					unsigned char rstLev:2;				 		
          unsigned char IC1:2;		
          unsigned char IC2:2;		
          unsigned char IC3:2;          
					// byte 2
					unsigned char OLT_HS1:1;          
		   		unsigned char OLT_HS2:1;
					unsigned char OLT_HS3:1;
					unsigned char OLT_HS4:1;
					unsigned char Vlock:1;
					unsigned char O_HSrec:1;
					unsigned char LinPU:1;		
					unsigned char TXDTOut:1;
		}bit; 
		unsigned char byte[3];  
	} L9952_CR2_TYPE;
      	



typedef union {
		struct REG_0_RD_52{                   
	       	// byte 0	
           unsigned char WU4:1;		
           unsigned char INH:1;		                           
         	 unsigned char LIN:1;		
          unsigned char coldStart:1;		                           
	        unsigned char _res:2;		
	        unsigned char glob_err:2;
					// byte 1		
					unsigned char HS4OC:1;
					unsigned char O_HSOC:1;
			 		unsigned char rel1:1;
					unsigned char rel2:1;
          unsigned char V2:1;
          unsigned char WU1:1;
          unsigned char WU2:1;
          unsigned char WU3:1;
					// byte 2
					unsigned char O_HS1OL:1;          
		   		unsigned char O_HS2OL:1;
					unsigned char O_HS3OL:1;
					unsigned char O_HS4OL:1;
					unsigned char O_HSOL:1;
					unsigned char HS1OC:1;
					unsigned char HS2OC:1;
			    unsigned char HS3OC:1;
		}bit; 
		unsigned char byte[3];  
	} L9952_SR0_TYPE;


typedef union {
		struct REG_1_RD_52{                   
	       		// byte 0	
          unsigned char trig:1;		
          unsigned char SHTgnd:1;		                           
         	unsigned char SHTbat:1;		
          unsigned char domTXD:1;		                           
	        unsigned char _res:2;		
	        unsigned char glob_err:2;
					// byte 1		
					unsigned char ST1:1;
					unsigned char Restarts5V:3;			 		
          unsigned char	WD_reset:4;          
					// byte 2
					unsigned char OV:1;
		   		unsigned char UV:1;
					unsigned char TW:1;
					unsigned char TSD1:1;
					unsigned char TSD2:1;
					unsigned char Vcc1Fail:1;
					unsigned char Vcc2Fail:1;
					unsigned char ST0:1;
		}bit; 
		unsigned char byte[3];  
	} L9952_SR1_TYPE;

              
                                                                                  
// *---FUNCTIONS---*/
void 	L9952_RegInit(void);
//void	L9952_Init(void);   
void  L9952_RefreshWDC(void); 
//void 	L9952_SetRegister(unsigned char regNumber ,unsigned char* value);   
void 	L9952_RefreshRegister(unsigned char regNumber);
   

                                 
void L9952_SwitchToVbatSleep(void);                                 


 

/*---CONSTANTS---*/


#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/
