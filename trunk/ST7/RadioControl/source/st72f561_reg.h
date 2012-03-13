/******************************************************************************
COPYRIGHT 2003 STMicroelectronics 
Source File Name : st72561_reg.h
Group            : MicroController Group
Author           : MCD Application Team
Date First Issued: 25/11/03
********************************Documentation**********************************
Purpose - This file declares all the hardware registers 


********************************Revision History*******************************
_______________________________________________________________________________
Date : 25/11/03                  Release:1.0       	   		        	      
******************************************************************************/

/********************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING
 * CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER
 * FOR THEM TO SAVE TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT
 * BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES
 * WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE
 * AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED
 * HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************/

#ifndef ST72F561_REG_H
#define ST72F561_REG_H

/*****************************************************************************/  
/* Only for COSMIC compiler                                                  */
#ifdef _COSMIC_                                                                
/*---------------------------------------------------------------------------*/ 
/* IO Ports Hardware Registers */  
/* PORT A register */
    @tiny volatile unsigned char PADR    @0x00;	 /* PORT A data Register     */
    @tiny volatile unsigned char PADDR   @0x01;  /* Data direction register  */
    @tiny volatile unsigned char PAOR    @0x02;	      /* Option register     */

/* PORT B register */
    @tiny volatile unsigned char PBDR    @0x03;	 /* PORT B data Register     */
    @tiny volatile unsigned char PBDDR   @0x04;  /* Data direction register  */
    @tiny volatile unsigned char PBOR    @0x05; /* Option Register           */

/* PORT C register */
    @tiny volatile unsigned char PCDR    @0x06;	 /* PORT C data Register     */
    @tiny volatile unsigned char PCDDR   @0x07;  /* Data direction register  */
    @tiny volatile unsigned char PCOR    @0x08;	      /* Option register     */

/* PORT D register */
    @tiny volatile unsigned char PDDR    @0x09;	 /* PORT D data Register     */
    @tiny volatile unsigned char PDDDR   @0x0A;  /* Data direction register  */
    @tiny volatile unsigned char PDOR    @0x0B;	      /* Option register     */

/* PORT E register */
    @tiny volatile unsigned char PEDR    @0x0C;	 /* PORT E data Register     */
    @tiny volatile unsigned char PEDDR   @0x0D;  /* Data direction register  */
    @tiny volatile unsigned char PEOR    @0x0E;	      /* Option register     */

/* PORT F register */
    @tiny volatile unsigned char PFDR    @0x0F;	 /* PORT F data Register     */
    @tiny volatile unsigned char PFDDR   @0x10;  /* Data direction register  */
    @tiny volatile unsigned char PFOR    @0x11;  /* Option Register          */

/*---------------------------------------------------------------------------*/    
/* SPI Hardware Registers */
    @tiny volatile unsigned char SPIDR   @0x21; /* SPI Data I/O Register     */
    @tiny volatile unsigned char SPICR   @0x22; /* SPI Control register      */
    @tiny volatile unsigned char SPICSR  @0x23; /* SPI Control/Status register*/

/*----------------------------------------------------------------------------*/    
/* FLASH Hardware Registers */
    @tiny volatile unsigned char FCSR    @0x24; /* Control/Status Register*/
        
/* ITC Hardware Registers */
    @tiny volatile unsigned char ISPR0 @0x25;/*Interrupt SoftwarePriority Reg0*/
    @tiny volatile unsigned char ISPR1 @0x26;/*Interrupt SoftwarePriority Reg1*/    
    @tiny volatile unsigned char ISPR2 @0x27;/*Interrupt SoftwarePriority Reg2*/
    @tiny volatile unsigned char ISPR3 @0x28;/*Interrupt SoftwarePriority Reg3*/    
    @tiny volatile unsigned char EICR0 @0x29;/*external Interrupt ControlReg 0*/    
    @tiny volatile unsigned char EICR1 @0x2A;/* External InterruptControl Reg1*/        
    
/* AWU Hardware Registers */
    @tiny volatile unsigned char AWUCSR @0x2B;/*AWU Control/Status Register   */
    @tiny volatile unsigned char AWUPR @0x2C;/*Autowake up from halt Prescaler*/    

/* CKCTRL Hardware Registers */
    @tiny volatile unsigned char SICSR @0x2D;
                                        /* System Integrity Cntrl/Status Reg */
    @tiny volatile unsigned char MCCSR @0x2E;
                                        /* Main Clock Cntrl/Status register  */    
    
/* WDG Hardware Registers */
    @tiny volatile unsigned char WDGCR @0x2F; /* Contrl register             */
    @tiny volatile unsigned char WWDGR @0x30; /* window watchdog Register    */

