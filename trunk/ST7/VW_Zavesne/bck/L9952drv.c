/******************************************************************************/
/*! Project Name:   L9952 driver
    @file           L9952drv.c
    @version        $Revision: 1.6 $
    @date           $Date: 2007/10/25 06:56:50 $
    @author         David Trojek
    @author         Vaclav Dvorak
    @brief          SW driver for ST L9952 device.

    Company:        STMicroelectronics
                    Pobrezni 3
                    186 00 Praha 8, Czech Republic

    Processor:      any (ST7)
    
    Compiler:       any (Cosmic)

    Copyright (c) 2005 STMicroelectronics.

    THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
    EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTY
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK
    AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE
    PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
    REPAIR OR CORRECTION.

*******************************************************************************/

/****************************** Revision History *******************************

    Date        Name            Description
    18.04.2007  David Trojek    Added function L9952drv_SetIntMode for L9952GXP.
    05.02.2007  David Trojek    Original Issue
					 Vaclav Dvorak	  Chnanged ICMP philosophy

*******************************************************************************/

#define L9952DRV_C_MAJOR_VERSION  1
#define L9952DRV_C_MINOR_VERSION  1
#define L9952DRV_C_PATCH_VERSION  0
#define L9952DRV_C_BUILD_REVISION "$Revision: 1.6 $"


#include "L9952drv.h"
#include "L9952drv_AL.h"

#if L9952DRV_C_MAJOR_VERSION != L9952DRV_H_MAJOR_VERSION
    #error "Wrong version of L9952drv.H"
#endif

#if L9952DRV_C_MAJOR_VERSION != L9952DRV_AL_H_MAJOR_VERSION
    #error "Wrong version of L9952drv_AL.h"
#endif

/*******************************************************************************
******************* macros for generating debugging messages *******************
*******************************************************************************/


/*******************************************************************************
************************* Internal Constants and Variables *********************
*******************************************************************************/


/*******************************************************************************
********************************** Variables **********************************
*******************************************************************************/

static uint8    CtrlReg0[3], /*!< Internal copy of L9952 control registers 0.
                                Bit order: x[0]:23..16, x[1]:15..8, x[2]:7..0 */
                CtrlReg1[3], /*!< Internal copy of L9952 control registers 1.
                                Bit order: x[0]:23..16, x[1]:15..8, x[2]:7..0 */
                CtrlReg2[3], /*!< Internal copy of L9952 control registers 2.
                                Bit order: x[0]:23..16, x[1]:15..8, x[2]:7..0 */
                StatReg0[3], /*!< Internal copy of L9952 status registers 0.
                                Bit order: x[0]:23..16, x[1]:15..8, x[2]:7..0 */
                StatReg1[3]; /*!< Internal copy of L9952 status registers 1.
                                Bit order: x[0]:23..16, x[1]:15..8, x[2]:7..0 */

#ifdef  L9952DRV_DEV_ERROR_DETECT
static uint8    InitFlag = 0U;  /*!< Flag to notice if L9952drv_Init() was 
                                already called. 0..not called.*/
#endif

/*******************************************************************************
********************************** Prototypes **********************************
*******************************************************************************/


void L9952drv_SetVReg1CurrentMonitorOn (void);


/*******************************************************************************
********************************** Functions ***********************************
*******************************************************************************/


#ifdef  L9952DRV_DEV_ERROR_DETECT
/******************************************************************************/
/*! @fn         bool L9952drv_ReportError (uint8 ServiceId, uint8 ErrorId)
    @param[in]  ServiceId defines ID of failing function (service)
    @param[in]  ErrorId defines ID of Error
    @return         TRUE  .. to continue in interrupted function anyway
                            like in run mode without L9952DRV_DEV_ERROR_DETECT, 
                    FALSE .. to stop execution of interrupted function by return
                             and to avoid any communication with L9952 device
    @brief 
Service for reporting of errors especially during development phase.
This function is originally implemented as dummy function. It allows the user to
implement his required functionality for instance error logging, settings of 
some user global error variables for detailed error localization etc.
*/
/******************************************************************************/

bool L9952drv_ReportError (uint8 ServiceId, uint8 ErrorId) {
    ServiceId = ServiceId;  /* to avoid error message parameter not used */
    ErrorId   = ErrorId;    /* to avoid error message parameter not used */

#ifdef L9952DRV_DEV_ERROR_DETECT_EXEC_CONTINUE
    return TRUE;    /*  to continue in interrupted function anyway */
                    /*    like in run mode without L9952DRV_DEV_ERROR_DETECT */ 
#else
    return FALSE;   /*  to stop execution of interrupted function by return; */
                    /*    and to avoid any communication with L9952 device */
#endif
}

#endif
/******************************************************************************/
/*! @fn         void L9952drv_Init (void)
    @brief 
This module shall initialize the whole L9952 driver (internal data structure
etc). It does not care about L9952 SPI adaptation layer nor SPI interface nor 
L9952 device itself. The SPI needs to be initialized earlier.
Caveats: L9952drv can control just one L9952 device.
This service should not be called during a running operation.
*/
/******************************************************************************/

void L9952drv_Init (void) {
    uint8 i;

#ifdef  L9952DRV_DEV_ERROR_DETECT
    InitFlag = 1U;  /* Flag to notice that L9952drv_Init()was already called*/
#endif
    for (i = 0U; i < 3U; i++){
        CtrlReg0[i] = 0U;
        CtrlReg1[i] = 0U;
        CtrlReg2[i] = 0U;
        StatReg0[i] = 0U;
        StatReg1[i] = 0U;

    }
    CtrlReg1[0] = (uint8)(0x01U << 6);
    CtrlReg2[0] = (uint8)(0x02U << 6);
}


/******************************************************************************/
/*! @fn         void L9952drv_SetStandbyMode(L9952drv_StandbyModeType mode)
    @param[in]  mode    defines type of stand by mode to be set
    @brief
This function sets selected Stand by mode of the L9952 device.
Affected register: CR0.20..21, CR2.20 (by L9952drv_SetVReg1CurrentMonitorOn)
Note: Function L9952drv_SetVReg1CurrentMonitorOn() is called before Control 
Register 0 is modified to go to Stand by mode. Reason is security. Function 
updates SW driver internal copy of Control Register 0 and the register is 
immediately sent to L9952 via SPI. Function refreshes SW driver internal copy
of Status0 register from L9952 via SPI.
Caveats: It is necessary to decrease power consumption from L9952 V1 voltage
regulator after set Stand by mode V1. Most often it means to set immediately 
Halt mode of the MCU. It is necessary to take care also about Watchdog 
triggering. The best time for the function calling is just after the calling of
L9952drv_WdgTrigger(); function in its regular watch dog time window. Function 
waits until both Control registers are transferred completely to L9952 via SPI.
*/
/******************************************************************************/

