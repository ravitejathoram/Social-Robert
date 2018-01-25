/*******************************************************************************
* File Name: Eyelid.h
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

#if !defined(CY_PWM_Eyelid_H)
#define CY_PWM_Eyelid_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Eyelid_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Eyelid_Resolution                     (16u)
#define Eyelid_UsingFixedFunction             (0u)
#define Eyelid_DeadBandMode                   (0u)
#define Eyelid_KillModeMinTime                (0u)
#define Eyelid_KillMode                       (0u)
#define Eyelid_PWMMode                        (1u)
#define Eyelid_PWMModeIsCenterAligned         (0u)
#define Eyelid_DeadBandUsed                   (0u)
#define Eyelid_DeadBand2_4                    (0u)

#if !defined(Eyelid_PWMUDB_genblk8_stsreg__REMOVED)
    #define Eyelid_UseStatus                  (1u)
#else
    #define Eyelid_UseStatus                  (0u)
#endif /* !defined(Eyelid_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Eyelid_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Eyelid_UseControl                 (1u)
#else
    #define Eyelid_UseControl                 (0u)
#endif /* !defined(Eyelid_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Eyelid_UseOneCompareMode              (0u)
#define Eyelid_MinimumKillTime                (1u)
#define Eyelid_EnableMode                     (0u)

#define Eyelid_CompareMode1SW                 (0u)
#define Eyelid_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Eyelid__B_PWM__DISABLED 0
#define Eyelid__B_PWM__ASYNCHRONOUS 1
#define Eyelid__B_PWM__SINGLECYCLE 2
#define Eyelid__B_PWM__LATCHED 3
#define Eyelid__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Eyelid__B_PWM__DBMDISABLED 0
#define Eyelid__B_PWM__DBM_2_4_CLOCKS 1
#define Eyelid__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Eyelid__B_PWM__ONE_OUTPUT 0
#define Eyelid__B_PWM__TWO_OUTPUTS 1
#define Eyelid__B_PWM__DUAL_EDGE 2
#define Eyelid__B_PWM__CENTER_ALIGN 3
#define Eyelid__B_PWM__DITHER 5
#define Eyelid__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Eyelid__B_PWM__LESS_THAN 1
#define Eyelid__B_PWM__LESS_THAN_OR_EQUAL 2
#define Eyelid__B_PWM__GREATER_THAN 3
#define Eyelid__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Eyelid__B_PWM__EQUAL 0
#define Eyelid__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Eyelid_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Eyelid_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Eyelid_PWMModeIsCenterAligned) */
        #if (Eyelid_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Eyelid_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_256_CLOCKS || \
            Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Eyelid_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Eyelid_KillModeMinTime) */

        /* Backup control register */
        #if(Eyelid_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Eyelid_UseControl) */

    #endif /* (!Eyelid_UsingFixedFunction) */

}Eyelid_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Eyelid_Start(void) ;
void    Eyelid_Stop(void) ;

#if (Eyelid_UseStatus || Eyelid_UsingFixedFunction)
    void  Eyelid_SetInterruptMode(uint8 interruptMode) ;
    uint8 Eyelid_ReadStatusRegister(void) ;
#endif /* (Eyelid_UseStatus || Eyelid_UsingFixedFunction) */

#define Eyelid_GetInterruptSource() Eyelid_ReadStatusRegister()

#if (Eyelid_UseControl)
    uint8 Eyelid_ReadControlRegister(void) ;
    void  Eyelid_WriteControlRegister(uint8 control)
          ;
#endif /* (Eyelid_UseControl) */

#if (Eyelid_UseOneCompareMode)
   #if (Eyelid_CompareMode1SW)
       void    Eyelid_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Eyelid_CompareMode1SW) */
#else
    #if (Eyelid_CompareMode1SW)
        void    Eyelid_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Eyelid_CompareMode1SW) */
    #if (Eyelid_CompareMode2SW)
        void    Eyelid_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Eyelid_CompareMode2SW) */
#endif /* (Eyelid_UseOneCompareMode) */

#if (!Eyelid_UsingFixedFunction)
    uint16   Eyelid_ReadCounter(void) ;
    uint16 Eyelid_ReadCapture(void) ;

    #if (Eyelid_UseStatus)
            void Eyelid_ClearFIFO(void) ;
    #endif /* (Eyelid_UseStatus) */

    void    Eyelid_WriteCounter(uint16 counter)
            ;
#endif /* (!Eyelid_UsingFixedFunction) */

void    Eyelid_WritePeriod(uint16 period)
        ;
uint16 Eyelid_ReadPeriod(void) ;

#if (Eyelid_UseOneCompareMode)
    void    Eyelid_WriteCompare(uint16 compare)
            ;
    uint16 Eyelid_ReadCompare(void) ;
