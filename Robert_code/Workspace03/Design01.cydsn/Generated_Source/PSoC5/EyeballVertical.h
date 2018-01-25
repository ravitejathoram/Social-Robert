/*******************************************************************************
* File Name: EyeballVertical.h
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

#if !defined(CY_PWM_EyeballVertical_H)
#define CY_PWM_EyeballVertical_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 EyeballVertical_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define EyeballVertical_Resolution                     (16u)
#define EyeballVertical_UsingFixedFunction             (0u)
#define EyeballVertical_DeadBandMode                   (0u)
#define EyeballVertical_KillModeMinTime                (0u)
#define EyeballVertical_KillMode                       (0u)
#define EyeballVertical_PWMMode                        (1u)
#define EyeballVertical_PWMModeIsCenterAligned         (0u)
#define EyeballVertical_DeadBandUsed                   (0u)
#define EyeballVertical_DeadBand2_4                    (0u)

#if !defined(EyeballVertical_PWMUDB_genblk8_stsreg__REMOVED)
    #define EyeballVertical_UseStatus                  (1u)
#else
    #define EyeballVertical_UseStatus                  (0u)
#endif /* !defined(EyeballVertical_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(EyeballVertical_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define EyeballVertical_UseControl                 (1u)
#else
    #define EyeballVertical_UseControl                 (0u)
#endif /* !defined(EyeballVertical_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define EyeballVertical_UseOneCompareMode              (0u)
#define EyeballVertical_MinimumKillTime                (1u)
#define EyeballVertical_EnableMode                     (0u)

#define EyeballVertical_CompareMode1SW                 (0u)
#define EyeballVertical_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define EyeballVertical__B_PWM__DISABLED 0
#define EyeballVertical__B_PWM__ASYNCHRONOUS 1
#define EyeballVertical__B_PWM__SINGLECYCLE 2
#define EyeballVertical__B_PWM__LATCHED 3
#define EyeballVertical__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define EyeballVertical__B_PWM__DBMDISABLED 0
#define EyeballVertical__B_PWM__DBM_2_4_CLOCKS 1
#define EyeballVertical__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define EyeballVertical__B_PWM__ONE_OUTPUT 0
#define EyeballVertical__B_PWM__TWO_OUTPUTS 1
#define EyeballVertical__B_PWM__DUAL_EDGE 2
#define EyeballVertical__B_PWM__CENTER_ALIGN 3
#define EyeballVertical__B_PWM__DITHER 5
#define EyeballVertical__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define EyeballVertical__B_PWM__LESS_THAN 1
#define EyeballVertical__B_PWM__LESS_THAN_OR_EQUAL 2
#define EyeballVertical__B_PWM__GREATER_THAN 3
#define EyeballVertical__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define EyeballVertical__B_PWM__EQUAL 0
#define EyeballVertical__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!EyeballVertical_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!EyeballVertical_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!EyeballVertical_PWMModeIsCenterAligned) */
        #if (EyeballVertical_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (EyeballVertical_UseStatus) */

        /* Backup for Deadband parameters */
        #if(EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_256_CLOCKS || \
            EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(EyeballVertical_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (EyeballVertical_KillModeMinTime) */

        /* Backup control register */
        #if(EyeballVertical_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (EyeballVertical_UseControl) */

    #endif /* (!EyeballVertical_UsingFixedFunction) */

}EyeballVertical_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    EyeballVertical_Start(void) ;
void    EyeballVertical_Stop(void) ;

#if (EyeballVertical_UseStatus || EyeballVertical_UsingFixedFunction)
    void  EyeballVertical_SetInterruptMode(uint8 interruptMode) ;
    uint8 EyeballVertical_ReadStatusRegister(void) ;
#endif /* (EyeballVertical_UseStatus || EyeballVertical_UsingFixedFunction) */

#define EyeballVertical_GetInterruptSource() EyeballVertical_ReadStatusRegister()

#if (EyeballVertical_UseControl)
    uint8 EyeballVertical_ReadControlRegister(void) ;
    void  EyeballVertical_WriteControlRegister(uint8 control)
          ;
#endif /* (EyeballVertical_UseControl) */

#if (EyeballVertical_UseOneCompareMode)
   #if (EyeballVertical_CompareMode1SW)
       void    EyeballVertical_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (EyeballVertical_CompareMode1SW) */
