/******************************************************************************/
/*! Project Name:   L9952 driver
    @file           L9952drv.h
    @version        $Revision: 1.4 $
    @date           $Date: 2007/04/23 09:49:31 $
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

*******************************************************************************/

#ifndef L9952DRV_H
#define L9952DRV_H

/*
  File version information
*/
#define L9952DRV_H_MAJOR_VERSION  1
#define L9952DRV_H_MINOR_VERSION  1
#define L9952DRV_H_PATCH_VERSION  0
#define L9952DRV_H_BUILD_REVISION "$Revision: 1.4 $"


#include "L9952drv_Cfg.h"
#include "Std_Types.h"

#if L9952DRV_H_MAJOR_VERSION != L9952DRV_CFG_H_MAJOR_VERSION
    #error "Wrong version of L9952drv_cfg.H"
#endif

/*******************************************************************************
*****************************   Function listing   *****************************
********************************************************************************
bool L9952drv_ReportError (uint8 ServiceId, uint8 ErrorId);
void L9952drv_Init (void);
void L9952drv_SetStandbyMode(L9952drv_StandbyModeType mode);
void L9952drv_SetOutMode (uint8 mask, L9952drv_OutModeType mode);
void L9952drv_SetOutHSAutorecovery (L9952drv_OutHSAutorecoveryType mode);
void L9952drv_SetRelayOutput (L9952drv_RelayOutputType value);
void L9952drv_SetVoltageReg2Mode (L9952drv_VoltageReg2ModeType mode);
void L9952drv_SetTimer1(L9952drv_Timer1PeriodType period, L9952drv_Timer1ONTimeType ontime);
void L9952drv_SetTimer2(L9952drv_Timer2ONTimeType ontime);
void L9952drv_SetDigOutput(L9952drv_DigOutputModeType mode);
void L9952drv_SetWUInputMode(uint8 mask, L9952drv_WUInputModeType mode);
void L9952drv_DisableWakeupSource(uint8 mask, uint8 bitpattern);
void L9952drv_SetResetThresholdLevel(L9952drv_ResetThresholdLevelType level);
void L9952drv_SetInputFilterMode(uint8 mask, L9952drv_InputFilterModeType mode);
void L9952drv_SetOutOLThresholdLevel (uint8 mask, L9952drv_OutOLThresholdLevelType level);
void L9952drv_LinSetup(L9952drv_LinSetupType value);
void L9952drv_ClearStatusRegisters(void);
void L9952drv_SetVsLockoutMode(L9952drv_VsLockoutModeType mode);
void L9952drv_WdgTrigger(void);
void L9952drv_SetRelayShutdownMode(L9952drv_RelayShutdownModeType mode);
bool L9952drv_GetGlobalErrorStatus(void);
void L9952drv_GetStatus0(L9952drv_StatusRegType *DataPtr);
void L9952drv_ReadStatus0(L9952drv_StatusRegType *DataPtr);
void L9952drv_GetStatus1(L9952drv_StatusRegType *DataPtr);
void L9952drv_ReadStatus1(L9952drv_StatusRegType *DataPtr);
void L9952drv_SetIntMode(L9952drv_IntModeType mode);
******************* Functions for internal purpose only **********************
void L9952drv_ReadControl0(L9952drv_StatusRegType *DataPtr);
void L9952drv_ReadControl1(L9952drv_StatusRegType *DataPtr);
void L9952drv_ReadControl2(L9952drv_StatusRegType *DataPtr);
void L9952drv_WRControl0(L9952drv_StatusRegType *DataPtr);
void L9952drv_WRControl1(L9952drv_StatusRegType *DataPtr);
void L9952drv_WRControl2(L9952drv_StatusRegType *DataPtr);
*******************************************************************************/


/*******************************************************************************
******************* macros for generating debugging messages *******************
*******************************************************************************/

/*******************************************************************************
************************** Public Constants and Variables **********************
*******************************************************************************/

/*! @def L9952DRV_MASK_OUT1
    Defines mask for output OUT1 of L9952. */
/*! @def L9952DRV_MASK_OUT2
    Defines mask for output OUT2 of L9952. */
/*! @def L9952DRV_MASK_OUT3
    Defines mask for output OUT3 of L9952. */
/*! @def L9952DRV_MASK_OUT4
    Defines mask for output OUT4 of L9952. */
/*! @def L9952DRV_MASK_OUTHS
    Defines mask for output OUTHS of L9952. */