#else
    void    Eyelid_WriteCompare1(uint16 compare)
            ;
    uint16 Eyelid_ReadCompare1(void) ;
    void    Eyelid_WriteCompare2(uint16 compare)
            ;
    uint16 Eyelid_ReadCompare2(void) ;
#endif /* (Eyelid_UseOneCompareMode) */


#if (Eyelid_DeadBandUsed)
    void    Eyelid_WriteDeadTime(uint8 deadtime) ;
    uint8   Eyelid_ReadDeadTime(void) ;
#endif /* (Eyelid_DeadBandUsed) */

#if ( Eyelid_KillModeMinTime)
    void Eyelid_WriteKillTime(uint8 killtime) ;
    uint8 Eyelid_ReadKillTime(void) ;
#endif /* ( Eyelid_KillModeMinTime) */

void Eyelid_Init(void) ;
void Eyelid_Enable(void) ;
void Eyelid_Sleep(void) ;
void Eyelid_Wakeup(void) ;
void Eyelid_SaveConfig(void) ;
void Eyelid_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Eyelid_INIT_PERIOD_VALUE          (60000u)
#define Eyelid_INIT_COMPARE_VALUE1        (0u)
#define Eyelid_INIT_COMPARE_VALUE2        (0u)
#define Eyelid_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Eyelid_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Eyelid_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Eyelid_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Eyelid_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Eyelid_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Eyelid_CTRL_CMPMODE2_SHIFT)
#define Eyelid_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Eyelid_CTRL_CMPMODE1_SHIFT)
#define Eyelid_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Eyelid_UsingFixedFunction)
   #define Eyelid_PERIOD_LSB              (*(reg16 *) Eyelid_PWMHW__PER0)
   #define Eyelid_PERIOD_LSB_PTR          ( (reg16 *) Eyelid_PWMHW__PER0)
   #define Eyelid_COMPARE1_LSB            (*(reg16 *) Eyelid_PWMHW__CNT_CMP0)
   #define Eyelid_COMPARE1_LSB_PTR        ( (reg16 *) Eyelid_PWMHW__CNT_CMP0)
   #define Eyelid_COMPARE2_LSB            (0x00u)
   #define Eyelid_COMPARE2_LSB_PTR        (0x00u)
   #define Eyelid_COUNTER_LSB             (*(reg16 *) Eyelid_PWMHW__CNT_CMP0)
   #define Eyelid_COUNTER_LSB_PTR         ( (reg16 *) Eyelid_PWMHW__CNT_CMP0)
   #define Eyelid_CAPTURE_LSB             (*(reg16 *) Eyelid_PWMHW__CAP0)
   #define Eyelid_CAPTURE_LSB_PTR         ( (reg16 *) Eyelid_PWMHW__CAP0)
   #define Eyelid_RT1                     (*(reg8 *)  Eyelid_PWMHW__RT1)
   #define Eyelid_RT1_PTR                 ( (reg8 *)  Eyelid_PWMHW__RT1)

#else
   #if (Eyelid_Resolution == 8u) /* 8bit - PWM */

       #if(Eyelid_PWMModeIsCenterAligned)
           #define Eyelid_PERIOD_LSB      (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Eyelid_PERIOD_LSB_PTR  ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Eyelid_PERIOD_LSB      (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Eyelid_PERIOD_LSB_PTR  ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Eyelid_PWMModeIsCenterAligned) */

       #define Eyelid_COMPARE1_LSB        (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Eyelid_COMPARE1_LSB_PTR    ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Eyelid_COMPARE2_LSB        (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Eyelid_COMPARE2_LSB_PTR    ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Eyelid_COUNTERCAP_LSB      (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Eyelid_COUNTERCAP_LSB_PTR  ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Eyelid_COUNTER_LSB         (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Eyelid_COUNTER_LSB_PTR     ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Eyelid_CAPTURE_LSB         (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Eyelid_CAPTURE_LSB_PTR     ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Eyelid_PWMModeIsCenterAligned)
               #define Eyelid_PERIOD_LSB      (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Eyelid_PERIOD_LSB_PTR  ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Eyelid_PERIOD_LSB      (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Eyelid_PERIOD_LSB_PTR  ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Eyelid_PWMModeIsCenterAligned) */

            #define Eyelid_COMPARE1_LSB       (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Eyelid_COMPARE1_LSB_PTR   ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Eyelid_COMPARE2_LSB       (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Eyelid_COMPARE2_LSB_PTR   ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Eyelid_COUNTERCAP_LSB     (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Eyelid_COUNTERCAP_LSB_PTR ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Eyelid_COUNTER_LSB        (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Eyelid_COUNTER_LSB_PTR    ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Eyelid_CAPTURE_LSB        (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Eyelid_CAPTURE_LSB_PTR    ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Eyelid_PWMModeIsCenterAligned)
               #define Eyelid_PERIOD_LSB      (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Eyelid_PERIOD_LSB_PTR  ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Eyelid_PERIOD_LSB      (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Eyelid_PERIOD_LSB_PTR  ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Eyelid_PWMModeIsCenterAligned) */

            #define Eyelid_COMPARE1_LSB       (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Eyelid_COMPARE1_LSB_PTR   ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Eyelid_COMPARE2_LSB       (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Eyelid_COMPARE2_LSB_PTR   ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Eyelid_COUNTERCAP_LSB     (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Eyelid_COUNTERCAP_LSB_PTR ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Eyelid_COUNTER_LSB        (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Eyelid_COUNTER_LSB_PTR    ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Eyelid_CAPTURE_LSB        (*(reg16 *) Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Eyelid_CAPTURE_LSB_PTR    ((reg16 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Eyelid_AUX_CONTROLDP1          (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Eyelid_AUX_CONTROLDP1_PTR      ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Eyelid_Resolution == 8) */

   #define Eyelid_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Eyelid_AUX_CONTROLDP0          (*(reg8 *)  Eyelid_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Eyelid_AUX_CONTROLDP0_PTR      ((reg8 *)   Eyelid_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Eyelid_UsingFixedFunction) */

