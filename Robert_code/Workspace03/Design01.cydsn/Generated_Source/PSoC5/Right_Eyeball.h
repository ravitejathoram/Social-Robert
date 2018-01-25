/*******************************************************************************
* File Name: Right_Eyeball.h
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

#if !defined(CY_PWM_Right_Eyeball_H)
#define CY_PWM_Right_Eyeball_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Right_Eyeball_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Right_Eyeball_Resolution                     (16u)
#define Right_Eyeball_UsingFixedFunction             (0u)
#define Right_Eyeball_DeadBandMode                   (0u)
#define Right_Eyeball_KillModeMinTime                (0u)
#define Right_Eyeball_KillMode                       (0u)
#define Right_Eyeball_PWMMode                        (1u)
#define Right_Eyeball_PWMModeIsCenterAligned         (0u)
#define Right_Eyeball_DeadBandUsed                   (0u)
#define Right_Eyeball_DeadBand2_4                    (0u)

#if !defined(Right_Eyeball_PWMUDB_genblk8_stsreg__REMOVED)
    #define Right_Eyeball_UseStatus                  (1u)
#else
    #define Right_Eyeball_UseStatus                  (0u)
#endif /* !defined(Right_Eyeball_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Right_Eyeball_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Right_Eyeball_UseControl                 (1u)
#else
    #define Right_Eyeball_UseControl                 (0u)
#endif /* !defined(Right_Eyeball_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Right_Eyeball_UseOneCompareMode              (0u)
#define Right_Eyeball_MinimumKillTime                (1u)
#define Right_Eyeball_EnableMode                     (0u)

#define Right_Eyeball_CompareMode1SW                 (0u)
#define Right_Eyeball_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Right_Eyeball__B_PWM__DISABLED 0
#define Right_Eyeball__B_PWM__ASYNCHRONOUS 1
#define Right_Eyeball__B_PWM__SINGLECYCLE 2
#define Right_Eyeball__B_PWM__LATCHED 3
#define Right_Eyeball__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Right_Eyeball__B_PWM__DBMDISABLED 0
#define Right_Eyeball__B_PWM__DBM_2_4_CLOCKS 1
#define Right_Eyeball__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Right_Eyeball__B_PWM__ONE_OUTPUT 0
#define Right_Eyeball__B_PWM__TWO_OUTPUTS 1
#define Right_Eyeball__B_PWM__DUAL_EDGE 2
#define Right_Eyeball__B_PWM__CENTER_ALIGN 3
#define Right_Eyeball__B_PWM__DITHER 5
#define Right_Eyeball__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Right_Eyeball__B_PWM__LESS_THAN 1
#define Right_Eyeball__B_PWM__LESS_THAN_OR_EQUAL 2
#define Right_Eyeball__B_PWM__GREATER_THAN 3
#define Right_Eyeball__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Right_Eyeball__B_PWM__EQUAL 0
#define Right_Eyeball__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Right_Eyeball_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Right_Eyeball_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Right_Eyeball_PWMModeIsCenterAligned) */
        #if (Right_Eyeball_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Right_Eyeball_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_256_CLOCKS || \
            Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Right_Eyeball_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Right_Eyeball_KillModeMinTime) */

        /* Backup control register */
        #if(Right_Eyeball_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Right_Eyeball_UseControl) */

    #endif /* (!Right_Eyeball_UsingFixedFunction) */

}Right_Eyeball_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Right_Eyeball_Start(void) ;
void    Right_Eyeball_Stop(void) ;

#if (Right_Eyeball_UseStatus || Right_Eyeball_UsingFixedFunction)
    void  Right_Eyeball_SetInterruptMode(uint8 interruptMode) ;
    uint8 Right_Eyeball_ReadStatusRegister(void) ;
#endif /* (Right_Eyeball_UseStatus || Right_Eyeball_UsingFixedFunction) */

#define Right_Eyeball_GetInterruptSource() Right_Eyeball_ReadStatusRegister()

#if (Right_Eyeball_UseControl)
    uint8 Right_Eyeball_ReadControlRegister(void) ;
    void  Right_Eyeball_WriteControlRegister(uint8 control)
          ;
#endif /* (Right_Eyeball_UseControl) */

#if (Right_Eyeball_UseOneCompareMode)
   #if (Right_Eyeball_CompareMode1SW)
       void    Right_Eyeball_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Right_Eyeball_CompareMode1SW) */