/*! @def L9952DRV_MASK_WU1
    Defines mask for wakup input WU1 of L9952. */
/*! @def L9952DRV_MASK_WU2
    Defines mask for wakup input WU2 of L9952. */
/*! @def L9952DRV_MASK_WU3
    Defines mask for wakup input WU3 of L9952. */
/*! @def L9952DRV_MASK_WU4
    Defines mask for wakup input WU4 of L9952. */
    
#define L9952DRV_MASK_OUT1  0x10U
#define L9952DRV_MASK_OUT2  0x20U
#define L9952DRV_MASK_OUT3  0x40U
#define L9952DRV_MASK_OUT4  0x80U
#define L9952DRV_MASK_OUTHS 0x01U
#define L9952DRV_MASK_WU1   0x01U
#define L9952DRV_MASK_WU2   0x02U
#define L9952DRV_MASK_WU3   0x04U
#define L9952DRV_MASK_WU4   0x08U


#ifdef L9952DRV_DEV_ERROR_DETECT
/*******************************************************************************
******************** Service ID constants for all functions ********************
*******************************************************************************/
/*! @def SID_L9952drv_Init
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetStandbyMode
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetOutMode
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetOutHSAutorecovery 
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetRelayOutput
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetVoltageReg2Mode 
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetTimer1
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetTimer2
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetDigOutput
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetWUInputMode
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_DisableWakeupSource
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetResetThresholdLevel
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetInputFilterMode
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetOutOLThresholdLevel
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_LinSetup
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_ClearStatusRegisters
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetVsLockoutMode
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_WdgTrigger
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetRelayShutdownMode
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_GetGlobalErrorStatus
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_GetStatus0
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_ReadStatus0
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_GetStatus1
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_ReadStatus1
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_IntMode
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_SetVReg1CurrentMonitorOn
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_ReportError
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_ReadControl0
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_ReadControl1
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_ReadControl2
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_WRControl0
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_WRControl1
    Defines Service ID of relevant function for Error detectiong purpose.*/
/*! @def SID_L9952drv_WRControl2
    Defines Service ID of relevant function for Error detectiong purpose.*/

#define SID_L9952drv_Init 0U
#define SID_L9952drv_SetStandbyMode 1U
#define SID_L9952drv_SetOutMode 2U
#define SID_L9952drv_SetOutHSAutorecovery 3U
#define SID_L9952drv_SetRelayOutput 4U
#define SID_L9952drv_SetVoltageReg2Mode 5U
#define SID_L9952drv_SetTimer1 6U
#define SID_L9952drv_SetTimer2 7U
#define SID_L9952drv_SetDigOutput 8U
#define SID_L9952drv_SetWUInputMode 9U
#define SID_L9952drv_DisableWakeupSource 10U
#define SID_L9952drv_SetResetThresholdLevel 11U
#define SID_L9952drv_SetInputFilterMode 12U
#define SID_L9952drv_SetOutOLThresholdLevel 13U
#define SID_L9952drv_LinSetup 14U
#define SID_L9952drv_ClearStatusRegisters 15U
#define SID_L9952drv_SetVsLockoutMode 16U
#define SID_L9952drv_WdgTrigger 17U
#define SID_L9952drv_SetRelayShutdownMode 18U
#define SID_L9952drv_GetGlobalErrorStatus 19U
#define SID_L9952drv_GetStatus0 20U
#define SID_L9952drv_ReadStatus0 21U
#define SID_L9952drv_GetStatus1 22U
#define SID_L9952drv_ReadStatus1 23U
#define SID_L9952drv_SetVReg1CurrentMonitorOn 24U
#define SID_L9952drv_IntMode 25U
/******************* Functions for internal purpose only **********************/
#define SID_L9952drv_ReportError 100U
#define SID_L9952drv_ReadControl0 101U
#define SID_L9952drv_ReadControl1 102U
#define SID_L9952drv_ReadControl2 103U
#define SID_L9952drv_WRControl0 104U
#define SID_L9952drv_WRControl1 105U
#define SID_L9952drv_WRControl2 106U

/*******************************************************************************
****************** Error ID constants common for all functions *****************
*******************************************************************************/
/*! @def L9952DRV_EID_OK
    Defines Error ID for Error detectiong purpose - OK no error */
/*! @def L9952DRV_EID_PARAMETER1_OUT_OF_RANGE
    Defines Error ID for Error detectiong purpose - Wrong parameter 1 */
/*! @def L9952DRV_EID_PARAMETER2_OUT_OF_RANGE
    Defines Error ID for Error detectiong purpose - Wrong parameter 2 */