void L9952drv_SetStandbyMode (L9952drv_StandbyModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetStandbyMode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    switch (mode) {
    case L9952DRV_STANDBYMODE_V1:
        CtrlReg0[0] |= 0x20U;
      //  L9952drv_SetVReg1CurrentMonitorOn();
        L9952DRV_AL_SPI_WR(CtrlReg0, StatReg0);
        CtrlReg0[0] &= (uint8)~0x20U;
        break;
    case L9952DRV_STANDBYMODE_VBAT:
        CtrlReg0[0] |= 0x10U;
        L9952DRV_AL_SPI_WR(CtrlReg0, StatReg0); /* should cause power off */
        CtrlReg0[0] &= (uint8)~0x10U;           /* line should not be reached */
        break;
    default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
        L9952drv_ReportError (SID_L9952drv_SetStandbyMode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
        return;
    }
}

/******************************************************************************/
/*! @fn         void L9952drv_SetOutMode (uint8 mask, L9952drv_OutModeType mode)
    @param[in]  mask    sets by mask which output will be changed.
                    Range: 0x00..0xF1
                    Bit 0:  1 = Mask is active for OUTHS, 
                            0 = Mask is not active for OUTHS.
                    Bit 4:  1 = Mask is active for OUT1, 
                            0 = Mask is not active for OUT1.
                    Bit 5:  1 = Mask is active for OUT2, 
                            0 = Mask is not active for OUT2.
                    Bit 6:  1 = Mask is active for OUT3, 
                            0 = Mask is not active for OUT3.
                    Bit 7:  1 = Mask is active for OUT4, 
                            0 = Mask is not active for OUT4.
                    Following constants are defined in L9952drv.h file:
                    L9952DRV_MASK_OUT1, L9952DRV_MASK_OUT2, L9952DRV_MASK_OUT3,
                    L9952DRV_MASK_OUT4, L9952DRV_MASK_OUTHS.
                    Example: OUT_MODE_MASK_OUT1 | OUT_MODE_MASK_OUT2 …  mask is
                    active for OUT1 and OUT2.
    @param[in]  mode    defines type of stand by mode to be set
    @brief      
Function controls HS outputs of L9952. Affected register: CR0.0..14
Note: Function updates SW driver internal copy of Control Register 0 and the 
register is immediately sent to L9952 via SPI.
Caveats: Function refreshes SW driver internal copy of Status0 register from 
L9952 via SPI. Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_SetOutMode (uint8 mask, L9952drv_OutModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    sint8 tmp;

    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetOutMode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
    if (mask & (uint8)~0xF1U) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetOutMode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE)) {
            return;
        }
    }
    tmp = (sint8)mode;
    if ((tmp < (sint8)L9952DRV_OUT_MODE_OFF) || (tmp > (sint8)L9952DRV_OUT_MODE_PWM2)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetOutMode, L9952DRV_EID_PARAMETER2_OUT_OF_RANGE)) {
            return;
        }
    }
#endif
    if (mask & L9952DRV_MASK_OUT1) {
        CtrlReg0[2] &= (uint8)~0x07U;
        CtrlReg0[2] |= (uint8)mode & 0x07U;
    }
    if (mask & L9952DRV_MASK_OUT2) {
        CtrlReg0[2] &= (uint8)~0x38U;
        CtrlReg0[2] |= (uint8)((uint8)mode<<3) & 0x38U;
    }
    if (mask & L9952DRV_MASK_OUT3) {
        CtrlReg0[2] &= (uint8)~0xC0U;
        CtrlReg0[1] &= (uint8)~0x01U;
        CtrlReg0[2] |= (uint8)((uint8)mode<<6) & 0xC0U;
        CtrlReg0[1] |= (uint8)((uint8)mode>>2) & 0x01U;
    }
    if (mask & L9952DRV_MASK_OUT4) {
        CtrlReg0[1] &= (uint8)~0x0EU;
        CtrlReg0[1] |= (uint8)((uint8)mode<<1) & 0x0EU;
    }
    if (mask & L9952DRV_MASK_OUTHS) {
        CtrlReg0[1] &= (uint8)~0x70U;
        CtrlReg0[1] |= (uint8)((uint8)mode<<4) & 0x70U;
    }
    L9952DRV_AL_SPI_WR(CtrlReg0, StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetOutHSAutorecovery (L9952drv_OutHSAutorecoveryType mode)
    @param[in]      mode    sets autorecovery functionality for OUT HS output 
    @brief      
Function enables/disables autorecovery functionality for OUT HS output of L9952.
Affected register: CR2.5
Note: Function updates SW driver internal copy of Control Register 2 and the 
register is immediately sent to L9952 via SPI.
Caveats: Function refreshes SW driver internal copy of Status0 register from 
L9952 via SPI. Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_SetOutHSAutorecovery (L9952drv_OutHSAutorecoveryType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetOutHSAutorecovery, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    switch (mode) {
        case L9952DRV_OUTHS_AUTORECOVERY_OFF:    
            CtrlReg2[2] &= (uint8)~0x20U;
            break;
        case L9952DRV_OUTHS_AUTORECOVERY_ON:
            CtrlReg2[2] |= 0x20U;
            break;
        default:
    #ifdef  L9952DRV_DEV_ERROR_DETECT
            L9952drv_ReportError (SID_L9952drv_SetOutHSAutorecovery, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
    #endif
            return;                 /* parameter value out of range */
    }
    L9952DRV_AL_SPI_WR(CtrlReg2, StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetRelayOutput (L9952drv_RelayOutputType value)
    @param[in]      value describes which relay will be set to which state
                    (or not changed)
    @brief                              
Function controls LS relay outputs of L9952. Affected register: CR0.15..16
Note: Function updates SW driver internal copy of Control Register 0 and the 
register is immediately sent to L9952 via SPI.
Caveats: Function refreshes SW driver internal copy of Status0 register from 
L9952 via SPI. Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/
/*! @def REL1_ON
For internal purpose of L9952drv_SetRelayOutput() only */
/*! @def REL1_OFF
For internal purpose of L9952drv_SetRelayOutput() only */
/*! @def REL2_ON
For internal purpose of L9952drv_SetRelayOutput() only */
/*! @def REL2_OFF
For internal purpose of L9952drv_SetRelayOutput() only */

#define REL1_ON     (CtrlReg0[1] |= 0x80U)
#define REL1_OFF    (CtrlReg0[1] &= (uint8)~0x80U)
#define REL2_ON     (CtrlReg0[0] |= 0x01U)
#define REL2_OFF    (CtrlReg0[0] &= (uint8)~0x01U)

void L9952drv_SetRelayOutput (L9952drv_RelayOutputType value) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetRelayOutput, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    switch (value) {
        case RELAYOUTPUT_OFF_OFF:   /* Switch both relays off. */
            REL1_OFF;
            REL2_OFF;
            break;
        case RELAYOUTPUT_ON_OFF:    /* Switch relay REL1 on and REL2 off.*/
            REL1_ON;
            REL2_OFF;
            break;
        case RELAYOUTPUT_OFF_ON:    /* Switch relay REL1 off and REL2 on.*/
            REL1_OFF;
            REL2_ON;
            break;
        case RELAYOUTPUT_ON_ON:     /* Switch both relays on.*/
            REL1_ON;
            REL2_ON;
            break;
        case RELAYOUTPUT_OFF_X:     /* Switch relay REL1 off and refresh 
                                        previous state of REL2 (don’t change).*/
            REL1_OFF;
            break;
        case RELAYOUTPUT_ON_X:      /* Switch relay REL1 on and refresh 
                                        previous stateof REL2 (don’t change).*/
            REL1_ON;
            break;
        case RELAYOUTPUT_X_OFF:     /* Switch relay REL2 off and refresh 
                                        previous state of REL1 (don’t change).*/
            REL2_OFF;
            break;
        case RELAYOUTPUT_X_ON:      /* Switch relay REL2 on and refresh
                                        previous state of REL1 (don’t change).*/
            REL2_ON;
            break;
        default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
            L9952drv_ReportError (SID_L9952drv_SetRelayOutput, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
            return;                 /* parameter value out of range */
    }
    L9952DRV_AL_SPI_WR(CtrlReg0, StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetVoltageReg2Mode (L9952drv_VoltageReg2ModeType mode)
    @param[in]      mode defines mode of Voltage regulator 2 to be set
    @brief                              
Function controls Voltage regulator 2 mode of L9952.Affected register:CR0.17..18
Note: Function updates SW driver internal copy of Control Register 0 and the
register is immediately sent to L9952 via SPI. Function refreshes SW driver 
internal copy of Status0 register from L9952 via SPI. 
Caveats: Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_SetVoltageReg2Mode (L9952drv_VoltageReg2ModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    sint8 tmp;

    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetVoltageReg2Mode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
    tmp = (sint8)mode;
    if ((tmp < (sint8)L9952DRV_VOLTAGE_REG2_OFF) || (tmp > (sint8)L9952DRV_VOLTAGE_REG2_ON)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetVoltageReg2Mode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE)) {
            return;
        }
    }
#endif

    CtrlReg0[0] &= (uint8)~0x06U;
    CtrlReg0[0] |= (uint8)((uint8)mode << 1U) & 0x06U;
    L9952DRV_AL_SPI_WR(CtrlReg0, StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetTimer1 (L9952drv_Timer1PeriodType period, L9952drv_Timer1ONTimeType ontime)
    @param[in]      period defines period of L9952 Timer 1
    @param[in]      ontime defines the part of period where the L9952 Timer 1 
                    output is set to 1.
    @brief                              
Function controls Timer1 of L9952. Affected register: CR1.15..18
Note: Function updates SW driver internal copy of Control Register 1 and the 
register is immediately sent to L9952 via SPI. Function refreshes SW driver 
internal copy of Status1 register from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952 
via SPI.
*/
/******************************************************************************/

void L9952drv_SetTimer1 (L9952drv_Timer1PeriodType period, L9952drv_Timer1ONTimeType ontime) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    sint8 tmp;

    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetTimer1, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
    tmp = (sint8)period;
    if ((tmp < (sint8)L9952DRV_TIMER1PERIOD_500) || (tmp > (sint8)L9952DRV_TIMER1PERIOD_4000)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetTimer1, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE)) {
            return;
        }
    }
    if ((ontime != L9952DRV_TIMER1ONTIME_10) && (ontime != L9952DRV_TIMER1ONTIME_20)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetTimer1, L9952DRV_EID_PARAMETER2_OUT_OF_RANGE)) {
            return;
        }
    }