#else
    #if (Right_Eyeball_CompareMode1SW)
        void    Right_Eyeball_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Right_Eyeball_CompareMode1SW) */
    #if (Right_Eyeball_CompareMode2SW)
        void    Right_Eyeball_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Right_Eyeball_CompareMode2SW) */
#endif /* (Right_Eyeball_UseOneCompareMode) */

#if (!Right_Eyeball_UsingFixedFunction)
    uint16   Right_Eyeball_ReadCounter(void) ;
    uint16 Right_Eyeball_ReadCapture(void) ;

    #if (Right_Eyeball_UseStatus)
            void Right_Eyeball_ClearFIFO(void) ;
    #endif /* (Right_Eyeball_UseStatus) */

    void    Right_Eyeball_WriteCounter(uint16 counter)
            ;
#endif /* (!Right_Eyeball_UsingFixedFunction) */

void    Right_Eyeball_WritePeriod(uint16 period)
        ;
uint16 Right_Eyeball_ReadPeriod(void) ;

#if (Right_Eyeball_UseOneCompareMode)
    void    Right_Eyeball_WriteCompare(uint16 compare)
            ;
    uint16 Right_Eyeball_ReadCompare(void) ;
#else
    void    Right_Eyeball_WriteCompare1(uint16 compare)
            ;
    uint16 Right_Eyeball_ReadCompare1(void) ;
    void    Right_Eyeball_WriteCompare2(uint16 compare)
            ;
    uint16 Right_Eyeball_ReadCompare2(void) ;
#endif /* (Right_Eyeball_UseOneCompareMode) */


#if (Right_Eyeball_DeadBandUsed)
    void    Right_Eyeball_WriteDeadTime(uint8 deadtime) ;
    uint8   Right_Eyeball_ReadDeadTime(void) ;
#endif /* (Right_Eyeball_DeadBandUsed) */

#if ( Right_Eyeball_KillModeMinTime)
    void Right_Eyeball_WriteKillTime(uint8 killtime) ;
    uint8 Right_Eyeball_ReadKillTime(void) ;
#endif /* ( Right_Eyeball_KillModeMinTime) */

void Right_Eyeball_Init(void) ;
void Right_Eyeball_Enable(void) ;
void Right_Eyeball_Sleep(void) ;
void Right_Eyeball_Wakeup(void) ;
void Right_Eyeball_SaveConfig(void) ;
void Right_Eyeball_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Right_Eyeball_INIT_PERIOD_VALUE          (60000u)
#define Right_Eyeball_INIT_COMPARE_VALUE1        (0u)
#define Right_Eyeball_INIT_COMPARE_VALUE2        (0u)
#define Right_Eyeball_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Right_Eyeball_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Right_Eyeball_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Right_Eyeball_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Right_Eyeball_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Right_Eyeball_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Right_Eyeball_CTRL_CMPMODE2_SHIFT)
#define Right_Eyeball_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Right_Eyeball_CTRL_CMPMODE1_SHIFT)
#define Right_Eyeball_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Right_Eyeball_UsingFixedFunction)
   #define Right_Eyeball_PERIOD_LSB              (*(reg16 *) Right_Eyeball_PWMHW__PER0)
   #define Right_Eyeball_PERIOD_LSB_PTR          ( (reg16 *) Right_Eyeball_PWMHW__PER0)
   #define Right_Eyeball_COMPARE1_LSB            (*(reg16 *) Right_Eyeball_PWMHW__CNT_CMP0)
   #define Right_Eyeball_COMPARE1_LSB_PTR        ( (reg16 *) Right_Eyeball_PWMHW__CNT_CMP0)
   #define Right_Eyeball_COMPARE2_LSB            (0x00u)
   #define Right_Eyeball_COMPARE2_LSB_PTR        (0x00u)
   #define Right_Eyeball_COUNTER_LSB             (*(reg16 *) Right_Eyeball_PWMHW__CNT_CMP0)
   #define Right_Eyeball_COUNTER_LSB_PTR         ( (reg16 *) Right_Eyeball_PWMHW__CNT_CMP0)
   #define Right_Eyeball_CAPTURE_LSB             (*(reg16 *) Right_Eyeball_PWMHW__CAP0)
   #define Right_Eyeball_CAPTURE_LSB_PTR         ( (reg16 *) Right_Eyeball_PWMHW__CAP0)
   #define Right_Eyeball_RT1                     (*(reg8 *)  Right_Eyeball_PWMHW__RT1)
   #define Right_Eyeball_RT1_PTR                 ( (reg8 *)  Right_Eyeball_PWMHW__RT1)

