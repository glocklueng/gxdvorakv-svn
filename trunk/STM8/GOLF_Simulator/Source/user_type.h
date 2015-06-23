/******************** (c) 2009 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.1 $
DATE 		: 				$Date: 2009/05/15 09:27:06 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
$log:$
******************************************************************************/



#ifndef USERT_H
#define USERT_H

//#include "stm8_type.h"
/**
*		types for CLK source selection
*/
typedef enum {CLK_HSI = 0xE1, CLK_LSI = 0xD2, CLK_HSE = 0xB4} CLK_TYPE;



typedef union {
			struct EES {
				unsigned char perm_supp:1;
				unsigned char dummy:7;
			}bit;
			unsigned char byte;
} EE_STORAGE_TYPE;


/**
*		Board Status TYPE
*/
typedef union {
		struct BSTB {
			unsigned char 	_dummy: 8;
			
			unsigned char 	CP_switch: 1;
			unsigned char  	FSO_switch: 1;
			unsigned char		PWM_out_Status:2;
			unsigned char		dummy6:4;			
		}bit;
		unsigned char byte[2];
} BOARD_STATUS_TYPE;


/**
*		SPI operation mode type
*/
typedef enum {
			SPI_RUN,
			SPI_STOP
			} SPI_MODE_TYPE;	

#endif


/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/

