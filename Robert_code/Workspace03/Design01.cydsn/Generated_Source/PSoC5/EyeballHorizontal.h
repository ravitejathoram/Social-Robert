/*******************************************************************************
* File Name: EyeballHorizontal.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_EyeballHorizontal_H)
#define CY_PWM_EyeballHorizontal_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 EyeballHorizontal_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define EyeballHorizontal_Resolution                     (16u)
#define EyeballHorizontal_UsingFixedFunction             (0u)
#define EyeballHorizontal_DeadBandMode                   (0u)
#define EyeballHorizontal_KillModeMinTime                (0u)
#define EyeballHorizontal_KillMode                       (0u)
#define EyeballHorizontal_PWMMode                        (1u)
#define EyeballHorizontal_PWMModeIsCenterAligned         (0u)
#define EyeballHorizontal_DeadBandUsed                   (0u)
#define EyeballHorizontal_DeadBand2_4                    (0u)

#if !defined(EyeballHorizontal_PWMUDB_genblk8_stsreg__REMOVED)
    #define EyeballHorizontal_UseStatus                  (1u)
#else
    #define EyeballHorizontal_UseStatus                  (0u)
#endif /* !defined(EyeballHorizontal_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(EyeballHorizontal_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define EyeballHorizontal_UseControl                 (1u)
#else
    #define EyeballHorizontal_UseControl                 (0u)
#endif /* !defined(EyeballHorizontal_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define EyeballHorizontal_UseOneCompareMode              (0u)
#define EyeballHorizontal_MinimumKillTime                (1u)
#define EyeballHorizontal_EnableMode                     (0u)

#define EyeballHorizontal_CompareMode1SW                 (0u)
#define EyeballHorizontal_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define EyeballHorizontal__B_PWM__DISABLED 0
#define EyeballHorizontal__B_PWM__ASYNCHRONOUS 1
#define EyeballHorizontal__B_PWM__SINGLECYCLE 2
#define EyeballHorizontal__B_PWM__LATCHED 3
#define EyeballHorizontal__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define EyeballHorizontal__B_PWM__DBMDISABLED 0
#define EyeballHorizontal__B_PWM__DBM_2_4_CLOCKS 1
#define EyeballHorizontal__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define EyeballHorizontal__B_PWM__ONE_OUTPUT 0
#define EyeballHorizontal__B_PWM__TWO_OUTPUTS 1
#define EyeballHorizontal__B_PWM__DUAL_EDGE 2
#define EyeballHorizontal__B_PWM__CENTER_ALIGN 3
#define EyeballHorizontal__B_PWM__DITHER 5
#define EyeballHorizontal__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define EyeballHorizontal__B_PWM__LESS_THAN 1
#define EyeballHorizontal__B_PWM__LESS_THAN_OR_EQUAL 2
#define EyeballHorizontal__B_PWM__GREATER_THAN 3
#define EyeballHorizontal__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define EyeballHorizontal__B_PWM__EQUAL 0
#define EyeballHorizontal__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!EyeballHorizontal_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!EyeballHorizontal_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!EyeballHorizontal_PWMModeIsCenterAligned) */
        #if (EyeballHorizontal_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (EyeballHorizontal_UseStatus) */

        /* Backup for Deadband parameters */
        #if(EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_256_CLOCKS || \
            EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(EyeballHorizontal_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (EyeballHorizontal_KillModeMinTime) */

        /* Backup control register */
        #if(EyeballHorizontal_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (EyeballHorizontal_UseControl) */

    #endif /* (!EyeballHorizontal_UsingFixedFunction) */

}EyeballHorizontal_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    EyeballHorizontal_Start(void) ;
void    EyeballHorizontal_Stop(void) ;

#if (EyeballHorizontal_UseStatus || EyeballHorizontal_UsingFixedFunction)
    void  EyeballHorizontal_SetInterruptMode(uint8 interruptMode) ;
    uint8 EyeballHorizontal_ReadStatusRegister(void) ;
#endif /* (EyeballHorizontal_UseStatus || EyeballHorizontal_UsingFixedFunction) */

#define EyeballHorizontal_GetInterruptSource() EyeballHorizontal_ReadStatusRegister()

#if (EyeballHorizontal_UseControl)
    uint8 EyeballHorizontal_ReadControlRegister(void) ;
    void  EyeballHorizontal_WriteControlRegister(uint8 control)
          ;
#endif /* (EyeballHorizontal_UseControl) */

#if (EyeballHorizontal_UseOneCompareMode)
   #if (EyeballHorizontal_CompareMode1SW)
       void    EyeballHorizontal_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (EyeballHorizontal_CompareMode1SW) */