#else
    #if (EyeballVertical_CompareMode1SW)
        void    EyeballVertical_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (EyeballVertical_CompareMode1SW) */
    #if (EyeballVertical_CompareMode2SW)
        void    EyeballVertical_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (EyeballVertical_CompareMode2SW) */
#endif /* (EyeballVertical_UseOneCompareMode) */

#if (!EyeballVertical_UsingFixedFunction)
    uint16   EyeballVertical_ReadCounter(void) ;
    uint16 EyeballVertical_ReadCapture(void) ;

    #if (EyeballVertical_UseStatus)
            void EyeballVertical_ClearFIFO(void) ;
    #endif /* (EyeballVertical_UseStatus) */

    void    EyeballVertical_WriteCounter(uint16 counter)
            ;
#endif /* (!EyeballVertical_UsingFixedFunction) */

void    EyeballVertical_WritePeriod(uint16 period)
        ;
uint16 EyeballVertical_ReadPeriod(void) ;

#if (EyeballVertical_UseOneCompareMode)
    void    EyeballVertical_WriteCompare(uint16 compare)
            ;
    uint16 EyeballVertical_ReadCompare(void) ;
#else
    void    EyeballVertical_WriteCompare1(uint16 compare)
            ;
    uint16 EyeballVertical_ReadCompare1(void) ;
    void    EyeballVertical_WriteCompare2(uint16 compare)
            ;
    uint16 EyeballVertical_ReadCompare2(void) ;
#endif /* (EyeballVertical_UseOneCompareMode) */


#if (EyeballVertical_DeadBandUsed)
    void    EyeballVertical_WriteDeadTime(uint8 deadtime) ;
    uint8   EyeballVertical_ReadDeadTime(void) ;
#endif /* (EyeballVertical_DeadBandUsed) */

#if ( EyeballVertical_KillModeMinTime)
    void EyeballVertical_WriteKillTime(uint8 killtime) ;
    uint8 EyeballVertical_ReadKillTime(void) ;
#endif /* ( EyeballVertical_KillModeMinTime) */

void EyeballVertical_Init(void) ;
void EyeballVertical_Enable(void) ;
void EyeballVertical_Sleep(void) ;
void EyeballVertical_Wakeup(void) ;
void EyeballVertical_SaveConfig(void) ;
void EyeballVertical_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define EyeballVertical_INIT_PERIOD_VALUE          (60000u)
#define EyeballVertical_INIT_COMPARE_VALUE1        (0u)
#define EyeballVertical_INIT_COMPARE_VALUE2        (0u)
#define EyeballVertical_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    EyeballVertical_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeballVertical_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeballVertical_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeballVertical_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define EyeballVertical_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  EyeballVertical_CTRL_CMPMODE2_SHIFT)
#define EyeballVertical_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  EyeballVertical_CTRL_CMPMODE1_SHIFT)
#define EyeballVertical_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (EyeballVertical_UsingFixedFunction)
   #define EyeballVertical_PERIOD_LSB              (*(reg16 *) EyeballVertical_PWMHW__PER0)
   #define EyeballVertical_PERIOD_LSB_PTR          ( (reg16 *) EyeballVertical_PWMHW__PER0)
   #define EyeballVertical_COMPARE1_LSB            (*(reg16 *) EyeballVertical_PWMHW__CNT_CMP0)
   #define EyeballVertical_COMPARE1_LSB_PTR        ( (reg16 *) EyeballVertical_PWMHW__CNT_CMP0)
   #define EyeballVertical_COMPARE2_LSB            (0x00u)
   #define EyeballVertical_COMPARE2_LSB_PTR        (0x00u)
   #define EyeballVertical_COUNTER_LSB             (*(reg16 *) EyeballVertical_PWMHW__CNT_CMP0)
   #define EyeballVertical_COUNTER_LSB_PTR         ( (reg16 *) EyeballVertical_PWMHW__CNT_CMP0)
   #define EyeballVertical_CAPTURE_LSB             (*(reg16 *) EyeballVertical_PWMHW__CAP0)
   #define EyeballVertical_CAPTURE_LSB_PTR         ( (reg16 *) EyeballVertical_PWMHW__CAP0)
   #define EyeballVertical_RT1                     (*(reg8 *)  EyeballVertical_PWMHW__RT1)
   #define EyeballVertical_RT1_PTR                 ( (reg8 *)  EyeballVertical_PWMHW__RT1)

