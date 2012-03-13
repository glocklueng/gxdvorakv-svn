/*  BASIC INTERRUPT VECTORS TABLE FOR STM8 devices with FLASH LOADER
 *  Copyright (c) 2008 STMicroelectronics
 */

typedef void @far (*interrupt_handler_t)(void);

struct interrupt_vector {
	unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};

extern void _stext();       /* startup routine */

@far extern @interrupt void USART_RX_Interrupt (void);
@far extern @interrupt void USART_TX_Interrupt (void);
@far extern @interrupt void TIM4_UPD_OVF_Interrupt (void);
@far extern @interrupt void GPIOD_EI3_Interrupt (void);
@far extern @interrupt void CAN_TX_ISR (void);
@far extern @interrupt void CAN_RX_ISR (void);
@far extern @interrupt void TIM1_UPD_OVF_Interrupt (void);

@far @interrupt void NonHandledInterrupt (void)
{
    /* in order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction
    */
    return;
}

extern void @near _stext();                 /* startup routine */

struct interrupt_vector const _vectab[] = {
	{0x82, (interrupt_handler_t)_stext}, /* reset */
	{0x82, NonHandledInterrupt}, /* trap  */
	{0x82, NonHandledInterrupt}, /* irq0  */
	{0x82, NonHandledInterrupt}, /* irq1  */
	{0x82, NonHandledInterrupt}, /* irq2  */
	{0x82, NonHandledInterrupt}, /* irq3  */
	{0x82, NonHandledInterrupt}, /* irq4  */
	{0x82, NonHandledInterrupt}, /* irq5  */
	{0x82, NonHandledInterrupt}, /* irq6  */
	{0x82, NonHandledInterrupt}, /* irq7  */
	{0x82, NonHandledInterrupt}, /* irq8  */
	{0x82, NonHandledInterrupt}, /* irq9  */
	{0x82, NonHandledInterrupt}, /* irq10 */
	{0x82, NonHandledInterrupt}, /* irq11 */
	{0x82, NonHandledInterrupt}, /* irq12 */
	{0x82, NonHandledInterrupt}, /* irq13 */
	{0x82, NonHandledInterrupt}, /* irq14 */
	{0x82, NonHandledInterrupt}, /* irq15 */
	{0x82, NonHandledInterrupt}, /* irq16 */
	{0x82, NonHandledInterrupt }, /* irq17 */
	{0x82, NonHandledInterrupt }, /* irq18 */
	{0x82, NonHandledInterrupt}, /* irq19 */
	{0x82, NonHandledInterrupt}, /* irq20 */
	{0x82, NonHandledInterrupt}, /* irq21 */
	{0x82, NonHandledInterrupt}, /* irq22 */
	{0x82, TIM4_UPD_OVF_Interrupt}, /* irq23 */
	{0x82, NonHandledInterrupt}, /* irq24 */
	{0x82, NonHandledInterrupt}, /* irq25 */
	{0x82, NonHandledInterrupt}, /* irq26 */
	{0x82, NonHandledInterrupt}, /* irq27 */
	{0x82, NonHandledInterrupt}, /* irq28 */
	{0x82, NonHandledInterrupt}, /* irq29 */
};