#endif

    CtrlReg1[0] &= (uint8)~0x07U;
    CtrlReg1[0] |= (uint8)((uint8)ontime << 2) & (uint8)(0x01U << 2);
    CtrlReg1[0] |= (uint8)((uint8)period >> 1) & 0x03U;
    if ((uint8)period & 0x01U) {
        CtrlReg1[1] |= 0x80U;
    }else {
        CtrlReg1[1] &= (uint8)~0x80U;
    }
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetTimer2 (L9952drv_Timer2ONTimeType ontime)
    @param[in]      ontime defines the part of period where the L9952 Timer 2
                    output is set to 1.
    @brief                              
Function controls timer2 of L9952. Affected register: CR1.19
Note: Function updates SW driver internal copy of Control Register 1 and the 
register is immediately sent to L9952 via SPI. Function refreshes SW driver 
internal copy of Status1 register from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952 
via SPI.
*/
/******************************************************************************/

void L9952drv_SetTimer2 (L9952drv_Timer2ONTimeType ontime) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetTimer2, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    switch (ontime) {
        case L9952DRV_TIMER2ONTIME_01:
            CtrlReg1[0] &= (uint8)~0x08U;
            break;
        case L9952DRV_TIMER2ONTIME_1:
            CtrlReg1[0] |= 0x08U;
            break;
        default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
            L9952drv_ReportError (SID_L9952drv_SetTimer2, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
            return;
    }
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetDigOutput (L9952drv_DigOutputModeType mode)
    @param[in]      mode describes modes for digital outputs Dig_Out3 and 
                    Dig_Out4 of L9952.
    @brief                              
Function controls digital outputs 3 and 4 of L9952.Affected register: CR1.12..14
Note: Function updates SW driver internal copy of Control Register 1 and the 
register is immediately sent to L9952 via SPI. Function refreshes SW driver 
internal copy of Status1 register from L9952 via SPI.
Caveats: Modes of both digital outputs are coupled because of L9952 internal 
construction. Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_SetDigOutput (L9952drv_DigOutputModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    sint8 tmp;

    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetDigOutput, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
    tmp = (sint8)mode;
    if ((tmp < (sint8)L9952DRV_DO_WU3_WU4) || (tmp > (sint8)L9952DRV_DO_HIZ_OLHS2)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetDigOutput, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE)) {
            return;
        }
    }
