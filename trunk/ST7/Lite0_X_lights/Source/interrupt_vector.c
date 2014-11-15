/*	BASIC INTERRUPT VECTORS TABLE FOR ST7 devices
 *	Copyright (c) 2002-2005 STMicroelectronics
 */


extern void _stext();		/* startup routine */  
extern volatile @interrupt void AT_OF_Interrupt(void);
extern volatile @interrupt void AT_CMP_Interrupt(void);
extern volatile @interrupt void AWU_Interrupt(void);
extern volatile @interrupt void LT_OF_Interrupt(void);

@interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}


/* Interrupt vector table, to be linked at the address
   0xFFE0 (in ROM) */ 
void (* const _vectab[])() = {
	NonHandledInterrupt,  		/* 0xFFE0 */
	NonHandledInterrupt,			/* 0xFFE2 */
	LT_OF_Interrupt,			/* 0xFFE4 */
	NonHandledInterrupt,			/* 0xFFE6 */
	AT_OF_Interrupt,			/* 0xFFE8 */
	AT_CMP_Interrupt,					/* 0xFFEA */
	NonHandledInterrupt,			/* 0xFFEC */
	NonHandledInterrupt,			/* 0xFFEE */
	NonHandledInterrupt,			/* 0xFFF0 */
	NonHandledInterrupt,			/* 0xFFF2 */
	NonHandledInterrupt,					/* 0xFFF4 */
	NonHandledInterrupt,			/* 0xFFF6 */
	NonHandledInterrupt,			/* 0xFFF8 */
	AWU_Interrupt,			/* 0xFFFA */
	NonHandledInterrupt,			/* Trap vector */
	_stext,			/* Reset Vector */
};