/* PWMART hardware Registers */    
    @tiny volatile unsigned char PWMDCR3 @0x31; /* PWM Duty Cycle Reg 3      */
    @tiny volatile unsigned char PWMDCR2 @0x32; /* PWM Duty Cycle Reg 2      */
    @tiny volatile unsigned char PWMDCR1 @0x33; /* PWM Duty Cycle Reg 1      */    
    @tiny volatile unsigned char PWMDCR0 @0x34; /* PWM Duty Cycle Reg 0      */    
    @tiny volatile unsigned char PWMCR   @0x35; /* PWM Duty Control Reg      */    
    @tiny volatile unsigned char ARTCSR  @0x36; /* ART Control/Status Reg    */
    @tiny volatile unsigned char ARTCAR @0x37; /* ART Counter Access Reg     */
    @tiny volatile unsigned char ARTARR @0x38; /* ART Auto Reload Reg        */
    @tiny volatile unsigned char ARTICCSR @0x39;
                                          /*ART Input Capture Cntrl/Stats reg*/
    @tiny volatile unsigned char ARTICR1 @0x3A; /* Input Capture reg 1       */
    @tiny volatile unsigned char ARTICR2 @0x3B; /* Input Capture reg 2       */        

/* 8 BIT TIMER REGISTERS */    
    @tiny volatile unsigned char T8CR2 @0x3C;    /* Control Register 2       */
    @tiny volatile unsigned char T8CR1 @0x3D;    /* Control Register 1       */
    @tiny volatile unsigned char T8CSR @0x3E;    /* Control/Status Register  */
    @tiny volatile unsigned char T8IC1R @0x3F;   /* Input capture 1 register */
    @tiny volatile unsigned char T8OC1R @0x40;   /* Output Compare 1 Register*/
    @tiny volatile unsigned char T8CTR @0x41;    /*Timer Counter Register    */
    @tiny volatile unsigned char T8ACTR @0x42;   /* Alternate Counter Reg    */
    @tiny volatile unsigned char T8IC2R @0x43;   /*Input Capture Register 2  */
    @tiny volatile unsigned char T8OC2R @0x44;   /* Output Compare 2 Reg     */
    
/* ADC port hardware registers */   
    @tiny volatile unsigned char ADCCSR @0x45;    /* Control/Status Register */
    @tiny volatile unsigned char ADCDRH @0x46;    /* Data Register High      */    
    @tiny volatile unsigned char ADCDRL @0x47;    /* Data Register Low       */

/* SCI Hardware Registers */
    @tiny volatile unsigned char SCI1SR @0x48;           /* Status Register */
    @tiny volatile unsigned char SCI1DR @0x49;              /* Data Register */
    @tiny volatile unsigned char SCI1BRR @0x4A;        /* Baud Rate Register */
    @tiny volatile unsigned char SCI1CR1 @0x4B;        /* Control Register 1 */
    @tiny volatile unsigned char SCI1CR2 @0x4C;        /* Control Register 2 */
    @tiny volatile unsigned char SCI1CR3 @0x4D;        /* Control Register 3 */
    @tiny volatile unsigned char SCI1ERPR @0x4E;
                                        /*Extended Receive Prescaler Register*/
    @tiny volatile unsigned char SCI1ETPR @0x4F; 
                                      /* Extended Transmit Prescaler Register*/
                                      
/* 16 Bit TIMER */
    @tiny volatile unsigned char T16CR2 @0x51;      /* Control Register 2     */
    @tiny volatile unsigned char T16CR1 @0x52;      /* Control Register 1     */
    @tiny volatile unsigned char T16CSR @0x53;      /* Control/Status Register*/
    @tiny volatile unsigned char T16IC1HR @0x54;    /* Input Capture 1 High   */
    @tiny volatile unsigned char T16IC1LR @0x55;    /* Input Capture 1 Low    */
    @tiny volatile unsigned char T16OC1HR @0x56;    /* Output Compare 1 High  */
    @tiny volatile unsigned char T16OC1LR @0x57;    /* Output Compare 1 Low   */
    @tiny volatile unsigned char T16CHR @0x58;      /* Counter High           */
    @tiny volatile unsigned char T16CLR @0x59;      /* Counter Low            */
    @tiny volatile unsigned char T16ACHR @0x5A;     /* Alternate Counter High */
    @tiny volatile unsigned char T16ACLR @0x5B;     /* Alternate Counter Low  */
    @tiny volatile unsigned char T16IC2HR @0x5C;    /* Input Capture 2 High   */
    @tiny volatile unsigned char T16IC2LR @0x5D;    /* Input Capture 2 Low    */
    @tiny volatile unsigned char T16OC2HR @0x5E;    /* Output Compare 2 High  */
    @tiny volatile unsigned char T16OC2LR @0x5F;    /* Output Compare 2 Low   */
   