#endif

    CtrlReg1[1] &= (uint8)~0x70U;
    CtrlReg1[1] |= (uint8)((uint8)mode << 4) & 0x70U;
    L9952DRV_AL_SPI_WR(CtrlReg1 ,StatReg1);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetWUInputMode (uint8 mask, L9952drv_WUInputModeType mode)
    @param[in]      mask sets WU input mode to be changed.
                    Range: 0x00..0x0F
                        Bit 0:  1 = Mask is active for WU1, 
                                0 = Mask is not active for WU1.
                        Bit 1:  1 = Mask is active for WU2, 
                                0 = Mask is not active for WU2.
                        Bit 2:  1 = Mask is active for WU3, 
                                0 = Mask is not active for WU3.
                        Bit 3:  1 = Mask is active for WU4, 
                                0 = Mask is not active for WU4.
                    Following constants are defined in L9952drv.h file:
                    L9952DRV_MASK_WU1, L9952DRV_MASK_WU2, L9952DRV_MASK_WU3,
                    L9952DRV_MASK_WU4.
                    Example: L9952DRV_MASK_WU2 | L9952DRV_MASK_WU3 
                    … mask is active for WU2 and WU3.
    @param[in]      mode describes mode (pull up/pull down) for dig. WU Inputs.
    @brief
Function sets mode (pull up / pull down) for digital wake up inputs WU1, WU2,
WU3 and WU4 of L9952. Affected register: CR1.8..11. Note: Function updates SW
driver internal copy of Control Register 1 and the register is immediately sent
to L9952 via SPI. Function refreshes SW driver internal copy of Status1 register
from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952 
via SPI.
*/
/******************************************************************************/

void L9952drv_SetWUInputMode (uint8 mask, L9952drv_WUInputModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetWUInputMode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
    if (mask & (uint8)~0x0FU) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetWUInputMode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE)) {
            return;
        }
    }
    if ((mode != L9952DRV_WU_INPUT_MODE_PULL_UP) && (mode != L9952DRV_WU_INPUT_MODE_PULL_DOWN)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetWUInputMode, L9952DRV_EID_PARAMETER2_OUT_OF_RANGE)) {
            return;
        }
    }
#endif

    if (mask & L9952DRV_MASK_WU1) {
        if (mode == L9952DRV_WU_INPUT_MODE_PULL_UP) {
            CtrlReg1[1] &= (uint8)~0x01U;
        }
        else {
            CtrlReg1[1] |= 0x01U;
        }
    }
    if (mask & L9952DRV_MASK_WU2) {
        if (mode == L9952DRV_WU_INPUT_MODE_PULL_UP) {
            CtrlReg1[1] &= (uint8)~0x02U;
        }
        else {
            CtrlReg1[1] |= 0x02U;
        }
    }
    if (mask & L9952DRV_MASK_WU3) {
        if (mode == L9952DRV_WU_INPUT_MODE_PULL_UP) {
            CtrlReg1[1] &= (uint8)~0x04U;
        }
        else {
            CtrlReg1[1] |= 0x04U;
        }
    }
    if (mask & L9952DRV_MASK_WU4) {
        if (mode == L9952DRV_WU_INPUT_MODE_PULL_UP) {
            CtrlReg1[1] &= (uint8)~0x08U;
        }
        else {
            CtrlReg1[1] |= 0x08U;
        }
    }
    L9952DRV_AL_SPI_WR(CtrlReg1 ,StatReg1); 
}


/******************************************************************************/
/*! @fn             void L9952drv_DisableWakeupSource (uint8 mask, uint8 bitpattern)
    @param[in]      mask sets wakeup source to be changed.
            Range: 0x00..0xFF
            Bit 0: 1 = Mask is active for WU1,0 = Mask is not active for WU1.
            Bit 1: 1 = Mask is active for WU2,0 = Mask is not active for WU2.
            Bit 2: 1 = Mask is active for WU3,0 = Mask is not active for WU3.
            Bit 3: 1 = Mask is active for WU4,0 = Mask is not active for WU4.
            Bit 4: 1 = Mask is active for open load of OUT1 wake up source,
                   0 = Mask is not active for open load of OUT1 wake up source.
            Bit 5: 1 = Mask is active for open load of OUT2 wake up source,
                   0 = Mask is not active for open load of OUT2 wake up source.
            Bit 6: 1 = Mask is active for open load of OUT3 wake up source,
                   0 = Mask is not active for open load of OUT3 wake up source.
            Bit 7: 1 = Mask is active for open load of OUT4 wake up source,
                   0 = Mask is not active for open load of OUT4 wake up source.
            Following constants are defined in L9952drv.h file:
            L9952DRV_MASK_OUT1, L9952DRV_MASK_OUT2, L9952DRV_MASK_OUT3,
            L9952DRV_MASK_OUT4, L9952DRV_MASK_WU1, L9952DRV_MASK_WU2,
            L9952DRV_MASK_WU3, L9952DRV_MASK_WU4.
            Example1: L9952DRV_MASK_OUT1 | L9952DRV_MASK_WU4 
            … mask is active for WU1 and openload of OUT4.
            Example2: L9952drv_DisableWakeupSource(0x32, 0x12);
            Or better by using predefined constants:
            L9952drv_DisableWakeupSource(L9952DRV_MASK_OUT1 | L9952DRV_MASK_OUT2
            | L9952DRV_MASK_WU2, L9952DRV_MASK_OUT1 | L9952DRV_MASK_WU2);
            Function disables wakeup source from OUT1 and WU2; and enables 
            wakeup source from OUT2. The rest reminds unchanged.
    @param[in]      bitpattern  Disables/enables wakeup functionality separately
                    for each wake up source. Particular bits are related to 
                    relevant wakeup sources in the same order as are defined by 
                    masks (see above). Each bit=1 disables related wakeup source
                    and each bit = 0 enables related wakeup source.
    @brief
Function enables / disables wakeup functionality separately for each wake up 
source defined by mask. Affected register: CR1.0..7 Note: Function updates SW 
driver internal copy of Control Register 1 and the register is immediately sent
to L9952 via SPI. Function refreshes SW driver internal copy of Status1 register
from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952 
via SPI.
*/
/******************************************************************************/