#else
   #if (Right_Eyeball_Resolution == 8u) /* 8bit - PWM */

       #if(Right_Eyeball_PWMModeIsCenterAligned)
           #define Right_Eyeball_PERIOD_LSB      (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Right_Eyeball_PERIOD_LSB_PTR  ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Right_Eyeball_PERIOD_LSB      (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Right_Eyeball_PERIOD_LSB_PTR  ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Right_Eyeball_PWMModeIsCenterAligned) */

       #define Right_Eyeball_COMPARE1_LSB        (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Right_Eyeball_COMPARE1_LSB_PTR    ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Right_Eyeball_COMPARE2_LSB        (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Right_Eyeball_COMPARE2_LSB_PTR    ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Right_Eyeball_COUNTERCAP_LSB      (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Right_Eyeball_COUNTERCAP_LSB_PTR  ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Right_Eyeball_COUNTER_LSB         (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Right_Eyeball_COUNTER_LSB_PTR     ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Right_Eyeball_CAPTURE_LSB         (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Right_Eyeball_CAPTURE_LSB_PTR     ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Right_Eyeball_PWMModeIsCenterAligned)
               #define Right_Eyeball_PERIOD_LSB      (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Right_Eyeball_PERIOD_LSB_PTR  ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Right_Eyeball_PERIOD_LSB      (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Right_Eyeball_PERIOD_LSB_PTR  ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Right_Eyeball_PWMModeIsCenterAligned) */

            #define Right_Eyeball_COMPARE1_LSB       (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Right_Eyeball_COMPARE1_LSB_PTR   ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Right_Eyeball_COMPARE2_LSB       (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Right_Eyeball_COMPARE2_LSB_PTR   ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Right_Eyeball_COUNTERCAP_LSB     (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Right_Eyeball_COUNTERCAP_LSB_PTR ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Right_Eyeball_COUNTER_LSB        (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Right_Eyeball_COUNTER_LSB_PTR    ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Right_Eyeball_CAPTURE_LSB        (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Right_Eyeball_CAPTURE_LSB_PTR    ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Right_Eyeball_PWMModeIsCenterAligned)
               #define Right_Eyeball_PERIOD_LSB      (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Right_Eyeball_PERIOD_LSB_PTR  ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Right_Eyeball_PERIOD_LSB      (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Right_Eyeball_PERIOD_LSB_PTR  ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Right_Eyeball_PWMModeIsCenterAligned) */

            #define Right_Eyeball_COMPARE1_LSB       (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Right_Eyeball_COMPARE1_LSB_PTR   ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Right_Eyeball_COMPARE2_LSB       (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Right_Eyeball_COMPARE2_LSB_PTR   ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Right_Eyeball_COUNTERCAP_LSB     (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Right_Eyeball_COUNTERCAP_LSB_PTR ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Right_Eyeball_COUNTER_LSB        (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Right_Eyeball_COUNTER_LSB_PTR    ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Right_Eyeball_CAPTURE_LSB        (*(reg16 *) Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Right_Eyeball_CAPTURE_LSB_PTR    ((reg16 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Right_Eyeball_AUX_CONTROLDP1          (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Right_Eyeball_AUX_CONTROLDP1_PTR      ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Right_Eyeball_Resolution == 8) */

   #define Right_Eyeball_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Right_Eyeball_AUX_CONTROLDP0          (*(reg8 *)  Right_Eyeball_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Right_Eyeball_AUX_CONTROLDP0_PTR      ((reg8 *)   Right_Eyeball_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Right_Eyeball_UsingFixedFunction) */

#if(Right_Eyeball_KillModeMinTime )
    #define Right_Eyeball_KILLMODEMINTIME        (*(reg8 *)  Right_Eyeball_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Right_Eyeball_KILLMODEMINTIME_PTR    ((reg8 *)   Right_Eyeball_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Right_Eyeball_KillModeMinTime ) */