/*! @def L9952DRV_EID_UNINIT
    Defines Error ID for Error detectiong purpose - Driver not initialized */

#define L9952DRV_EID_OK 00U
#define L9952DRV_EID_PARAMETER1_OUT_OF_RANGE 11U
#define L9952DRV_EID_PARAMETER2_OUT_OF_RANGE 12U
#define L9952DRV_EID_UNINIT 20U

#endif
/*******************************************************************************
***************************** New type definition ******************************
*******************************************************************************/


/*! Defines Stand by modes of L9952. */
typedef enum { 
    L9952DRV_STANDBYMODE_V1,    /*!< Switch L9952 to V1 stand by mode. */
    L9952DRV_STANDBYMODE_VBAT   /*!< Switch L9952 to Vbat stand by mode. */
}L9952drv_StandbyModeType;


/*! Defines output mode of HS outputs. */
typedef enum {
    L9952DRV_OUT_MODE_OFF,      /*!< Driver is OFF in all modes.*/
    L9952DRV_OUT_MODE_ON,       /*!< Driver is ON in active mode, OFF in standby
                                    mode.*/
    L9952DRV_OUT_MODE_TIMER1,   /*!< Driver is cyclic ON with the timing of
                                    Timer1 in active mode and stand by modes.*/
    L9952DRV_OUT_MODE_TIMER2,   /*!< Driver is cyclic ON with the timing of
                                    Timer2 in active mode and stand by modes.*/
    L9952DRV_OUT_MODE_PWM1,     /*!< Driver is controlled by the PWM1 input.*/
    L9952DRV_OUT_MODE_PWM2      /*!< Driver is controlled by the PWM2 input.*/
} L9952drv_OutModeType;


/*! Defines states for OUT HS output autorecovery functionality controlling. */
typedef enum {
    L9952DRV_OUTHS_AUTORECOVERY_OFF,    /*!< Disables autorecovery functionality
                                            for OUT HS output of L9952.*/
    L9952DRV_OUTHS_AUTORECOVERY_ON      /*!< Enables autorecovery functionality 
                                            for OUT HS output of L9952.*/
} L9952drv_OutHSAutorecoveryType;


/*! Defines states for relay outputs controlling.*/
typedef enum {
    RELAYOUTPUT_OFF_OFF,    /*!< Switch both relays off.*/
    RELAYOUTPUT_ON_OFF,     /*!< Switch relay REL1 on and REL2 off.*/
    RELAYOUTPUT_OFF_ON,     /*!< Switch relay REL1 off and REL2 on.*/
    RELAYOUTPUT_ON_ON,      /*!< Switch both relays on.*/
    RELAYOUTPUT_OFF_X,      /*!< Switch relay REL1 off and refresh previous 
                                state of REL2 (don’t change).*/
    RELAYOUTPUT_ON_X,       /*!< Switch relay REL1 on and refresh previous 
                                stateof REL2 (don’t change).*/
    RELAYOUTPUT_X_OFF,      /*!< Switch relay REL2 off and refresh previous
                                state of REL1 (don’t change).*/
    RELAYOUTPUT_X_ON        /*!< Switch relay REL2 on and refresh previous
                                state of REL1 (don’t change).*/
} L9952drv_RelayOutputType;


/*! Defines modes of L9952 voltage regulator 2.*/
typedef enum {
    L9952DRV_VOLTAGE_REG2_OFF,          /*!< Switch voltage regulator 2 always
                                            off.*/
    L9952DRV_VOLTAGE_REG2_ON_ACTIVE,    /*!< Switch voltage regulator 2 on only
                                            when L9952 is in active mode.*/
    L9952DRV_VOLTAGE_REG2_ON_V1,        /*!< Switch voltage regulator 2 on only
                                            when L9952 is in active mode or V1
                                            standby mode.*/
    L9952DRV_VOLTAGE_REG2_ON            /*!< Switch voltage regulator 2 always
                                            on.*/
} L9952drv_VoltageReg2ModeType;