#else
   #if (EyeballVertical_Resolution == 8u) /* 8bit - PWM */

       #if(EyeballVertical_PWMModeIsCenterAligned)
           #define EyeballVertical_PERIOD_LSB      (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define EyeballVertical_PERIOD_LSB_PTR  ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define EyeballVertical_PERIOD_LSB      (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define EyeballVertical_PERIOD_LSB_PTR  ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (EyeballVertical_PWMModeIsCenterAligned) */

       #define EyeballVertical_COMPARE1_LSB        (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeballVertical_COMPARE1_LSB_PTR    ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeballVertical_COMPARE2_LSB        (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeballVertical_COMPARE2_LSB_PTR    ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeballVertical_COUNTERCAP_LSB      (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeballVertical_COUNTERCAP_LSB_PTR  ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeballVertical_COUNTER_LSB         (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeballVertical_COUNTER_LSB_PTR     ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeballVertical_CAPTURE_LSB         (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define EyeballVertical_CAPTURE_LSB_PTR     ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(EyeballVertical_PWMModeIsCenterAligned)
               #define EyeballVertical_PERIOD_LSB      (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define EyeballVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define EyeballVertical_PERIOD_LSB      (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define EyeballVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (EyeballVertical_PWMModeIsCenterAligned) */

            #define EyeballVertical_COMPARE1_LSB       (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeballVertical_COMPARE1_LSB_PTR   ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeballVertical_COMPARE2_LSB       (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeballVertical_COMPARE2_LSB_PTR   ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeballVertical_COUNTERCAP_LSB     (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeballVertical_COUNTERCAP_LSB_PTR ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeballVertical_COUNTER_LSB        (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeballVertical_COUNTER_LSB_PTR    ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeballVertical_CAPTURE_LSB        (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define EyeballVertical_CAPTURE_LSB_PTR    ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(EyeballVertical_PWMModeIsCenterAligned)
               #define EyeballVertical_PERIOD_LSB      (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define EyeballVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define EyeballVertical_PERIOD_LSB      (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define EyeballVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (EyeballVertical_PWMModeIsCenterAligned) */

            #define EyeballVertical_COMPARE1_LSB       (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeballVertical_COMPARE1_LSB_PTR   ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeballVertical_COMPARE2_LSB       (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeballVertical_COMPARE2_LSB_PTR   ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeballVertical_COUNTERCAP_LSB     (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeballVertical_COUNTERCAP_LSB_PTR ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeballVertical_COUNTER_LSB        (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeballVertical_COUNTER_LSB_PTR    ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeballVertical_CAPTURE_LSB        (*(reg16 *) EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define EyeballVertical_CAPTURE_LSB_PTR    ((reg16 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define EyeballVertical_AUX_CONTROLDP1          (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define EyeballVertical_AUX_CONTROLDP1_PTR      ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (EyeballVertical_Resolution == 8) */

   #define EyeballVertical_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define EyeballVertical_AUX_CONTROLDP0          (*(reg8 *)  EyeballVertical_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define EyeballVertical_AUX_CONTROLDP0_PTR      ((reg8 *)   EyeballVertical_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (EyeballVertical_UsingFixedFunction) */

#if(EyeballVertical_KillModeMinTime )
    #define EyeballVertical_KILLMODEMINTIME        (*(reg8 *)  EyeballVertical_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define EyeballVertical_KILLMODEMINTIME_PTR    ((reg8 *)   EyeballVertical_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (EyeballVertical_KillModeMinTime ) */