/* SCI Hardware Registers */
    @tiny volatile unsigned char SCI2SR @0x60;           /* Status Register */
    @tiny volatile unsigned char SCI2DR @0x61;              /* Data Register */
    @tiny volatile unsigned char SCI2BRR @0x62;        /* Baud Rate Register */
    @tiny volatile unsigned char SCI2CR1 @0x63;        /* Control Register 1 */
    @tiny volatile unsigned char SCI2CR2 @0x64;        /* Control Register 2 */
    @tiny volatile unsigned char SCI2CR3 @0x65;        /* Control Register 3 */
    @tiny volatile unsigned char SCI2ERPR @0x66;
                                        /*Extended Receive Prescaler Register*/
    @tiny volatile unsigned char SCI2ETPR @0x67; 
                                      /* Extended Transmit Prescaler Register*/

/* CAN Hardware Registers */   
    @tiny volatile unsigned char CAN_CMCR @0x68; /* CAN Master Control Register*/
    @tiny volatile unsigned char CAN_CMSR @0x69; /* Master status Register     */
    @tiny volatile unsigned char CAN_CTSR @0x6A; /* Transmit Status Register   */
    @tiny volatile unsigned char CAN_CTPR @0x6B; /* Transmit Priority register */
    @tiny volatile unsigned char CAN_CRFR @0x6C; /* Receive FIFO Register      */
    @tiny volatile unsigned char CAN_CIER @0x6D; /* Interrupt Enable Register  */
    @tiny volatile unsigned char CAN_CDGR @0x6E; /* Diagnosis Register         */
    @tiny volatile unsigned char CAN_CPSR @0x6F; /* Page selection register    */

/*  Tx MailBox/Receive FIFO Registers */
    @tiny volatile unsigned char CAN_MCSR  	@0x70;   /* For Tx */
    @tiny volatile unsigned char CAN_MFMI  	@0x70;   /* For Receive FIFO */
    @tiny volatile unsigned char CAN_MDLC  	@0x71;
    @tiny volatile unsigned char CAN_MIDR0 	@0x72;
    @tiny volatile unsigned char CAN_MIDR1 	@0x73;
    @tiny volatile unsigned char CAN_MIDR2	@0x74;
    @tiny volatile unsigned char CAN_MIDR3 	@0x75;
    @tiny volatile unsigned char CAN_MDAR[8]    @0x76;
    @tiny volatile unsigned int  CAN_MDAW[4]	@0x76;
     
	
    @tiny volatile unsigned char CAN_MTSLR 	@0x7e;
    @tiny volatile unsigned char CAN_MTSHR 	@0x7f;
    
    @tiny volatile unsigned int  CAN_MIDR01 	@0x72;
    @tiny volatile unsigned int  CAN_MIDR23 	@0x74;

/*  Configuaration/Diagnosis Registers */    
    
    @tiny volatile unsigned char CAN_CESR  	@0x70;
    @tiny volatile unsigned char CAN_CEIER 	@0x71;
    @tiny volatile unsigned char CAN_TECR  	@0x72;
    @tiny volatile unsigned char CAN_RECR  	@0x73;
    @tiny volatile unsigned char CAN_CBTR0 	@0x74;
    @tiny volatile unsigned char CAN_CBTR1 	@0x75;
    @tiny volatile unsigned char CAN_unknown1 	@0x76;
    @tiny volatile unsigned char CAN_unknown2 	@0x77;
    @tiny volatile unsigned char CAN_CFMR0 	@0x78;
    @tiny volatile unsigned char CAN_CFMR1 	@0x79;
    @tiny volatile unsigned char CAN_CFCR0 	@0x7a;
    @tiny volatile unsigned char CAN_CFCR1 	@0x7b;
    @tiny volatile unsigned char CAN_CFCR2 	@0x7c;
    @tiny volatile unsigned char CAN_unknown3 	@0x7d;
    @tiny volatile unsigned char CAN_unknown4 	@0x7e;
    @tiny volatile unsigned char CAN_unknown5 	@0x7f;