#if(Eyelid_KillModeMinTime )
    #define Eyelid_KILLMODEMINTIME        (*(reg8 *)  Eyelid_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Eyelid_KILLMODEMINTIME_PTR    ((reg8 *)   Eyelid_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Eyelid_KillModeMinTime ) */

#if(Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_256_CLOCKS)
    #define Eyelid_DEADBAND_COUNT         (*(reg8 *)  Eyelid_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Eyelid_DEADBAND_COUNT_PTR     ((reg8 *)   Eyelid_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Eyelid_DEADBAND_LSB_PTR       ((reg8 *)   Eyelid_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Eyelid_DEADBAND_LSB           (*(reg8 *)  Eyelid_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Eyelid_UsingFixedFunction)
        #define Eyelid_DEADBAND_COUNT         (*(reg8 *)  Eyelid_PWMHW__CFG0)
        #define Eyelid_DEADBAND_COUNT_PTR     ((reg8 *)   Eyelid_PWMHW__CFG0)
        #define Eyelid_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Eyelid_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Eyelid_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Eyelid_DEADBAND_COUNT         (*(reg8 *)  Eyelid_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Eyelid_DEADBAND_COUNT_PTR     ((reg8 *)   Eyelid_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Eyelid_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Eyelid_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Eyelid_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Eyelid_UsingFixedFunction) */
#endif /* (Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_256_CLOCKS) */



#if (Eyelid_UsingFixedFunction)
    #define Eyelid_STATUS                 (*(reg8 *) Eyelid_PWMHW__SR0)
    #define Eyelid_STATUS_PTR             ((reg8 *) Eyelid_PWMHW__SR0)
    #define Eyelid_STATUS_MASK            (*(reg8 *) Eyelid_PWMHW__SR0)
    #define Eyelid_STATUS_MASK_PTR        ((reg8 *) Eyelid_PWMHW__SR0)
    #define Eyelid_CONTROL                (*(reg8 *) Eyelid_PWMHW__CFG0)
    #define Eyelid_CONTROL_PTR            ((reg8 *) Eyelid_PWMHW__CFG0)
    #define Eyelid_CONTROL2               (*(reg8 *) Eyelid_PWMHW__CFG1)
    #define Eyelid_CONTROL3               (*(reg8 *) Eyelid_PWMHW__CFG2)
    #define Eyelid_GLOBAL_ENABLE          (*(reg8 *) Eyelid_PWMHW__PM_ACT_CFG)
    #define Eyelid_GLOBAL_ENABLE_PTR      ( (reg8 *) Eyelid_PWMHW__PM_ACT_CFG)
    #define Eyelid_GLOBAL_STBY_ENABLE     (*(reg8 *) Eyelid_PWMHW__PM_STBY_CFG)
    #define Eyelid_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Eyelid_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Eyelid_BLOCK_EN_MASK          (Eyelid_PWMHW__PM_ACT_MSK)
    #define Eyelid_BLOCK_STBY_EN_MASK     (Eyelid_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Eyelid_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Eyelid_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Eyelid_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Eyelid_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Eyelid_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Eyelid_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Eyelid_CTRL_ENABLE            (uint8)((uint8)0x01u << Eyelid_CTRL_ENABLE_SHIFT)
    #define Eyelid_CTRL_RESET             (uint8)((uint8)0x01u << Eyelid_CTRL_RESET_SHIFT)
    #define Eyelid_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Eyelid_CTRL_CMPMODE2_SHIFT)
    #define Eyelid_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Eyelid_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Eyelid_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Eyelid_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Eyelid_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Eyelid_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Eyelid_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Eyelid_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Eyelid_STATUS_TC_INT_EN_MASK_SHIFT            (Eyelid_STATUS_TC_SHIFT - 4u)
    #define Eyelid_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Eyelid_STATUS_CMP1_INT_EN_MASK_SHIFT          (Eyelid_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Eyelid_STATUS_TC              (uint8)((uint8)0x01u << Eyelid_STATUS_TC_SHIFT)
    #define Eyelid_STATUS_CMP1            (uint8)((uint8)0x01u << Eyelid_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Eyelid_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Eyelid_STATUS_TC >> 4u)
    #define Eyelid_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Eyelid_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Eyelid_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Eyelid_RT1_MASK              (uint8)((uint8)0x03u << Eyelid_RT1_SHIFT)
    #define Eyelid_SYNC                  (uint8)((uint8)0x03u << Eyelid_RT1_SHIFT)
    #define Eyelid_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Eyelid_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Eyelid_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Eyelid_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Eyelid_SYNCDSI_SHIFT)