#if(Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_256_CLOCKS)
    #define Right_Eyeball_DEADBAND_COUNT         (*(reg8 *)  Right_Eyeball_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Right_Eyeball_DEADBAND_COUNT_PTR     ((reg8 *)   Right_Eyeball_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Right_Eyeball_DEADBAND_LSB_PTR       ((reg8 *)   Right_Eyeball_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Right_Eyeball_DEADBAND_LSB           (*(reg8 *)  Right_Eyeball_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Right_Eyeball_UsingFixedFunction)
        #define Right_Eyeball_DEADBAND_COUNT         (*(reg8 *)  Right_Eyeball_PWMHW__CFG0)
        #define Right_Eyeball_DEADBAND_COUNT_PTR     ((reg8 *)   Right_Eyeball_PWMHW__CFG0)
        #define Right_Eyeball_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Right_Eyeball_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Right_Eyeball_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Right_Eyeball_DEADBAND_COUNT         (*(reg8 *)  Right_Eyeball_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Right_Eyeball_DEADBAND_COUNT_PTR     ((reg8 *)   Right_Eyeball_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Right_Eyeball_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Right_Eyeball_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Right_Eyeball_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Right_Eyeball_UsingFixedFunction) */
#endif /* (Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_256_CLOCKS) */



#if (Right_Eyeball_UsingFixedFunction)
    #define Right_Eyeball_STATUS                 (*(reg8 *) Right_Eyeball_PWMHW__SR0)
    #define Right_Eyeball_STATUS_PTR             ((reg8 *) Right_Eyeball_PWMHW__SR0)
    #define Right_Eyeball_STATUS_MASK            (*(reg8 *) Right_Eyeball_PWMHW__SR0)
    #define Right_Eyeball_STATUS_MASK_PTR        ((reg8 *) Right_Eyeball_PWMHW__SR0)
    #define Right_Eyeball_CONTROL                (*(reg8 *) Right_Eyeball_PWMHW__CFG0)
    #define Right_Eyeball_CONTROL_PTR            ((reg8 *) Right_Eyeball_PWMHW__CFG0)
    #define Right_Eyeball_CONTROL2               (*(reg8 *) Right_Eyeball_PWMHW__CFG1)
    #define Right_Eyeball_CONTROL3               (*(reg8 *) Right_Eyeball_PWMHW__CFG2)
    #define Right_Eyeball_GLOBAL_ENABLE          (*(reg8 *) Right_Eyeball_PWMHW__PM_ACT_CFG)
    #define Right_Eyeball_GLOBAL_ENABLE_PTR      ( (reg8 *) Right_Eyeball_PWMHW__PM_ACT_CFG)
    #define Right_Eyeball_GLOBAL_STBY_ENABLE     (*(reg8 *) Right_Eyeball_PWMHW__PM_STBY_CFG)
    #define Right_Eyeball_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Right_Eyeball_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Right_Eyeball_BLOCK_EN_MASK          (Right_Eyeball_PWMHW__PM_ACT_MSK)
    #define Right_Eyeball_BLOCK_STBY_EN_MASK     (Right_Eyeball_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Right_Eyeball_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Right_Eyeball_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Right_Eyeball_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Right_Eyeball_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Right_Eyeball_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Right_Eyeball_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Right_Eyeball_CTRL_ENABLE            (uint8)((uint8)0x01u << Right_Eyeball_CTRL_ENABLE_SHIFT)
    #define Right_Eyeball_CTRL_RESET             (uint8)((uint8)0x01u << Right_Eyeball_CTRL_RESET_SHIFT)
    #define Right_Eyeball_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Right_Eyeball_CTRL_CMPMODE2_SHIFT)
    #define Right_Eyeball_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Right_Eyeball_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Right_Eyeball_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Right_Eyeball_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Right_Eyeball_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Right_Eyeball_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Right_Eyeball_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Right_Eyeball_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Right_Eyeball_STATUS_TC_INT_EN_MASK_SHIFT            (Right_Eyeball_STATUS_TC_SHIFT - 4u)
    #define Right_Eyeball_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Right_Eyeball_STATUS_CMP1_INT_EN_MASK_SHIFT          (Right_Eyeball_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Right_Eyeball_STATUS_TC              (uint8)((uint8)0x01u << Right_Eyeball_STATUS_TC_SHIFT)
    #define Right_Eyeball_STATUS_CMP1            (uint8)((uint8)0x01u << Right_Eyeball_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Right_Eyeball_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Right_Eyeball_STATUS_TC >> 4u)
    #define Right_Eyeball_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Right_Eyeball_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Right_Eyeball_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Right_Eyeball_RT1_MASK              (uint8)((uint8)0x03u << Right_Eyeball_RT1_SHIFT)
    #define Right_Eyeball_SYNC                  (uint8)((uint8)0x03u << Right_Eyeball_RT1_SHIFT)
    #define Right_Eyeball_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Right_Eyeball_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Right_Eyeball_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Right_Eyeball_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Right_Eyeball_SYNCDSI_SHIFT)