/*  Acceptance Filter Registers*/

    @tiny volatile unsigned char CAN_CFxR0 @0x70;
    @tiny volatile unsigned char CAN_CFxR1 @0x71;
    @tiny volatile unsigned char CAN_CFxR2 @0x72;
    @tiny volatile unsigned char CAN_CFxR3 @0x73;
    @tiny volatile unsigned char CAN_CFxR4 @0x74;
    @tiny volatile unsigned char CAN_CFxR5 @0x75;
    @tiny volatile unsigned char CAN_CFxR6 @0x76;
    @tiny volatile unsigned char CAN_CFxR7 @0x77;

    @tiny volatile unsigned char CAN_CFyR0 @0x78;
    @tiny volatile unsigned char CAN_CFyR1 @0x79;
    @tiny volatile unsigned char CAN_CFyR2 @0x7a;
    @tiny volatile unsigned char CAN_CFyR3 @0x7b;
    @tiny volatile unsigned char CAN_CFyR4 @0x7c;
    @tiny volatile unsigned char CAN_CFyR5 @0x7d;
    @tiny volatile unsigned char CAN_CFyR6 @0x7e;
    @tiny volatile unsigned char CAN_CFyR7 @0x7f;

    @tiny volatile unsigned int CAN_CFxR01 @0x70;
    @tiny volatile unsigned int CAN_CFxR23 @0x72;
    @tiny volatile unsigned int CAN_CFxR45 @0x74;
    @tiny volatile unsigned int CAN_CFxR67 @0x76;

    @tiny volatile unsigned int CAN_CFyR01 @0x78;
    @tiny volatile unsigned int CAN_CFyR23 @0x7a;
    @tiny volatile unsigned int CAN_CFyR45 @0x7c;
    @tiny volatile unsigned int CAN_CFyR67 @0x7e;

/*****************************************************************************/                                           
 
	#define bit0		0x01
	#define bit1		0x02
	#define bit2		0x04
	#define bit3		0x08
	#define bit4		0x10
	#define bit5		0x20
	#define bit6		0x40
	#define bit7		0x80
 
 
 
 
 /********** Lin/SCI **********************/
 
	#define TDRE 	0x80
	#define RDRF 	0x20
	// SCRCR2	register
	#define TCIE	0x40
	
 /*********** SPI **********************/
	#define SPIF 	0x80
 /*********** TIMER8/16 ***************/
 // TxCRS
	#define	ICF1	0x80
	#define	OCF1	0x40
	#define	TOF	0x20
	#define	ICF2	0x10
	#define	OCF2	0x08
	#define	TIMD	0x04
	
	
 
/* ADC Control/Status Register bit definition */

#define EOC         0x80        	/* End of Conversion */
#define SPEED		  0x40			/* ADC clock selection */
#define ADON        0x20        	/* A/D converter on */
/* LINSCI status register bit definition  */

#define TDRE        0x80        /* Tansmit data register empty */
#define TC          0x40        /* Transmission complete       */
#define RDRF        0x20        /* Received data ready flag    */
#define IDLE        0x10        /* Idle line detect            */
#define _0R         0x08        /* Overrun error               */
#define NF          0x04        /* Noise flag                  */
#define FE          0x02        /* Framing error               */
#define PE			  0x01		/* Parity Error				   */
                                                                                                                                                                                                                                                                                                               
/* LINSCI control register 1 bit definition */
#define R8          0x80        /* Receive data bit8           */
#define T8          0x40        /* Transmit data bit8          */
#define SCID		  0x20		/* Disable for Low Power Consumption */
#define M           0x10        /* Word lenght                 */
#define WAKE        0x08        /* Wake-up method              */
#define PCE			  0x04		/* Parity control enable       */
#define PS			  0x02		/* Parity Selection			   */
#define PIE			  0x01		/* Parity Interrupt enable     */

/* LINSCI control register 2 bit definition */
#define TIE         0x80        /* Transmitter interrupt enable */
#define TCIE        0x40        /* Transmission complete interrupt enable */
#define RIE         0x20        /* Receiver interupt enable    */ 
#define ILIE        0x10        /* Idle line interrupt enable  */
#define TE          0x08        /* Transmitter enable          */
#define RE          0x04        /* Receiver enable             */            
#define RWU         0x02        /* Receiver wake_up            */
#define SBK         0x01        /* Send break                  */

/* LINSCI control register 3 bit definition */
#define NP          0x80        /* No Preamble					*/
#define LINE        0x40        /* LIN Mode enable				*/
#define LSLV        0x20        /* LIN Mode enable				*/ 
#define LASE        0x10        /* LIN Auto Synch Enable		*/
#define LHDM        0x08        /* LIN Header Detection Methode	*/
#define LHIE        0x04        /* LIN Header Interrupt Enable	*/            
#define LHDF        0x02        /* LIN Header Detection Flag	*/
#define LSF         0x01        /* LIN Synch Field State		*/
 
/* additional LINSCI 2 control register 3 bit definition */
#define CLKEN       0x08        /* LIN Clock enable				*/
#define CPOL        0x04        /* LIN Clock polarity			*/            
#define CPHA        0x02        /* LIN clock Phase				*/
#define LBCL        0x01        /* LIN last bit clock pulse		*/


/* LINSCI prescaler fraction register */
#define LDUM		  0x80		/* LIN Divider Update Methode	*/ 
                      
#endif /*_COSMIC_ */
#endif /* st72561 */