#if(EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_256_CLOCKS)
    #define EyeballVertical_DEADBAND_COUNT         (*(reg8 *)  EyeballVertical_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeballVertical_DEADBAND_COUNT_PTR     ((reg8 *)   EyeballVertical_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeballVertical_DEADBAND_LSB_PTR       ((reg8 *)   EyeballVertical_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define EyeballVertical_DEADBAND_LSB           (*(reg8 *)  EyeballVertical_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (EyeballVertical_UsingFixedFunction)
        #define EyeballVertical_DEADBAND_COUNT         (*(reg8 *)  EyeballVertical_PWMHW__CFG0)
        #define EyeballVertical_DEADBAND_COUNT_PTR     ((reg8 *)   EyeballVertical_PWMHW__CFG0)
        #define EyeballVertical_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeballVertical_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define EyeballVertical_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define EyeballVertical_DEADBAND_COUNT         (*(reg8 *)  EyeballVertical_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeballVertical_DEADBAND_COUNT_PTR     ((reg8 *)   EyeballVertical_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeballVertical_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeballVertical_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define EyeballVertical_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (EyeballVertical_UsingFixedFunction) */
#endif /* (EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_256_CLOCKS) */



#if (EyeballVertical_UsingFixedFunction)
    #define EyeballVertical_STATUS                 (*(reg8 *) EyeballVertical_PWMHW__SR0)
    #define EyeballVertical_STATUS_PTR             ((reg8 *) EyeballVertical_PWMHW__SR0)
    #define EyeballVertical_STATUS_MASK            (*(reg8 *) EyeballVertical_PWMHW__SR0)
    #define EyeballVertical_STATUS_MASK_PTR        ((reg8 *) EyeballVertical_PWMHW__SR0)
    #define EyeballVertical_CONTROL                (*(reg8 *) EyeballVertical_PWMHW__CFG0)
    #define EyeballVertical_CONTROL_PTR            ((reg8 *) EyeballVertical_PWMHW__CFG0)
    #define EyeballVertical_CONTROL2               (*(reg8 *) EyeballVertical_PWMHW__CFG1)
    #define EyeballVertical_CONTROL3               (*(reg8 *) EyeballVertical_PWMHW__CFG2)
    #define EyeballVertical_GLOBAL_ENABLE          (*(reg8 *) EyeballVertical_PWMHW__PM_ACT_CFG)
    #define EyeballVertical_GLOBAL_ENABLE_PTR      ( (reg8 *) EyeballVertical_PWMHW__PM_ACT_CFG)
    #define EyeballVertical_GLOBAL_STBY_ENABLE     (*(reg8 *) EyeballVertical_PWMHW__PM_STBY_CFG)
    #define EyeballVertical_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) EyeballVertical_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define EyeballVertical_BLOCK_EN_MASK          (EyeballVertical_PWMHW__PM_ACT_MSK)
    #define EyeballVertical_BLOCK_STBY_EN_MASK     (EyeballVertical_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define EyeballVertical_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define EyeballVertical_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define EyeballVertical_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define EyeballVertical_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define EyeballVertical_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define EyeballVertical_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define EyeballVertical_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeballVertical_CTRL_ENABLE_SHIFT)
    #define EyeballVertical_CTRL_RESET             (uint8)((uint8)0x01u << EyeballVertical_CTRL_RESET_SHIFT)
    #define EyeballVertical_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeballVertical_CTRL_CMPMODE2_SHIFT)
    #define EyeballVertical_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeballVertical_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define EyeballVertical_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define EyeballVertical_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << EyeballVertical_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define EyeballVertical_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define EyeballVertical_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define EyeballVertical_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeballVertical_STATUS_TC_INT_EN_MASK_SHIFT            (EyeballVertical_STATUS_TC_SHIFT - 4u)
    #define EyeballVertical_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeballVertical_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeballVertical_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define EyeballVertical_STATUS_TC              (uint8)((uint8)0x01u << EyeballVertical_STATUS_TC_SHIFT)
    #define EyeballVertical_STATUS_CMP1            (uint8)((uint8)0x01u << EyeballVertical_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define EyeballVertical_STATUS_TC_INT_EN_MASK              (uint8)((uint8)EyeballVertical_STATUS_TC >> 4u)
    #define EyeballVertical_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)EyeballVertical_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define EyeballVertical_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define EyeballVertical_RT1_MASK              (uint8)((uint8)0x03u << EyeballVertical_RT1_SHIFT)
    #define EyeballVertical_SYNC                  (uint8)((uint8)0x03u << EyeballVertical_RT1_SHIFT)
    #define EyeballVertical_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define EyeballVertical_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << EyeballVertical_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define EyeballVertical_SYNCDSI_EN            (uint8)((uint8)0x0Fu << EyeballVertical_SYNCDSI_SHIFT)