void L9952drv_DisableWakeupSource (uint8 mask, uint8 bitpattern) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_DisableWakeupSource, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    CtrlReg1[2] &= (uint8)~mask;
    CtrlReg1[2] |= (bitpattern & mask);
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetResetThresholdLevel (L9952drv_ResetThresholdLevelType level)
    @param[in]      level defines reset threshold level value
    @brief
Function sets reset threshold level of L9952. Affected register: CR2.8..9
Note: Function updates SW driver internal copy of Control Register 2 and the 
register is immediately sent to L9952 via SPI. Function refreshes SW driver 
internal copy of Status0 register from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_SetResetThresholdLevel (L9952drv_ResetThresholdLevelType level) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetResetThresholdLevel, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    switch (level) {
    case L9952DRV_RESET_THRESHOLD_4650:
        CtrlReg2[1] &= (uint8)~0x03U;
        break;
    case L9952DRV_RESET_THRESHOLD_4350:
        CtrlReg2[1] &= (uint8)~0x03U;
        CtrlReg2[1] |= 0x01U;
        break;
    default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
        L9952drv_ReportError (SID_L9952drv_SetResetThresholdLevel, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
        return;
    }
    L9952DRV_AL_SPI_WR(CtrlReg2, StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetInputFilterMode (uint8 mask, L9952drv_InputFilterModeType mode)
    @param[in]      mask sets which WU input filter settings will be changed.
                    Range: 0x00 .. 0x0F
                    Bit 0:  1 = Mask is active for WU1, 
                            0 = Mask is not active for WU1.
                    Bit 1:  1 = Mask is active for WU2, 
                            0 = Mask is not active for WU2.
                    Bit 2:  1 = Mask is active for WU3, 
                            0 = Mask is not active for WU3.
                    Bit 3:  1 = Mask is active for WU4, 
                            0 = Mask is not active for WU4.
                    Following constants are defined in L9952drv.h file:
                    L9952DRV_MASK_WU1, L9952DRV_MASK_WU2, L9952DRV_MASK_WU3,
                    L9952DRV_MASK_WU4.
                    Example: L9952DRV_MASK_WU1 | L9952DRV_MASK_WU4 …
                    mask is active for WU1 and WU4.
    @param[in]      mode sets filter timing for related WU inputs.
    @brief
Function controls filter for digital wake up inputs WU1, WU2, WU3 and WU4 of 
L9952. Affected register: CR2.10..17 Note: Function updates SW driver internal
copy of Control Register2 and the register is immediately sent to L9952 via SPI.
Function refreshes SW driver internal copy of Status0 register from L9952 via 
SPI.
Caveats: Function waits until the data are transferred completely to L9952 
via SPI.
*/
/******************************************************************************/

void L9952drv_SetInputFilterMode (uint8 mask, L9952drv_InputFilterModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    sint8 tmp;

    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetInputFilterMode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
    if (mask & (uint8)~0x0FU) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetInputFilterMode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE)) {
            return;
        }
    }
    tmp = (sint8)mode;
    if ((tmp < (sint8)L9952DRV_IN_FILTER_64) || (tmp > (sint8)L9952DRV_IN_FILTER_800_TIMER1)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetInputFilterMode, L9952DRV_EID_PARAMETER2_OUT_OF_RANGE)) {
            return;
        }
    }
#endif

    if (mask & L9952DRV_MASK_WU1) {
        CtrlReg2[1] &= (uint8)~0x0CU;
        CtrlReg2[1] |= (uint8)((uint8)mode << 2) & 0x0CU;
    }
    if (mask & L9952DRV_MASK_WU2) {
        CtrlReg2[1] &= (uint8)~0x30U;
        CtrlReg2[1] |= (uint8)((uint8)mode << 4) & 0x30U;
    }
    if (mask & L9952DRV_MASK_WU3) {
        CtrlReg2[1] &= (uint8)~0xC0U;
        CtrlReg2[1] |= (uint8)((uint8)mode << 6) & 0xC0U;
    }
    if (mask & L9952DRV_MASK_WU4) {
        CtrlReg2[0] &= (uint8)~0x03U;
        CtrlReg2[0] |= (uint8)mode & 0x03U;
    }
    L9952DRV_AL_SPI_WR(CtrlReg2 ,StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetOutOLThresholdLevel (uint8 mask, L9952drv_OutOLThresholdLevelType level)
    @param[in]      mask sets by mask for which output will be changed OLT level
                    Range: 0..0xF0
                    Bit 4:  1 = Mask is active for OUT1, 
                            0 = Mask is not active for OUT1.
                    Bit 5:  1 = Mask is active for OUT 2, 
                            0 = Mask is not active for OUT2.
                    Bit 6:  1 = Mask is active for OUT 3, 
                            0 = Mask is not active for OUT3.
                    Bit 7:  1 = Mask is active for OUT 4, 
                            0 = Mask is not active for OUT4.
                    Following constants are defined in L9952drv.h file:
                    L9952DRV_MASK_OUT1, L9952DRV_MASK_OUT2, L9952DRV_MASK_OUT3
                    L9952DRV_MASK_OUT4.
                    Example: L9952DRV_MASK_OUT1 | L9952DRV_MASK_OUT 4 mask is 
                    active for OUT1 and OUT4.
    @param[in]      level defines level for open load detection for related
                    HS outputs.
    @brief
Function sets openload detection level for selected HS outputs 1..4 of L9952.
Affected register: CR2.0..3 Note: Function updates SW driver internal copy of
Control Register 2 and the register is immediately sent to L9952 via SPI.
Function refreshes SW driver internal copy of Status0 register from L9952 via
SPI.
Caveats: Function waits until the data are transferred completely to L9952 via 
SPI.
*/
/******************************************************************************/

void L9952drv_SetOutOLThresholdLevel (uint8 mask, L9952drv_OutOLThresholdLevelType level) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetOutOLThresholdLevel, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
    if (mask & (uint8)~0xF0U) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetOutOLThresholdLevel, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE)) {
            return;
        }
    }
    if ((level != L9952DRV_OUT_OLTHRESHOLD_2) && (level != L9952DRV_OUT_OLTHRESHOLD_8)) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetOutOLThresholdLevel, L9952DRV_EID_PARAMETER2_OUT_OF_RANGE)) {
            return;
        }
    }
