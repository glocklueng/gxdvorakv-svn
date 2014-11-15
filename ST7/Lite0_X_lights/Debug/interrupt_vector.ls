   1                     ; C Compiler for ST7 (COSMIC Software)
   2                     ; Generator V4.5b - 07 Sep 2004
  33                     ; 12 @interrupt void NonHandledInterrupt (void)
  33                     ; 13 {
  34                     	switch	.text
  35  0000               _NonHandledInterrupt:
  39                     ; 17 	return;
  42  0000 80            	iret
  44                     .const:	section	.text
  45  0000               __vectab:
  47  0000 0000          	dc.w	_NonHandledInterrupt
  49  0002 0000          	dc.w	_NonHandledInterrupt
  51  0004 0000          	dc.w	_LT_OF_Interrupt
  53  0006 0000          	dc.w	_NonHandledInterrupt
  55  0008 0000          	dc.w	_AT_OF_Interrupt
  57  000a 0000          	dc.w	_AT_CMP_Interrupt
  59  000c 0000          	dc.w	_NonHandledInterrupt
  61  000e 0000          	dc.w	_NonHandledInterrupt
  63  0010 0000          	dc.w	_NonHandledInterrupt
  65  0012 0000          	dc.w	_NonHandledInterrupt
  67  0014 0000          	dc.w	_NonHandledInterrupt
  69  0016 0000          	dc.w	_NonHandledInterrupt
  71  0018 0000          	dc.w	_NonHandledInterrupt
  73  001a 0000          	dc.w	_AWU_Interrupt
  75  001c 0000          	dc.w	_NonHandledInterrupt
  77  001e 0000          	dc.w	__stext
 102                     	xdef	__vectab
 103                     	xdef	_NonHandledInterrupt
 104                     	xref	_LT_OF_Interrupt
 105                     	xref	_AWU_Interrupt
 106                     	xref	_AT_CMP_Interrupt
 107                     	xref	_AT_OF_Interrupt
 108                     	xref	__stext
 127                     	end