#else
    #if (EyeballHorizontal_CompareMode1SW)
        void    EyeballHorizontal_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (EyeballHorizontal_CompareMode1SW) */
    #if (EyeballHorizontal_CompareMode2SW)
        void    EyeballHorizontal_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (EyeballHorizontal_CompareMode2SW) */
#endif /* (EyeballHorizontal_UseOneCompareMode) */

#if (!EyeballHorizontal_UsingFixedFunction)
    uint16   EyeballHorizontal_ReadCounter(void) ;
    uint16 EyeballHorizontal_ReadCapture(void) ;

    #if (EyeballHorizontal_UseStatus)
            void EyeballHorizontal_ClearFIFO(void) ;
    #endif /* (EyeballHorizontal_UseStatus) */

    void    EyeballHorizontal_WriteCounter(uint16 counter)
            ;
#endif /* (!EyeballHorizontal_UsingFixedFunction) */

void    EyeballHorizontal_WritePeriod(uint16 period)
        ;
uint16 EyeballHorizontal_ReadPeriod(void) ;

#if (EyeballHorizontal_UseOneCompareMode)
    void    EyeballHorizontal_WriteCompare(uint16 compare)
            ;
    uint16 EyeballHorizontal_ReadCompare(void) ;
#else
    void    EyeballHorizontal_WriteCompare1(uint16 compare)
            ;
    uint16 EyeballHorizontal_ReadCompare1(void) ;
    void    EyeballHorizontal_WriteCompare2(uint16 compare)
            ;
    uint16 EyeballHorizontal_ReadCompare2(void) ;
#endif /* (EyeballHorizontal_UseOneCompareMode) */


#if (EyeballHorizontal_DeadBandUsed)
    void    EyeballHorizontal_WriteDeadTime(uint8 deadtime) ;
    uint8   EyeballHorizontal_ReadDeadTime(void) ;
#endif /* (EyeballHorizontal_DeadBandUsed) */

#if ( EyeballHorizontal_KillModeMinTime)
    void EyeballHorizontal_WriteKillTime(uint8 killtime) ;
    uint8 EyeballHorizontal_ReadKillTime(void) ;
#endif /* ( EyeballHorizontal_KillModeMinTime) */

void EyeballHorizontal_Init(void) ;
void EyeballHorizontal_Enable(void) ;
void EyeballHorizontal_Sleep(void) ;
void EyeballHorizontal_Wakeup(void) ;
void EyeballHorizontal_SaveConfig(void) ;
void EyeballHorizontal_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define EyeballHorizontal_INIT_PERIOD_VALUE          (60000u)
#define EyeballHorizontal_INIT_COMPARE_VALUE1        (0u)
#define EyeballHorizontal_INIT_COMPARE_VALUE2        (0u)
#define EyeballHorizontal_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    EyeballHorizontal_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeballHorizontal_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeballHorizontal_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeballHorizontal_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define EyeballHorizontal_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  EyeballHorizontal_CTRL_CMPMODE2_SHIFT)
#define EyeballHorizontal_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  EyeballHorizontal_CTRL_CMPMODE1_SHIFT)
#define EyeballHorizontal_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (EyeballHorizontal_UsingFixedFunction)
   #define EyeballHorizontal_PERIOD_LSB              (*(reg16 *) EyeballHorizontal_PWMHW__PER0)
   #define EyeballHorizontal_PERIOD_LSB_PTR          ( (reg16 *) EyeballHorizontal_PWMHW__PER0)
   #define EyeballHorizontal_COMPARE1_LSB            (*(reg16 *) EyeballHorizontal_PWMHW__CNT_CMP0)
   #define EyeballHorizontal_COMPARE1_LSB_PTR        ( (reg16 *) EyeballHorizontal_PWMHW__CNT_CMP0)
   #define EyeballHorizontal_COMPARE2_LSB            (0x00u)
   #define EyeballHorizontal_COMPARE2_LSB_PTR        (0x00u)
   #define EyeballHorizontal_COUNTER_LSB             (*(reg16 *) EyeballHorizontal_PWMHW__CNT_CMP0)
   #define EyeballHorizontal_COUNTER_LSB_PTR         ( (reg16 *) EyeballHorizontal_PWMHW__CNT_CMP0)
   #define EyeballHorizontal_CAPTURE_LSB             (*(reg16 *) EyeballHorizontal_PWMHW__CAP0)
   #define EyeballHorizontal_CAPTURE_LSB_PTR         ( (reg16 *) EyeballHorizontal_PWMHW__CAP0)
   #define EyeballHorizontal_RT1                     (*(reg8 *)  EyeballHorizontal_PWMHW__RT1)
   #define EyeballHorizontal_RT1_PTR                 ( (reg8 *)  EyeballHorizontal_PWMHW__RT1)