#else
    #define EyeballVertical_STATUS                (*(reg8 *)   EyeballVertical_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeballVertical_STATUS_PTR            ((reg8 *)    EyeballVertical_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeballVertical_STATUS_MASK           (*(reg8 *)   EyeballVertical_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeballVertical_STATUS_MASK_PTR       ((reg8 *)    EyeballVertical_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeballVertical_STATUS_AUX_CTRL       (*(reg8 *)   EyeballVertical_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define EyeballVertical_CONTROL               (*(reg8 *)   EyeballVertical_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define EyeballVertical_CONTROL_PTR           ((reg8 *)    EyeballVertical_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define EyeballVertical_CTRL_ENABLE_SHIFT      (0x07u)
    #define EyeballVertical_CTRL_RESET_SHIFT       (0x06u)
    #define EyeballVertical_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define EyeballVertical_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define EyeballVertical_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define EyeballVertical_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeballVertical_CTRL_ENABLE_SHIFT)
    #define EyeballVertical_CTRL_RESET             (uint8)((uint8)0x01u << EyeballVertical_CTRL_RESET_SHIFT)
    #define EyeballVertical_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeballVertical_CTRL_CMPMODE2_SHIFT)
    #define EyeballVertical_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeballVertical_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define EyeballVertical_STATUS_KILL_SHIFT          (0x05u)
    #define EyeballVertical_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define EyeballVertical_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define EyeballVertical_STATUS_TC_SHIFT            (0x02u)
    #define EyeballVertical_STATUS_CMP2_SHIFT          (0x01u)
    #define EyeballVertical_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define EyeballVertical_STATUS_KILL_INT_EN_MASK_SHIFT          (EyeballVertical_STATUS_KILL_SHIFT)
    #define EyeballVertical_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (EyeballVertical_STATUS_FIFONEMPTY_SHIFT)
    #define EyeballVertical_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (EyeballVertical_STATUS_FIFOFULL_SHIFT)
    #define EyeballVertical_STATUS_TC_INT_EN_MASK_SHIFT            (EyeballVertical_STATUS_TC_SHIFT)
    #define EyeballVertical_STATUS_CMP2_INT_EN_MASK_SHIFT          (EyeballVertical_STATUS_CMP2_SHIFT)
    #define EyeballVertical_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeballVertical_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define EyeballVertical_STATUS_KILL            (uint8)((uint8)0x00u << EyeballVertical_STATUS_KILL_SHIFT )
    #define EyeballVertical_STATUS_FIFOFULL        (uint8)((uint8)0x01u << EyeballVertical_STATUS_FIFOFULL_SHIFT)
    #define EyeballVertical_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << EyeballVertical_STATUS_FIFONEMPTY_SHIFT)
    #define EyeballVertical_STATUS_TC              (uint8)((uint8)0x01u << EyeballVertical_STATUS_TC_SHIFT)
    #define EyeballVertical_STATUS_CMP2            (uint8)((uint8)0x01u << EyeballVertical_STATUS_CMP2_SHIFT)
    #define EyeballVertical_STATUS_CMP1            (uint8)((uint8)0x01u << EyeballVertical_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define EyeballVertical_STATUS_KILL_INT_EN_MASK            (EyeballVertical_STATUS_KILL)
    #define EyeballVertical_STATUS_FIFOFULL_INT_EN_MASK        (EyeballVertical_STATUS_FIFOFULL)
    #define EyeballVertical_STATUS_FIFONEMPTY_INT_EN_MASK      (EyeballVertical_STATUS_FIFONEMPTY)
    #define EyeballVertical_STATUS_TC_INT_EN_MASK              (EyeballVertical_STATUS_TC)
    #define EyeballVertical_STATUS_CMP2_INT_EN_MASK            (EyeballVertical_STATUS_CMP2)
    #define EyeballVertical_STATUS_CMP1_INT_EN_MASK            (EyeballVertical_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define EyeballVertical_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define EyeballVertical_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define EyeballVertical_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define EyeballVertical_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define EyeballVertical_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* EyeballVertical_UsingFixedFunction */

#endif  /* CY_PWM_EyeballVertical_H */


/* [] END OF FILE */