#endif

    if (mask & L9952DRV_MASK_OUT1) {
        if (level == L9952DRV_OUT_OLTHRESHOLD_2) {
            CtrlReg2[2] &= (uint8)~0x01U;
        }
        else {
            CtrlReg2[2] |= 0x01U;
        }
    }
    if (mask & L9952DRV_MASK_OUT2) {
        if (level == L9952DRV_OUT_OLTHRESHOLD_2) {
            CtrlReg2[2] &= (uint8)~0x02U;
        }
        else {
            CtrlReg2[2] |= 0x02U;
        }
    }
    if (mask & L9952DRV_MASK_OUT3) {
        if (level == L9952DRV_OUT_OLTHRESHOLD_2) {
            CtrlReg2[2] &= (uint8)~0x04U;
        }
        else {
            CtrlReg2[2] |= 0x04U;
        }
    }
    if (mask & L9952DRV_MASK_OUT4) {
        if (level == L9952DRV_OUT_OLTHRESHOLD_2) {
            CtrlReg2[2] &= (uint8)~0x08U;
        }
        else {
            CtrlReg2[2] |= 0x08U;
        }
    }
    L9952DRV_AL_SPI_WR(CtrlReg2 ,StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_LinSetup (L9952drv_LinSetupType value)
    @param[in]      value contains on bits 0..2 LIN setup values for pull up 
                    enabling, dominant TxD timeout and LIN slope

    @brief
Function sets LIN configuration. Affected register: CR2.6, 2.7, 2.18.
Note: Function updates SW driver internal copy of Control Register 2 and the
register is immediately sent to L9952 via SPI. Function refreshes SW driver
internal copy of Status0 register from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952 via 
SPI.
*/
/******************************************************************************/
/*! @def SLOPE_0
For internal purpose of L9952drv_LinSetup() only */
/*! @def SLOPE_1
For internal purpose of L9952drv_LinSetup() only */
/*! @def TXD_TOUT_DIS
For internal purpose of L9952drv_LinSetup() only */
/*! @def TXD_TOUT_EN
For internal purpose of L9952drv_LinSetup() only */
/*! @def PUP_EN
For internal purpose of L9952drv_LinSetup() only */
/*! @def PUP_DIS
For internal purpose of L9952drv_LinSetup() only */

#define SLOPE_0 (CtrlReg2[0] &= (uint8)~0x04U)
#define SLOPE_1 (CtrlReg2[0] |= 0x04U)

#define TXD_TOUT_DIS (CtrlReg2[2] |= 0x80U)
#define TXD_TOUT_EN  (CtrlReg2[2] &= (uint8)~0x80U)

#define PUP_EN (CtrlReg2[2] &= (uint8)~0x40U)
#define PUP_DIS (CtrlReg2[2] |= 0x40U)

void L9952drv_LinSetup (L9952drv_LinSetupType value) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_LinSetup, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    switch (value) {
        case L9952DRV_LIN_SL_DI_TIM_EN_PUP_EN:
            SLOPE_0;
            TXD_TOUT_EN;
            PUP_EN;
            break;
        case L9952DRV_LIN_SL_DI_TIM_EN_PUP_DI:
            SLOPE_0;
            TXD_TOUT_EN;
            PUP_DIS;
            break;
        case L9952DRV_LIN_SL_DI_TIM_DI_PUP_EN:
            SLOPE_0;
            TXD_TOUT_DIS;
            PUP_EN;
            break;
        case L9952DRV_LIN_SL_DI_TIM_DI_PUP_DI:
            SLOPE_0;
            TXD_TOUT_DIS;
            PUP_DIS;
            break;
        case L9952DRV_LIN_SL_EN_TIM_EN_PUP_EN:
            SLOPE_1;
            TXD_TOUT_EN;
            PUP_EN;
            break;
        case L9952DRV_LIN_SL_EN_TIM_EN_PUP_DI:
            SLOPE_1;
            TXD_TOUT_EN;
            PUP_DIS;
            break;
        case L9952DRV_LIN_SL_EN_TIM_DI_PUP_EN:
            SLOPE_1;
            TXD_TOUT_DIS;
            PUP_EN;
            break;
        case L9952DRV_LIN_SL_EN_TIM_DI_PUP_DI:
            SLOPE_1;
            TXD_TOUT_DIS;
            PUP_DIS;
            break;
        default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
            L9952drv_ReportError (SID_L9952drv_LinSetup, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
            return;                 /* parameter value out of range */
    }
    L9952DRV_AL_SPI_WR(CtrlReg2 ,StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_ClearStatusRegisters (void)
    @brief
Function clears content of both status registers directly in L9952.
Affected register: CR1.21
Note: Function updates SW driver internal copy of Control Register 1 and the
register is immediately sent to L9952 via SPI. Than it changes back internal
copy of Control Register 1 and the register is immediately sent to L9952 via SPI
again. Function refreshes SW driver internal copy of Status1 register from L9952
via SPI.
Caveats: Function waits until the data are transferred completely to L9952 via 
SPI.
*/
/******************************************************************************/

void L9952drv_ClearStatusRegisters (void) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_ClearStatusRegisters, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    CtrlReg1[0] |= 0x20U;
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
    CtrlReg1[0] &= (uint8)~0x20U;
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetVsLockoutMode (L9952drv_VsLockoutModeType mode)
    @param[in]      mode selects L9952 behavior after Vs recovery
    @brief
Function enables automatic recovery after Vs over/under-voltage recovery of
L9952. Affected register: CR2.4 Note: Function updates SW driver internal copy
of Control Register 2 and the register is immediately sent to L9952 via SPI.
Function refreshes SW driver internal copy of Status0 register from L9952 via 
SPI.
Function waits until the data are transferred completely to L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952 via 
SPI.
*/
/******************************************************************************/
void L9952drv_SetVsLockoutMode (L9952drv_VsLockoutModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetVsLockoutMode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    switch (mode) {
        case L9952DRV_VS_LOCKOUT_DISABLE:
            CtrlReg2[2] &= (uint8)~0x10U;
            break;
        case L9952DRV_VS_LOCKOUT_ENABLE:
            CtrlReg2[2] |= 0x10U;
            break;
        default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
            L9952drv_ReportError (SID_L9952drv_SetVsLockoutMode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
            return;
    }
    L9952DRV_AL_SPI_WR(CtrlReg2, StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_WdgTrigger (void)
    @brief
Function triggers the watchdog hardware. It has to be called periodically by 
upper layer function (usually the watchdog manager) in order to prevent the 
watchdog hardware from expiring. Right timing is essential. For more detail see
L9952 datasheet. Affected register: CR0.19
It is useful to periodically refresh dedicated bit positions of main internal 
variables from security point of view. This function was chosen as right place
to do it.
Function writes internal copy of Control Register 0 to L9952 device via SPI.
Function protects the user from taking care about special conditions related to
WD handling after wake up from stand by modes. Function refreshes driver 
internal copy of Status0 register from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952 
via SPI.
*/
/******************************************************************************/

void L9952drv_WdgTrigger (void) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_WdgTrigger, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif

/* It is useful to periodically refresh dedicated bit positions of main internal
      variables from security point of view. This function was chosen as right
      place to do it. */
    CtrlReg0[0] &= (uint8)~0x80U;
    CtrlReg0[0] &= (uint8)~0x40U;   /* more efficient than &~0xC0 at 8bit CPU */
    CtrlReg1[0] &= (uint8)~0x80U;
    CtrlReg1[0] |= 0x40U;
    CtrlReg2[0] |= 0x80U;
    CtrlReg2[0] &= (uint8)~0x40U;

    CtrlReg0[0] ^= 0x08U;           /* refresh WD */ 
    L9952DRV_AL_SPI_WR(CtrlReg0, StatReg0);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetRelayShutdownMode(L9952drv_RelayShutdownModeType mode)
    @param[in]      mode selects L9952 behavior of relay output during 
                    under/over-voltage
    @brief          
Function enables automatic shutdown of relay outputs during 
Vs over/under-voltage of L9952. Affected register: CR2.19 Note: Function updates
SW driver internal copy of Control Register 2 and the register is immediately
sent to L9952 via SPI. Function refreshes SW driver internal copy of Status0
register from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_SetRelayShutdownMode (L9952drv_RelayShutdownModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetRelayShutdownMode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif

    switch (mode) {
        case L9952DRV_RELAY_SHUTDOWN_ENABLE:
            CtrlReg2[0] &= (uint8)~0x08U;
            break;
        case L9952DRV_RELAY_SHUTDOWN_DISABLE:
            CtrlReg2[0] |= 0x08U;
            break;
        default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
            L9952drv_ReportError (SID_L9952drv_SetRelayShutdownMode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
            return;
    }
    L9952DRV_AL_SPI_WR(CtrlReg2, StatReg0);
}

/******************************************************************************/
/*! @fn             bool L9952drv_GetGlobalErrorStatus (void)
    @return         TRUE  .. global error status is set, (at least one error 
                            flag is set), 
                    FALSE .. global error status is reset (no error)
    @brief          
Function gets status of cumulative error bit of L9952. This function is 
implemented with using of L9952drv_GetStatus0() function. Note: This status is
possible to get by regular reading of complete Status register 0 (or 1) or read
just first byte of Status register 0 (or 1). The shortest method is to read SPI
DO bit while SPI CS(chipselect) is active and SPI is not clocked. SPI must not
be communicating during this procedure to avoid SPI conflict. 
Caveats: To read just SPI DO bit while SPI CS(chipselect) is active is not SPI
standard operation. MCU related SPI driver maybe does not support such
functionality and troubles would appear in L9952 SPI adaptation layer with
implementation. Function waits until the data are transferred completely to
L9952 via SPI.
*/
/******************************************************************************/

bool L9952drv_GetGlobalErrorStatus (void) {

    L9952drv_StatusRegType tmp;

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_GetGlobalErrorStatus, L9952DRV_EID_UNINIT)) {
            return (TRUE);          /* return Global error to upper function */
        }
    }
#endif
    
    L9952drv_GetStatus0(&tmp);
    if (tmp & 0x0800000U) {         /* bit 23 contains glogal error status */
        return (TRUE);
    }
    else {
        return (FALSE);
    }
}


/******************************************************************************/
/*! @fn             void L9952drv_GetStatus0 (L9952drv_StatusRegType *DataPtr)  
    @param[out]     *DataPtr points to data structure which will be filled with
                    Status0.
    @brief          
Function reads actual status from L9952 via SPI and than files data structure
with Staus0 data. (Control register 2 is refreshed to L9952 from SW driver
internal copy via SPI to read Status register 0 via SPI.)
Caveats: Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_GetStatus0 (L9952drv_StatusRegType *DataPtr) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_GetStatus0, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    L9952DRV_AL_SPI_WR(CtrlReg2, StatReg0);
    *DataPtr = (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg0[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg0[1]<<8)
             + (L9952drv_StatusRegType)StatReg0[2];
}


/******************************************************************************/
/*! @fn             void L9952drv_ReadStatus0 (L9952drv_StatusRegType *DataPtr)
    @param[out]     *DataPtr points to data structure which will be filled with
                    Status0.
    @brief          
Function files data structure with latest SW driver internal copy of Status 0
data. 
Caveats: Function returns internal data copy. Status 0 is not refreshed by
reading status from L9952 by SPI. Internal data copy of Status0 is refreshed
every watchdog triggering by calling of L9952drv_WdgTrigger() function i.e.
periodically with period 10ms.
*/
/******************************************************************************/

void L9952drv_ReadStatus0 (L9952drv_StatusRegType *DataPtr) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_ReadStatus0, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    *DataPtr = (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg0[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg0[1]<<8)
             + (L9952drv_StatusRegType)StatReg0[2];
}


/******************************************************************************/
/*! @fn             void L9952drv_GetStatus1 (L9952drv_StatusRegType *DataPtr)
    @param[out]     *DataPtr points to data structure which will be filled with
                    Status1.
    @brief          
Function reads actual status from L9952 via SPI and than files data structure
with Staus1 data. (Control register 1 is refreshed to L9952 from SW driver 
internal copy via SPI to read Status register 1 via SPI.) 
Caveats: Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_GetStatus1 (L9952drv_StatusRegType *DataPtr) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_GetStatus1, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
    *DataPtr = (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg1[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg1[1]<<8)
             + (L9952drv_StatusRegType)StatReg1[2];
}


/******************************************************************************/
/*! @fn             void L9952drv_ReadStatus1 (L9952drv_StatusRegType *DataPtr)
    @param[out]     *DataPtr points to data structure which will be filled with
                    Status1.
    @brief          
Function files data structure with latest SW driver internal copy of Staus1
data. 
Caveats: Function returns internal data copy. Status 1 is not refreshed by
reading status from L9952 by SPI. Use function L9952drv_GetStatus1() to get
actual refreshed data via SPI.
*/
/******************************************************************************/

void L9952drv_ReadStatus1 (L9952drv_StatusRegType *DataPtr) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_ReadStatus1, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    *DataPtr = (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg1[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)StatReg1[1]<<8)
             + (L9952drv_StatusRegType)StatReg1[2];
}


/******************************************************************************/
/*! @fn             void L9952drv_SetIntMode(L9952drv_IntModeType mode)
    @param[in]      mode selects L9952 interrupt mode
    @brief          

Function selects L9952 interrupt mode of L9952. Affected register: CR1.20
Note: Function updates SW driver internal copy of Control Register 1 and 
the register is immediately sent to L9952 via SPI. Note: Function refreshes
SW driver internal copy of Status1 register from L9952 via SPI.
Caveats: Function waits until the data are transferred completely to L9952
via SPI.
*/
/******************************************************************************/

void L9952drv_SetIntMode(L9952drv_IntModeType mode) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_IntMode, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif

    switch (mode) {
        case L9952DRV_INT_DISABLE:
            CtrlReg1[0] &= (uint8)~0x10U;
            break;
        case L9952DRV_INT_ENABLE:
            CtrlReg1[0] |= 0x10U;
            break;
        default:
#ifdef  L9952DRV_DEV_ERROR_DETECT
            L9952drv_ReportError (SID_L9952drv_IntMode, L9952DRV_EID_PARAMETER1_OUT_OF_RANGE);
#endif
            return;
    }
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
}


/******************************************************************************/
/*! @fn             void L9952drv_SetVReg1CurrentMonitorOn (void)
    @brief
Function for internal purpose only.
Function sets ON Voltage regulator 1 current monitoring mode of L9952 in V1 
stand by mode. Affected register: CR2.20. Note: Function updates SW driver 
internal copy of Control Register 2 and the register is immediately sent to 
L9952 via SPI. Function refreshes driver internal copy of Status0 register
from L9952 via SPI. 
*/
/******************************************************************************/

void L9952drv_SetVReg1CurrentMonitorOn (void) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_SetVReg1CurrentMonitorOn, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    CtrlReg2[0] &= (uint8)~0x10U;
    L9952DRV_AL_SPI_WR(CtrlReg2, StatReg0);
}

/*******************************************************************************
********************************************************************************
                    Functions for internal purpose only.                        
********************************************************************************
*******************************************************************************/

/******************************************************************************/
/*! @fn             void L9952drv_ReadControl0 (L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function reads internal copy of Control register 0. 
*/
/******************************************************************************/
void L9952drv_ReadControl0 (L9952drv_StatusRegType *DataPtr) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_ReadControl0, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    *DataPtr = (L9952drv_StatusRegType)((L9952drv_StatusRegType)CtrlReg0[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)CtrlReg0[1]<<8)
             + (L9952drv_StatusRegType)CtrlReg0[2];
}