/*! Defines period of L9952 timer 1.*/
typedef enum {
    L9952DRV_TIMER1PERIOD_500,      /*!< Set timer 1 period to 0.5s.*/
    L9952DRV_TIMER1PERIOD_1000,     /*!< Set timer 1 period to 1s.*/
    L9952DRV_TIMER1PERIOD_1500,     /*!< Set timer 1 period to 1.5s.*/
    L9952DRV_TIMER1PERIOD_2000,     /*!< Set timer 1 period to 2s.*/
    L9952DRV_TIMER1PERIOD_2500,     /*!< Set timer 1 period to 2.5s.*/
    L9952DRV_TIMER1PERIOD_3000,     /*!< Set timer 1 period to 3s.*/
    L9952DRV_TIMER1PERIOD_3500,     /*!< Set timer 1 period to 3.5s.*/
    L9952DRV_TIMER1PERIOD_4000      /*!< Set timer 1 period to 4s.*/
} L9952drv_Timer1PeriodType;


/*! Defines ON Time parameter of L9952 timer 1.*/
typedef enum {
    L9952DRV_TIMER1ONTIME_10,       /*!< Defines ON time value 10ms.*/
    L9952DRV_TIMER1ONTIME_20        /*!< Defines ON time value 20ms.*/
} L9952drv_Timer1ONTimeType;

/*! Defines ON Time parameter value for timer 2 of L9952.*/
typedef enum {
    L9952DRV_TIMER2ONTIME_01,       /*!< Defines ON time value 100us.*/
    L9952DRV_TIMER2ONTIME_1         /*!< Defines ON time value 1ms.*/
} L9952drv_Timer2ONTimeType;


/*! Defines which signals are looped to digital outputs Dig_Out3
and Dig_Out4.*/
typedef enum {
    L9952DRV_DO_WU3_WU4,        /*!< Set Dig_Out3 to loopback of WU3 and set
                                    Dig_Dut4 to loopback of WU4.*/
    L9952DRV_DO_HIZ_WU4,        /*!< Set Dig_Out3 to Hi impedance and set 
                                    Dig_Dut4 to loopback of WU4.*/
    L9952DRV_DO_WU3_HIZ,        /*!< Set Dig_Out3 to loopback of WU3 and set 
                                    Dig_Dut4 to Hi impedance.*/
    L9952DRV_DO_WU3_OLHS2,      /*!< Set Dig_Out3 to loopback of WU3 and set 
                                    Dig_Out4 to loopback of open load state of 
                                    OUT2.*/
    L9952DRV_DO_OLHS1_WU4,      /*!< Set Dig_Out3 to loopback of open load state
                                    of OUT1 and set Dig_Out4 to loopback WU4.*/
    L9952DRV_DO_OLHS1_OLHS2,    /*!< Set Dig_Out3 to loopback of open load state
                                    of OUT1 and set Dig_Out4 to loopback of open
                                    load state of OUT2.*/
    L9952DRV_DO_OLHS1_HIZ,      /*!< Set Dig_Out3 to loopback of open load state
                                    of OUT1 and set Dig_Out4 to Hi impedance.*/
    L9952DRV_DO_HIZ_OLHS2       /*!< Set Dig_Out3 to Hi impedance and set 
                                    Dig_Out4 to loopback of open load state of 
                                    OUT2.*/
} L9952drv_DigOutputModeType;


/*! Defines pull up/down mode for WU related inputs.*/
typedef enum {
    L9952DRV_WU_INPUT_MODE_PULL_UP,     /*!< Defines pull up mode for related
                                            WU input.*/
    L9952DRV_WU_INPUT_MODE_PULL_DOWN    /*!< Defines pull down mode for related
                                            WU input.*/
} L9952drv_WUInputModeType;


/*! Defines input filter configuration for related WU inputs.*/
typedef enum {
    L9952DRV_IN_FILTER_64,         /*!< Defines input filter time value
                                           to 64us unsynchronized.*/
    L9952DRV_IN_FILTER_80_TIMER2,  /*!< Defines input filter time value
                                            to 80us synchronized with timer 2.*/
    L9952DRV_IN_FILTER_800_TIMER2, /*!< Defines input filter time value
                                           to 800us synchronized with timer 2.*/
    L9952DRV_IN_FILTER_800_TIMER1  /*!< Defines input filter time value
                                           to 800us synchronized with timer 1.*/
} L9952drv_InputFilterModeType;


/*! Defines reset threshold level value.*/
typedef enum {
    L9952DRV_RESET_THRESHOLD_4650,    /*!< Defines reset threshold level 
                                                4,65V.*/
    L9952DRV_RESET_THRESHOLD_4350       /*!< Defines reset threshold level 
                                                4,35V.*/
} L9952drv_ResetThresholdLevelType;


