/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companion Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/comm_commands.h,v 1.3.6.5 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.3.6.5 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: comm_commands.h,v $
	Revision 1.3.6.5  2009/05/22 06:37:55  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.3.6.4  2009/02/11 14:55:12  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.3.6.3  2008/09/15 13:49:54  vaclav dvorak
	- comments of files by	
	Revision 1.3.6.2  2007/12/06 14:32:13  vaclav dvorak
	- comments of files by new	
	Revision 1.3.6.1  2007/11/23 10:12:46  vaclav dvorak
	- comments of files by new	
	Revision 1.3  2007/04/05 13:46:49  vaclav dvorak
	- added Get global error status function
	
	Revision 1.2  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.1  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	
******************************************************************************/


#ifndef COMM_H
#define COMM_H

/**
 *
 */
//#define CompanionBoard		0x20
	

/**
 * 	SCI byte 0 commands
 * 	the rest is defined in the L9952.h
 */                            
#define PSD_CMD					0x01    
#define ST7_CMD					0x07 
#define L99PM62DRV_CMD	0x21
#define L99PM62_CMD			0x62
#define L99PM60DRV_CMD	0x22
#define L99PM60_CMD			0x60
#define COMM_TEST				0x7f 

	

	/**
	 * 	ST7   commands for ST7_CMD
	 */
	 
	#define ST7_WDC								0x20
			#define SET_WDC_TIME					0x30
			#define SET_LOW_TIME					0x31
			#define DONT_REFRESH					0x32
			#define SET_LOW_FAIL_NBR			0x33
			#define SET_WDC_ADD_CMD				0x34
			#define SET_LOW_ADD_CMD				0x35
						
	 
   #define ST7_BOARD_STATUS					0x01
			#define ST7_GET_STATUS				0x0C
			#define ST7_GET_DRV_VAL				0x07
	
   #define ST7_BOAR_INV							0x02
			#define ST_DB									0x0A
	
	/*#define ST7_PWM								0x10
			#define SET_PWM_FREQ					0x20   
			#define SET_PWM_DUTY					0x21
			#define SET_PWM_POLARITY			0x22   
			#define SET_PWM_DISABLE				0x23
			#define GET_PWM_FREQ					0x2A
			#define GET_PWM_DUTY					0x2B
					// PWM mask
					#define SET_PWM0				0x01
					#define SET_PWM1				0x02
					#define SET_PWM_ALL			0x03 	*/



	#define ST7_SPI_CONTROL						0x08
			#define SET_SPI_SLOW					0x50

	#define ST7_IO_CONTROL						0x30
			#define DRV_OUT_CTRL					0x01
	
	#define ST7_LIN_CONTROL						0x05
			#define SET_LIN_LEVEL					0x01
			#define LIN_BURST							0x02
			
	#define ST7_CAN_CONTROL						0x15
			#define SET_CAN_LEVEL					0x01
			#define CAN_BURST							0x02

	#define ST7_V1_STB_CONTROL				0x40
			#define 	SET_ON_TIME					0x07
			#define 	SET_BLANKING_TIME		0x08	
		
	
/*******************************************************************************
*******    L99PM62   COMMANDS  (ST-SPI)*****************************************
*******************************************************************************/
		// byte 1
		
		#define SET_L99PM62_CR1 		0x01
		#define SET_L99PM62_CR2 		0x02
		#define SET_L99PM62_CR3 		0x03
		#define SET_L99PM62_CR4 		0x04
		#define SET_L99PM62_CR5 		0x05
		#define SET_L99PM62_CR6 		0x06
		
		#define GET_L99PM62_CR1 		0x41
		#define GET_L99PM62_CR2 		0x42
		#define GET_L99PM62_CR3 		0x43
		#define GET_L99PM62_CR4 		0x44
		#define GET_L99PM62_CR5 		0x45
		#define GET_L99PM62_CR6 		0x46
				
		#define GET_L99PM62_SR1 		0x51
		#define GET_L99PM62_SR2 		0x52
		#define GET_L99PM62_SR3 		0x53
				
		#define CLR_L99PM62_SR1 		0x91
		#define CLR_L99PM62_SR2 		0x92
		#define CLR_L99PM62_SR3 		0x93
		
		#define RET_L99PM62_SR1 		0x11
		#define RET_L99PM62_SR2 		0x12
		#define RET_L99PM62_SR3 		0x13
				
		#define SET_L99PM62_CFR 		0x3F
		#define GET_L99PM62_CFR 		0x7F
		#define CLR_L99PM62_CFR			0xBF	// clr of global status
			// this mask is not used -  call driver function 30
		
		#define GET_L99PM62_ROM 		0xC0
		
/*******************************************************************************
*******    L99PM60   COMMANDS  (ST-SPI)*****************************************
*******************************************************************************/
		// byte 1
		
		#define SET_L99PM60_CR1 		0x01
		#define SET_L99PM60_CR2 		0x02
		
		#define GET_L99PM60_CR1 		0x41
		#define GET_L99PM60_CR2 		0x42
				
		#define GET_L99PM60_SR1 		0x51
		#define GET_L99PM60_SR2 		0x52
		#define GET_L99PM60_SR3 		0x53
		#define GET_L99PM60_SR4 		0x54
				
		#define CLR_L99PM60_SR1 		0x91
		#define CLR_L99PM60_SR2 		0x92
		#define CLR_L99PM60_SR3 		0x93
		#define CLR_L99PM60_SR4 		0x94

		#define SET_L99PM60_CFR 		0x3F
		#define GET_L99PM60_CFR 		0x7F
		#define CLR_L99PM60_CFR			0xBF	// clr of global status
		
		#define GET_L99PM60_ROM 		0xC0
		
#endif

 
 
 
 
 
 
/******** (c) 2005  STMicroelectronics ****************** END OF FILE ********/