#else
   #if (EyeballHorizontal_Resolution == 8u) /* 8bit - PWM */

       #if(EyeballHorizontal_PWMModeIsCenterAligned)
           #define EyeballHorizontal_PERIOD_LSB      (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define EyeballHorizontal_PERIOD_LSB_PTR  ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define EyeballHorizontal_PERIOD_LSB      (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define EyeballHorizontal_PERIOD_LSB_PTR  ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (EyeballHorizontal_PWMModeIsCenterAligned) */

       #define EyeballHorizontal_COMPARE1_LSB        (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeballHorizontal_COMPARE1_LSB_PTR    ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeballHorizontal_COMPARE2_LSB        (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeballHorizontal_COMPARE2_LSB_PTR    ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeballHorizontal_COUNTERCAP_LSB      (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeballHorizontal_COUNTERCAP_LSB_PTR  ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeballHorizontal_COUNTER_LSB         (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeballHorizontal_COUNTER_LSB_PTR     ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeballHorizontal_CAPTURE_LSB         (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define EyeballHorizontal_CAPTURE_LSB_PTR     ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(EyeballHorizontal_PWMModeIsCenterAligned)
               #define EyeballHorizontal_PERIOD_LSB      (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define EyeballHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define EyeballHorizontal_PERIOD_LSB      (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define EyeballHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (EyeballHorizontal_PWMModeIsCenterAligned) */

            #define EyeballHorizontal_COMPARE1_LSB       (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeballHorizontal_COMPARE1_LSB_PTR   ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeballHorizontal_COMPARE2_LSB       (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeballHorizontal_COMPARE2_LSB_PTR   ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeballHorizontal_COUNTERCAP_LSB     (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeballHorizontal_COUNTERCAP_LSB_PTR ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeballHorizontal_COUNTER_LSB        (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeballHorizontal_COUNTER_LSB_PTR    ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeballHorizontal_CAPTURE_LSB        (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define EyeballHorizontal_CAPTURE_LSB_PTR    ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(EyeballHorizontal_PWMModeIsCenterAligned)
               #define EyeballHorizontal_PERIOD_LSB      (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define EyeballHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define EyeballHorizontal_PERIOD_LSB      (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define EyeballHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (EyeballHorizontal_PWMModeIsCenterAligned) */

            #define EyeballHorizontal_COMPARE1_LSB       (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeballHorizontal_COMPARE1_LSB_PTR   ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeballHorizontal_COMPARE2_LSB       (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeballHorizontal_COMPARE2_LSB_PTR   ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeballHorizontal_COUNTERCAP_LSB     (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeballHorizontal_COUNTERCAP_LSB_PTR ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeballHorizontal_COUNTER_LSB        (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeballHorizontal_COUNTER_LSB_PTR    ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeballHorizontal_CAPTURE_LSB        (*(reg16 *) EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define EyeballHorizontal_CAPTURE_LSB_PTR    ((reg16 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define EyeballHorizontal_AUX_CONTROLDP1          (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define EyeballHorizontal_AUX_CONTROLDP1_PTR      ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (EyeballHorizontal_Resolution == 8) */

   #define EyeballHorizontal_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define EyeballHorizontal_AUX_CONTROLDP0          (*(reg8 *)  EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define EyeballHorizontal_AUX_CONTROLDP0_PTR      ((reg8 *)   EyeballHorizontal_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (EyeballHorizontal_UsingFixedFunction) */

#if(EyeballHorizontal_KillModeMinTime )
    #define EyeballHorizontal_KILLMODEMINTIME        (*(reg8 *)  EyeballHorizontal_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define EyeballHorizontal_KILLMODEMINTIME_PTR    ((reg8 *)   EyeballHorizontal_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (EyeballHorizontal_KillModeMinTime ) */

#if(EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_256_CLOCKS)
    #define EyeballHorizontal_DEADBAND_COUNT         (*(reg8 *)  EyeballHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeballHorizontal_DEADBAND_COUNT_PTR     ((reg8 *)   EyeballHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeballHorizontal_DEADBAND_LSB_PTR       ((reg8 *)   EyeballHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define EyeballHorizontal_DEADBAND_LSB           (*(reg8 *)  EyeballHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (EyeballHorizontal_UsingFixedFunction)
        #define EyeballHorizontal_DEADBAND_COUNT         (*(reg8 *)  EyeballHorizontal_PWMHW__CFG0)
        #define EyeballHorizontal_DEADBAND_COUNT_PTR     ((reg8 *)   EyeballHorizontal_PWMHW__CFG0)
        #define EyeballHorizontal_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeballHorizontal_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define EyeballHorizontal_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define EyeballHorizontal_DEADBAND_COUNT         (*(reg8 *)  EyeballHorizontal_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeballHorizontal_DEADBAND_COUNT_PTR     ((reg8 *)   EyeballHorizontal_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeballHorizontal_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeballHorizontal_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define EyeballHorizontal_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (EyeballHorizontal_UsingFixedFunction) */