/*! Defines output openload threshold level value for related outputs. */
typedef enum {
    L9952DRV_OUT_OLTHRESHOLD_2,   /*!< Defines output openload threshold 
                                            level value 2mA.*/
    L9952DRV_OUT_OLTHRESHOLD_8  /*!< Defines output openload threshold 
                                            level value 8mA.*/
} L9952drv_OutOLThresholdLevelType;


/*! Defines all possible configurations related to L9952 LIN interface. One of
them to be chosen. */
typedef enum {
    L9952DRV_LIN_SL_DI_TIM_EN_PUP_EN,   /*!< Enables master pullup LINPU and
      enables TxD dominant timeout for LIN and disables alternative LIN slope.*/
    L9952DRV_LIN_SL_DI_TIM_EN_PUP_DI,   /*!< Disables master pullup LINPU and
      enables TxD dominant timeout for LIN and disables alternative LIN slope.*/
    L9952DRV_LIN_SL_DI_TIM_DI_PUP_EN,   /*!< Enables master pullup LINPU and
      disables TxD dominant timeout for LIN and disables alternative LIN slope*/
    L9952DRV_LIN_SL_DI_TIM_DI_PUP_DI,   /*!< Disables master pullup LINPU and
      disables TxD dominant timeout for LIN and disables alternative LIN slope*/
    L9952DRV_LIN_SL_EN_TIM_EN_PUP_EN,   /*!< Enables master pullup LINPU and
      enables TxD dominant timeout for LIN and enables alternative LIN slope.*/
    L9952DRV_LIN_SL_EN_TIM_EN_PUP_DI,   /*!< Disables master pullup LINPU and
      enables TxD dominant timeout for LIN and enables alternative LIN slope.*/
    L9952DRV_LIN_SL_EN_TIM_DI_PUP_EN,   /*!< Enables master pullup LINPU and
      disables TxD dominant timeout for LIN and enables alternative LIN slope.*/
    L9952DRV_LIN_SL_EN_TIM_DI_PUP_DI    /*!< Disables master pullup LINPU and
      disables TxD dominant timeout for LIN and enables alternative LIN slope.*/
} L9952drv_LinSetupType;


/*! Defines VS lockout modes for function which controls automatic restart after
Vs over/under-voltage recovery of L9952. */
typedef enum {
    L9952DRV_VS_LOCKOUT_DISABLE,     /*!< Function disables VS lockout
                                     (i.e. enables automatic restart) after
                                      Vs over/under-voltage recovery of L9952.*/
    L9952DRV_VS_LOCKOUT_ENABLE       /*!< Function enables VS lockout
                                     (i.e. disables automatic restart) after
                                      Vs over/under-voltage recovery of L9952.*/
} L9952drv_VsLockoutModeType;


/*! Defines modes for function which controls Vs Over/Under voltage shutdown
of REL1,2 (low side drivers)  */
typedef enum {
    L9952DRV_RELAY_SHUTDOWN_ENABLE,  /*!< Function enables shutdown of relay
                                      outputs during Vs over/under-voltage
                                      of L9952 i.e. REL1,2 turned Off in case
                                      of Vs Over-/Undervoltage.*/
    L9952DRV_RELAY_SHUTDOWN_DISABLE  /*!< Function disables shutdown of relay
                                      outputs during Vs over/under-voltage
                                      of L9952 i.e. REL1,2 turned Off in case
                                      of Vs Over-/Undervoltage.*/
} L9952drv_RelayShutdownModeType;


/*! Defines modes for function which controls interrupt mode of L9952. */
typedef enum {
    L9952DRV_INT_DISABLE,            /*!< Disables interrupt mode.*/
    L9952DRV_INT_ENABLE              /*!< Enables interrupt mode.*/
} L9952drv_IntModeType;


/*! L9952drv_StatusRegType defines global data type for access to complete local
copy of L9952 Status registers 0 and 1. Access to internal structure and
particular bit variables of each status register is provided by set of mask
related to each bit variable inside the status register.*/
typedef uint32 L9952drv_StatusRegType;


/*******************************************************************************
********************************** Functions ***********************************
*******************************************************************************/



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

bool L9952drv_ReportError (uint8 ServiceId, uint8 ErrorId);


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

void L9952drv_Init (void);


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

void L9952drv_SetStandbyMode(L9952drv_StandbyModeType mode);


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

void L9952drv_SetOutMode (uint8 mask, L9952drv_OutModeType mode);


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

void L9952drv_SetOutHSAutorecovery (L9952drv_OutHSAutorecoveryType mode);



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

