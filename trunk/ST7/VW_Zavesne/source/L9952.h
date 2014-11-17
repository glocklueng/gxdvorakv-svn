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
					_Bool  rel2;		
          unsigned char onV2:2;		          
         	_Bool	 trig;		
					_Bool  goVbat;		                           
	        _Bool  goV1;		
					unsigned char adr:2;
					// byte 1		
					_Bool HS32;
					_Bool HS40;	
			 		_Bool HS41;		
          _Bool HS42;		
          _Bool outHS0;		                           
          _Bool outHS1;		
          _Bool outHS2;		
          _Bool rel1;
					// byte 2 
					_Bool HS10;
					_Bool HS11;          
		   		_Bool HS12;
					_Bool HS20;
					_Bool HS21;
          _Bool HS22;
					_Bool HS30;
			    _Bool HS31;		
		}bit; 
		unsigned char byte[3];  
	} L9952_CR0_TYPE;
      
	
typedef union {	
	struct REG_1_WR_52{                   
	       	// byte 0	
          _Bool T11;		                           
         	_Bool T12;		
          _Bool T13;		                           
	        _Bool T20;		
          _Bool Int_en;		
					_Bool clr;	
	        unsigned char adr:2;
					// byte 1		
					_Bool U0;
					_Bool U1;	
			 		_Bool U2;		
          _Bool U3;		
					unsigned char Looping:3;		                                     
          _Bool T10;
					// byte 2
					_Bool W0;          
		   		_Bool W1;
					_Bool W2;
					_Bool W3;
					_Bool W4;
					_Bool W5;					
					_Bool W6;
			    _Bool W7;		
		}bit; 
		unsigned char byte[3];  
	} L9952_CR1_TYPE;
 
typedef union {	
		struct REG_2_WR_52{                   
	       	// byte 0	               
         	unsigned char IC4:2;		          
	        _Bool LINslope;		
          _Bool LSOVUV;		
          unsigned char _res:2;
	        unsigned char adr:2;				
					// byte 1		
					unsigned char rstLev:2;				 		
          unsigned char IC1:2;		
          unsigned char IC2:2;		
          unsigned char IC3:2;          
					// byte 2
					_Bool OLT_HS1;          
		   		_Bool OLT_HS2;
					_Bool OLT_HS3;
					_Bool OLT_HS4;
					_Bool Vlock;
					_Bool O_HSrec;
					_Bool LinPU;		
					_Bool TXDTOut;
		}bit; 
		unsigned char byte[3];  
	} L9952_CR2_TYPE;
      	



typedef union {
		struct REG_0_RD_52{                   
	       	// byte 0	
           _Bool I3;		
           _Bool INH;		                           
         	 _Bool LIN;		
          _Bool coldStart;		                           
	        unsigned char _res:2;		
	        unsigned char glob_err:2;
					// byte 1		
					_Bool HS4OC;
					_Bool O_HSOC;
			 		_Bool rel1;
					_Bool rel2;
          _Bool V2;
          _Bool I0;
          _Bool I1;
          _Bool I2;
					// byte 2
					_Bool O_HS1OL;          
		   		_Bool O_HS2OL;
					_Bool O_HS3OL;
					_Bool O_HS4OL;
					_Bool O_HSOL;
					_Bool HS1OC;
					_Bool HS2OC;
			    _Bool HS3OC;
		}bit; 
		unsigned char byte[3];  
	} L9952_SR0_TYPE;


typedef union {
		struct REG_1_RD_52{                   
	       		// byte 0	
          _Bool trig;		
          _Bool SHTgnd;		                           
         	_Bool SHTbat;		
          _Bool domTXD;		                           
	        unsigned char _res:2;		
	        unsigned char glob_err:2;
					// byte 1		
					_Bool ST1;
					unsigned char Restarts5V:3;			 		
          unsigned char	WD_reset:4;          
					// byte 2
					_Bool OV;
		   		_Bool UV;
					_Bool TW;
					_Bool TSD1;
					_Bool TSD2;
					_Bool Vcc1Fail;
					_Bool Vcc2Fail;
					_Bool ST0;
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
