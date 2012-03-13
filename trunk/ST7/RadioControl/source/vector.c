/******************** (c) 2006 STMicroelectronics ****************************

PROJECT  : 				Companien Application Board

$Header: c:\cvs_repository/CompanionAppBoard\ST7/source/vector.c,v 1.1.6.1 2008/09/15 13:49:54 vaclav dvorak Exp $
	
VERSION  : 				$Revision: 1.1.6.1 $

DATE 		: 				$Date: 2008/09/15 13:49:54 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: vaclav dvorak $

MODIFICATIONS :
	$Log: vector.c,v $
	Revision 1.1.6.1  2008/09/15 13:49:54  vaclav dvorak
	- comments of files by	
	Revision 1.1  2006/03/23 14:17:54  vaclav dvorak
	no message
	

******************************************************************************/


//void ART_Interrupt (void);
//void LINSCI_1_Interrupt (void);
//void LINSCI_2_Interrupt (void);
void TIMER16_Interrupt (void);
void TIMER8_Interrupt (void);
//void SPI_Interrupt (void);
void CanTx_ISR (void);
void CanRx_ISR (void);
void PORTS_3_Interrupt (void);
void PORTS_2_Interrupt (void);
void PORTS_1_Interrupt (void);
void PORTS_0_Interrupt (void);
void CSS_Interrupt (void);
void NMI_Interrupt (void);
//void TRAP_Interrupt (void);
void _stext(void);

@interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}


void (*const _vectab[])() = {
       NonHandledInterrupt,
       NonHandledInterrupt,
       NonHandledInterrupt,
       TIMER16_Interrupt,
       TIMER8_Interrupt,
       NonHandledInterrupt,
       CanTx_ISR,
       CanRx_ISR,
       PORTS_3_Interrupt,
       PORTS_2_Interrupt,
       PORTS_1_Interrupt,
       PORTS_0_Interrupt,
       CSS_Interrupt,
       NMI_Interrupt,
       NonHandledInterrupt,
       _stext
       };

/*** (c) 2000 STMicroelectronics ****************** END OF FILE ***/