#else
    #define Eyelid_STATUS                (*(reg8 *)   Eyelid_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Eyelid_STATUS_PTR            ((reg8 *)    Eyelid_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Eyelid_STATUS_MASK           (*(reg8 *)   Eyelid_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Eyelid_STATUS_MASK_PTR       ((reg8 *)    Eyelid_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Eyelid_STATUS_AUX_CTRL       (*(reg8 *)   Eyelid_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Eyelid_CONTROL               (*(reg8 *)   Eyelid_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Eyelid_CONTROL_PTR           ((reg8 *)    Eyelid_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Eyelid_CTRL_ENABLE_SHIFT      (0x07u)
    #define Eyelid_CTRL_RESET_SHIFT       (0x06u)
    #define Eyelid_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Eyelid_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Eyelid_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Eyelid_CTRL_ENABLE            (uint8)((uint8)0x01u << Eyelid_CTRL_ENABLE_SHIFT)
    #define Eyelid_CTRL_RESET             (uint8)((uint8)0x01u << Eyelid_CTRL_RESET_SHIFT)
    #define Eyelid_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Eyelid_CTRL_CMPMODE2_SHIFT)
    #define Eyelid_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Eyelid_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Eyelid_STATUS_KILL_SHIFT          (0x05u)
    #define Eyelid_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Eyelid_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Eyelid_STATUS_TC_SHIFT            (0x02u)
    #define Eyelid_STATUS_CMP2_SHIFT          (0x01u)
    #define Eyelid_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Eyelid_STATUS_KILL_INT_EN_MASK_SHIFT          (Eyelid_STATUS_KILL_SHIFT)
    #define Eyelid_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Eyelid_STATUS_FIFONEMPTY_SHIFT)
    #define Eyelid_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Eyelid_STATUS_FIFOFULL_SHIFT)
    #define Eyelid_STATUS_TC_INT_EN_MASK_SHIFT            (Eyelid_STATUS_TC_SHIFT)
    #define Eyelid_STATUS_CMP2_INT_EN_MASK_SHIFT          (Eyelid_STATUS_CMP2_SHIFT)
    #define Eyelid_STATUS_CMP1_INT_EN_MASK_SHIFT          (Eyelid_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Eyelid_STATUS_KILL            (uint8)((uint8)0x00u << Eyelid_STATUS_KILL_SHIFT )
    #define Eyelid_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Eyelid_STATUS_FIFOFULL_SHIFT)
    #define Eyelid_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Eyelid_STATUS_FIFONEMPTY_SHIFT)
    #define Eyelid_STATUS_TC              (uint8)((uint8)0x01u << Eyelid_STATUS_TC_SHIFT)
    #define Eyelid_STATUS_CMP2            (uint8)((uint8)0x01u << Eyelid_STATUS_CMP2_SHIFT)
    #define Eyelid_STATUS_CMP1            (uint8)((uint8)0x01u << Eyelid_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Eyelid_STATUS_KILL_INT_EN_MASK            (Eyelid_STATUS_KILL)
    #define Eyelid_STATUS_FIFOFULL_INT_EN_MASK        (Eyelid_STATUS_FIFOFULL)
    #define Eyelid_STATUS_FIFONEMPTY_INT_EN_MASK      (Eyelid_STATUS_FIFONEMPTY)
    #define Eyelid_STATUS_TC_INT_EN_MASK              (Eyelid_STATUS_TC)
    #define Eyelid_STATUS_CMP2_INT_EN_MASK            (Eyelid_STATUS_CMP2)
    #define Eyelid_STATUS_CMP1_INT_EN_MASK            (Eyelid_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Eyelid_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Eyelid_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Eyelid_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Eyelid_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Eyelid_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Eyelid_UsingFixedFunction */

#endif  /* CY_PWM_Eyelid_H */


/* [] END OF FILE */