#else
    #define Right_Eyeball_STATUS                (*(reg8 *)   Right_Eyeball_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Right_Eyeball_STATUS_PTR            ((reg8 *)    Right_Eyeball_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Right_Eyeball_STATUS_MASK           (*(reg8 *)   Right_Eyeball_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Right_Eyeball_STATUS_MASK_PTR       ((reg8 *)    Right_Eyeball_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Right_Eyeball_STATUS_AUX_CTRL       (*(reg8 *)   Right_Eyeball_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Right_Eyeball_CONTROL               (*(reg8 *)   Right_Eyeball_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Right_Eyeball_CONTROL_PTR           ((reg8 *)    Right_Eyeball_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Right_Eyeball_CTRL_ENABLE_SHIFT      (0x07u)
    #define Right_Eyeball_CTRL_RESET_SHIFT       (0x06u)
    #define Right_Eyeball_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Right_Eyeball_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Right_Eyeball_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Right_Eyeball_CTRL_ENABLE            (uint8)((uint8)0x01u << Right_Eyeball_CTRL_ENABLE_SHIFT)
    #define Right_Eyeball_CTRL_RESET             (uint8)((uint8)0x01u << Right_Eyeball_CTRL_RESET_SHIFT)
    #define Right_Eyeball_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Right_Eyeball_CTRL_CMPMODE2_SHIFT)
    #define Right_Eyeball_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Right_Eyeball_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Right_Eyeball_STATUS_KILL_SHIFT          (0x05u)
    #define Right_Eyeball_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Right_Eyeball_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Right_Eyeball_STATUS_TC_SHIFT            (0x02u)
    #define Right_Eyeball_STATUS_CMP2_SHIFT          (0x01u)
    #define Right_Eyeball_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Right_Eyeball_STATUS_KILL_INT_EN_MASK_SHIFT          (Right_Eyeball_STATUS_KILL_SHIFT)
    #define Right_Eyeball_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Right_Eyeball_STATUS_FIFONEMPTY_SHIFT)
    #define Right_Eyeball_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Right_Eyeball_STATUS_FIFOFULL_SHIFT)
    #define Right_Eyeball_STATUS_TC_INT_EN_MASK_SHIFT            (Right_Eyeball_STATUS_TC_SHIFT)
    #define Right_Eyeball_STATUS_CMP2_INT_EN_MASK_SHIFT          (Right_Eyeball_STATUS_CMP2_SHIFT)
    #define Right_Eyeball_STATUS_CMP1_INT_EN_MASK_SHIFT          (Right_Eyeball_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Right_Eyeball_STATUS_KILL            (uint8)((uint8)0x00u << Right_Eyeball_STATUS_KILL_SHIFT )
    #define Right_Eyeball_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Right_Eyeball_STATUS_FIFOFULL_SHIFT)
    #define Right_Eyeball_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Right_Eyeball_STATUS_FIFONEMPTY_SHIFT)
    #define Right_Eyeball_STATUS_TC              (uint8)((uint8)0x01u << Right_Eyeball_STATUS_TC_SHIFT)
    #define Right_Eyeball_STATUS_CMP2            (uint8)((uint8)0x01u << Right_Eyeball_STATUS_CMP2_SHIFT)
    #define Right_Eyeball_STATUS_CMP1            (uint8)((uint8)0x01u << Right_Eyeball_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Right_Eyeball_STATUS_KILL_INT_EN_MASK            (Right_Eyeball_STATUS_KILL)
    #define Right_Eyeball_STATUS_FIFOFULL_INT_EN_MASK        (Right_Eyeball_STATUS_FIFOFULL)
    #define Right_Eyeball_STATUS_FIFONEMPTY_INT_EN_MASK      (Right_Eyeball_STATUS_FIFONEMPTY)
    #define Right_Eyeball_STATUS_TC_INT_EN_MASK              (Right_Eyeball_STATUS_TC)
    #define Right_Eyeball_STATUS_CMP2_INT_EN_MASK            (Right_Eyeball_STATUS_CMP2)
    #define Right_Eyeball_STATUS_CMP1_INT_EN_MASK            (Right_Eyeball_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Right_Eyeball_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Right_Eyeball_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Right_Eyeball_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Right_Eyeball_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Right_Eyeball_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Right_Eyeball_UsingFixedFunction */

#endif  /* CY_PWM_Right_Eyeball_H */


/* [] END OF FILE */
