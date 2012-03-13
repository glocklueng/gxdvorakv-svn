/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/spi.h,v 1.5.2.3 2009/05/22 06:37:55 Vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.5.2.3 $

DATE 		: 				$Date: 2009/05/22 06:37:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :
	$Log: spi.h,v $
	Revision 1.5.2.3  2009/05/22 06:37:55  Vaclav dvorak
	
	Committed on the Free edition of March Hare Software CVSNT Server.
	Upgrade to CVS Suite for more features and support:
	http://march-hare.com/cvsnt/
	
	Revision 1.5.2.2  2008/04/23 08:03:25  vaclav dvorak
	empty log message ***
	@
	te	
	Revision 1.5.2.1  2007/11/23 10:12:51  vaclav dvorak
	empty log message ***
	@
	te	
	Revision 1.5  2007/10/25 06:56:50  vaclav dvorak
	*** empty log message ***
	
	Revision 1.4  2007/01/15 14:08:36  vaclav dvorak
	*** empty log message ***
	
	Revision 1.3  2006/10/06 13:04:02  vaclav dvorak
	*** empty log message ***
	
	Revision 1.2  2006/09/15 08:39:19  vaclav dvorak
	- backup beffor projjets structure change
	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/



#ifndef SPI1_H
#define SPI1_H

#include "std_types.h"

	
/*---FUNCTIONS---*/

void SPI_Init(void);
//bool SPI_Send(uint8 *dataIn ,uint8 *dataOut);
bool ST_SPI_Send_16(	uint8 	commandByte, 	uint8* 	dataIn, 
							uint8* 	globalStatus, 	uint8* 	dataOut);
bool ST_SPI_Send_8(	uint8 	commandByte, 	uint8* 	dataIn, 
							uint8* 	globalStatus, 	uint8* 	dataOut);						
bool ST_SPI_ReadDevInfo(uint8 address, uint8* globalStatus, uint8*	dataOut);

void SPI_SetSlowMode(_Bool status);
bool SPI_GetMode(void);

/*---CONSTANTS---*/

#define Chipselect_HI (PEDR |= 0x40)
#define Chipselect_LO (PEDR &= ~0x40)

#define DATAOUT_HI	PCDR |= 0x40
#define DATAOUT_LO	PCDR &= ~0x40

#define CLK_HI			PCDR |= 0x80
#define CLK_LO			PCDR &= ~0x80

#define IS_DATIN		PCDR & 0x20



#define Mirror_HI		PADR |= 0x08
#define Mirror_LO		PADR &= ~0x08
#endif


/*** (c) 2002  STMicroelectronics ****************** END OF FILE ***/