/******************************************************************************/
/*! @fn             void L9952drv_ReadControl1 (L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function reads internal copy of Control register 1. 
*/
/******************************************************************************/
void L9952drv_ReadControl1 (L9952drv_StatusRegType *DataPtr) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_ReadControl1, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    *DataPtr = (L9952drv_StatusRegType)((L9952drv_StatusRegType)CtrlReg1[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)CtrlReg1[1]<<8)
             + (L9952drv_StatusRegType)CtrlReg1[2];
}


/******************************************************************************/
/*! @fn             void L9952drv_ReadControl2 (L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function reads internal copy of Control register 2. 
*/
/******************************************************************************/
void L9952drv_ReadControl2 (L9952drv_StatusRegType *DataPtr) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_ReadControl2, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    *DataPtr = (L9952drv_StatusRegType)((L9952drv_StatusRegType)CtrlReg2[0]<<16)
             + (L9952drv_StatusRegType)((L9952drv_StatusRegType)CtrlReg2[1]<<8)
             + (L9952drv_StatusRegType)CtrlReg2[2];
}

/******************************************************************************/
/*! @fn         void L9952drv_WRControl0 (const L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function replaces internal copy of Control register 0. (bits 19 and 22 and 23
are not changable)
*/
/******************************************************************************/
void L9952drv_WRControl0 (const L9952drv_StatusRegType *DataPtr) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_WRControl0, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    CtrlReg0[2] = (uint8)(*DataPtr);
    CtrlReg0[1] = (uint8)(*DataPtr>>8);
    CtrlReg0[0] = (CtrlReg0[0] & 0x08U) | ((uint8)(*DataPtr>>16) & 0x37U);
    L9952DRV_AL_SPI_WR(CtrlReg0, StatReg0);
}