#endif /* (EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_256_CLOCKS) */



#if (EyeballHorizontal_UsingFixedFunction)
    #define EyeballHorizontal_STATUS                 (*(reg8 *) EyeballHorizontal_PWMHW__SR0)
    #define EyeballHorizontal_STATUS_PTR             ((reg8 *) EyeballHorizontal_PWMHW__SR0)
    #define EyeballHorizontal_STATUS_MASK            (*(reg8 *) EyeballHorizontal_PWMHW__SR0)
    #define EyeballHorizontal_STATUS_MASK_PTR        ((reg8 *) EyeballHorizontal_PWMHW__SR0)
    #define EyeballHorizontal_CONTROL                (*(reg8 *) EyeballHorizontal_PWMHW__CFG0)
    #define EyeballHorizontal_CONTROL_PTR            ((reg8 *) EyeballHorizontal_PWMHW__CFG0)
    #define EyeballHorizontal_CONTROL2               (*(reg8 *) EyeballHorizontal_PWMHW__CFG1)
    #define EyeballHorizontal_CONTROL3               (*(reg8 *) EyeballHorizontal_PWMHW__CFG2)
    #define EyeballHorizontal_GLOBAL_ENABLE          (*(reg8 *) EyeballHorizontal_PWMHW__PM_ACT_CFG)
    #define EyeballHorizontal_GLOBAL_ENABLE_PTR      ( (reg8 *) EyeballHorizontal_PWMHW__PM_ACT_CFG)
    #define EyeballHorizontal_GLOBAL_STBY_ENABLE     (*(reg8 *) EyeballHorizontal_PWMHW__PM_STBY_CFG)
    #define EyeballHorizontal_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) EyeballHorizontal_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define EyeballHorizontal_BLOCK_EN_MASK          (EyeballHorizontal_PWMHW__PM_ACT_MSK)
    #define EyeballHorizontal_BLOCK_STBY_EN_MASK     (EyeballHorizontal_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define EyeballHorizontal_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define EyeballHorizontal_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define EyeballHorizontal_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define EyeballHorizontal_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define EyeballHorizontal_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define EyeballHorizontal_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define EyeballHorizontal_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeballHorizontal_CTRL_ENABLE_SHIFT)
    #define EyeballHorizontal_CTRL_RESET             (uint8)((uint8)0x01u << EyeballHorizontal_CTRL_RESET_SHIFT)
    #define EyeballHorizontal_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeballHorizontal_CTRL_CMPMODE2_SHIFT)
    #define EyeballHorizontal_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeballHorizontal_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define EyeballHorizontal_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define EyeballHorizontal_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << EyeballHorizontal_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define EyeballHorizontal_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define EyeballHorizontal_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define EyeballHorizontal_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeballHorizontal_STATUS_TC_INT_EN_MASK_SHIFT            (EyeballHorizontal_STATUS_TC_SHIFT - 4u)
    #define EyeballHorizontal_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeballHorizontal_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeballHorizontal_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define EyeballHorizontal_STATUS_TC              (uint8)((uint8)0x01u << EyeballHorizontal_STATUS_TC_SHIFT)
    #define EyeballHorizontal_STATUS_CMP1            (uint8)((uint8)0x01u << EyeballHorizontal_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define EyeballHorizontal_STATUS_TC_INT_EN_MASK              (uint8)((uint8)EyeballHorizontal_STATUS_TC >> 4u)
    #define EyeballHorizontal_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)EyeballHorizontal_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define EyeballHorizontal_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define EyeballHorizontal_RT1_MASK              (uint8)((uint8)0x03u << EyeballHorizontal_RT1_SHIFT)
    #define EyeballHorizontal_SYNC                  (uint8)((uint8)0x03u << EyeballHorizontal_RT1_SHIFT)
    #define EyeballHorizontal_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define EyeballHorizontal_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << EyeballHorizontal_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define EyeballHorizontal_SYNCDSI_EN            (uint8)((uint8)0x0Fu << EyeballHorizontal_SYNCDSI_SHIFT)