void L9952drv_SetRelayOutput (L9952drv_RelayOutputType value);


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

void L9952drv_SetVoltageReg2Mode (L9952drv_VoltageReg2ModeType mode);


/******************************************************************************/
/*! @fn             void L9952drv_SetTimer1(L9952drv_Timer1PeriodType period, L9952drv_Timer1ONTimeType ontime)
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

void L9952drv_SetTimer1(L9952drv_Timer1PeriodType period, L9952drv_Timer1ONTimeType ontime);


/******************************************************************************/
/*! @fn             void L9952drv_SetTimer2(L9952drv_Timer2ONTimeType ontime)
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

void L9952drv_SetTimer2(L9952drv_Timer2ONTimeType ontime);


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

void L9952drv_SetDigOutput(L9952drv_DigOutputModeType mode);


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

void L9952drv_SetWUInputMode(uint8 mask, L9952drv_WUInputModeType mode);


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

void L9952drv_DisableWakeupSource(uint8 mask, uint8 bitpattern);
    

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

void L9952drv_SetResetThresholdLevel(L9952drv_ResetThresholdLevelType level);


/******************************************************************************/
/*! @fn             void L9952drv_SetInputFilterMode(uint8 mask, L9952drv_InputFilterModeType mode)
    @param[in]      mask sets which WU input filter settings will be changed.
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

void L9952drv_SetInputFilterMode(uint8 mask, L9952drv_InputFilterModeType mode);


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

void L9952drv_SetOutOLThresholdLevel (uint8 mask, L9952drv_OutOLThresholdLevelType level);


/******************************************************************************/
/*! @fn             void L9952drv_LinSetup(L9952drv_LinSetupType value)
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

void L9952drv_LinSetup(L9952drv_LinSetupType value);


/******************************************************************************/
/*! @fn             void L9952drv_ClearStatusRegisters(void)
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
void L9952drv_ClearStatusRegisters(void);


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
void L9952drv_SetVsLockoutMode(L9952drv_VsLockoutModeType mode);


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

void L9952drv_WdgTrigger(void);


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

void L9952drv_SetRelayShutdownMode(L9952drv_RelayShutdownModeType mode);


/******************************************************************************/
/*! @fn             bool void L9952drv_GetGlobalErrorStatus(void)
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

bool L9952drv_GetGlobalErrorStatus(void);


/******************************************************************************/
/*! @fn             void L9952drv_GetStatus0(L9952drv_StatusRegType *DataPtr)  
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

void L9952drv_GetStatus0(L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn             void L9952drv_ReadStatus0(L9952drv_StatusRegType *DataPtr)
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

void L9952drv_ReadStatus0(L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn             void L9952drv_GetStatus1(L9952drv_StatusRegType *DataPtr)
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

void L9952drv_GetStatus1(L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn             void L9952drv_ReadStatus1(L9952drv_StatusRegType *DataPtr)
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

void L9952drv_ReadStatus1(L9952drv_StatusRegType *DataPtr);


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

void L9952drv_SetIntMode(L9952drv_IntModeType mode);


/*******************************************************************************
********************************************************************************
                    Functions for internal purpose only.
********************************************************************************
*******************************************************************************/


/******************************************************************************/
/*! @fn             void L9952drv_ReadControl0(L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function reads internal copy of Control register 0. 
*/
/******************************************************************************/

void L9952drv_ReadControl0(L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn             void L9952drv_ReadControl1(L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function reads internal copy of Control register 1. 
*/
/******************************************************************************/

void L9952drv_ReadControl1(L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn             void L9952drv_ReadControl2(L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function reads internal copy of Control register 2. 
*/
/******************************************************************************/

void L9952drv_ReadControl2(L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn         void L9952drv_WRControl0(const L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function replaces internal copy of Control register 0. (bits 19 and 22 and 23
are not changable)
*/
/******************************************************************************/

void L9952drv_WRControl0(const L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn         void L9952drv_WRControl1(const L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function replaces internal copy of Control register 1. (bits 22 and 23
are not changable)
*/
/******************************************************************************/

void L9952drv_WRControl1(const L9952drv_StatusRegType *DataPtr);


/******************************************************************************/
/*! @fn         void L9952drv_WRControl2(const L9952drv_StatusRegType *DataPtr)
    @brief
Function for internal purpose only.
Function replaces internal copy of Control register 2. (bits 22 and 23
are not changable)
*/
/******************************************************************************/

void L9952drv_WRControl2(const L9952drv_StatusRegType *DataPtr);


#endif