/******************************************************************************/
/*! @fn         void L9952drv_WRControl1 (const L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function replaces internal copy of Control register 1. (bits 22 and 23
are not changable)
*/
/******************************************************************************/
void L9952drv_WRControl1 (const L9952drv_StatusRegType *DataPtr) {
    
#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_WRControl1, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    CtrlReg1[2] = (uint8)(*DataPtr);
    CtrlReg1[1] = (uint8)(*DataPtr>>8);
    CtrlReg1[0] = ((uint8)(*DataPtr>>16) & 0x3FU) | (uint8)(0x01U << 6);
    L9952DRV_AL_SPI_WR(CtrlReg1, StatReg1);
}


/******************************************************************************/
/*! @fn         void L9952drv_WRControl2 (const L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function replaces internal copy of Control register 2. (bits 22 and 23
are not changable)
*/
/******************************************************************************/
void L9952drv_WRControl2 (const L9952drv_StatusRegType *DataPtr) {

#ifdef  L9952DRV_DEV_ERROR_DETECT
    if (!InitFlag) {
        if (FALSE == L9952drv_ReportError (SID_L9952drv_WRControl2, L9952DRV_EID_UNINIT)) {
            return;
        }
    }
#endif
    CtrlReg2[2] = (uint8)(*DataPtr);
    CtrlReg2[1] = (uint8)(*DataPtr>>8);
    CtrlReg2[0] = ((uint8)(*DataPtr>>16) & 0x3FU) | (uint8)(0x02U << 6);
    L9952DRV_AL_SPI_WR(CtrlReg2, StatReg0);
}