#else
    #define EyeballHorizontal_STATUS                (*(reg8 *)   EyeballHorizontal_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeballHorizontal_STATUS_PTR            ((reg8 *)    EyeballHorizontal_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeballHorizontal_STATUS_MASK           (*(reg8 *)   EyeballHorizontal_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeballHorizontal_STATUS_MASK_PTR       ((reg8 *)    EyeballHorizontal_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeballHorizontal_STATUS_AUX_CTRL       (*(reg8 *)   EyeballHorizontal_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define EyeballHorizontal_CONTROL               (*(reg8 *)   EyeballHorizontal_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define EyeballHorizontal_CONTROL_PTR           ((reg8 *)    EyeballHorizontal_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define EyeballHorizontal_CTRL_ENABLE_SHIFT      (0x07u)
    #define EyeballHorizontal_CTRL_RESET_SHIFT       (0x06u)
    #define EyeballHorizontal_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define EyeballHorizontal_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define EyeballHorizontal_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define EyeballHorizontal_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeballHorizontal_CTRL_ENABLE_SHIFT)
    #define EyeballHorizontal_CTRL_RESET             (uint8)((uint8)0x01u << EyeballHorizontal_CTRL_RESET_SHIFT)
    #define EyeballHorizontal_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeballHorizontal_CTRL_CMPMODE2_SHIFT)
    #define EyeballHorizontal_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeballHorizontal_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define EyeballHorizontal_STATUS_KILL_SHIFT          (0x05u)
    #define EyeballHorizontal_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define EyeballHorizontal_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define EyeballHorizontal_STATUS_TC_SHIFT            (0x02u)
    #define EyeballHorizontal_STATUS_CMP2_SHIFT          (0x01u)
    #define EyeballHorizontal_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define EyeballHorizontal_STATUS_KILL_INT_EN_MASK_SHIFT          (EyeballHorizontal_STATUS_KILL_SHIFT)
    #define EyeballHorizontal_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (EyeballHorizontal_STATUS_FIFONEMPTY_SHIFT)
    #define EyeballHorizontal_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (EyeballHorizontal_STATUS_FIFOFULL_SHIFT)
    #define EyeballHorizontal_STATUS_TC_INT_EN_MASK_SHIFT            (EyeballHorizontal_STATUS_TC_SHIFT)
    #define EyeballHorizontal_STATUS_CMP2_INT_EN_MASK_SHIFT          (EyeballHorizontal_STATUS_CMP2_SHIFT)
    #define EyeballHorizontal_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeballHorizontal_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define EyeballHorizontal_STATUS_KILL            (uint8)((uint8)0x00u << EyeballHorizontal_STATUS_KILL_SHIFT )
    #define EyeballHorizontal_STATUS_FIFOFULL        (uint8)((uint8)0x01u << EyeballHorizontal_STATUS_FIFOFULL_SHIFT)
    #define EyeballHorizontal_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << EyeballHorizontal_STATUS_FIFONEMPTY_SHIFT)
    #define EyeballHorizontal_STATUS_TC              (uint8)((uint8)0x01u << EyeballHorizontal_STATUS_TC_SHIFT)
    #define EyeballHorizontal_STATUS_CMP2            (uint8)((uint8)0x01u << EyeballHorizontal_STATUS_CMP2_SHIFT)
    #define EyeballHorizontal_STATUS_CMP1            (uint8)((uint8)0x01u << EyeballHorizontal_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define EyeballHorizontal_STATUS_KILL_INT_EN_MASK            (EyeballHorizontal_STATUS_KILL)
    #define EyeballHorizontal_STATUS_FIFOFULL_INT_EN_MASK        (EyeballHorizontal_STATUS_FIFOFULL)
    #define EyeballHorizontal_STATUS_FIFONEMPTY_INT_EN_MASK      (EyeballHorizontal_STATUS_FIFONEMPTY)
    #define EyeballHorizontal_STATUS_TC_INT_EN_MASK              (EyeballHorizontal_STATUS_TC)
    #define EyeballHorizontal_STATUS_CMP2_INT_EN_MASK            (EyeballHorizontal_STATUS_CMP2)
    #define EyeballHorizontal_STATUS_CMP1_INT_EN_MASK            (EyeballHorizontal_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define EyeballHorizontal_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define EyeballHorizontal_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define EyeballHorizontal_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define EyeballHorizontal_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define EyeballHorizontal_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* EyeballHorizontal_UsingFixedFunction */

#endif  /* CY_PWM_EyeballHorizontal_H */


/* [] END OF FILE */
