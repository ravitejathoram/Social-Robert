/*******************************************************************************
* File Name: Lips.h
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

#if !defined(CY_PWM_Lips_H)
#define CY_PWM_Lips_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Lips_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Lips_Resolution                     (16u)
#define Lips_UsingFixedFunction             (0u)
#define Lips_DeadBandMode                   (0u)
#define Lips_KillModeMinTime                (0u)
#define Lips_KillMode                       (0u)
#define Lips_PWMMode                        (1u)
#define Lips_PWMModeIsCenterAligned         (0u)
#define Lips_DeadBandUsed                   (0u)
#define Lips_DeadBand2_4                    (0u)

#if !defined(Lips_PWMUDB_genblk8_stsreg__REMOVED)
    #define Lips_UseStatus                  (1u)
#else
    #define Lips_UseStatus                  (0u)
#endif /* !defined(Lips_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Lips_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Lips_UseControl                 (1u)
#else
    #define Lips_UseControl                 (0u)
#endif /* !defined(Lips_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Lips_UseOneCompareMode              (0u)
#define Lips_MinimumKillTime                (1u)
#define Lips_EnableMode                     (0u)

#define Lips_CompareMode1SW                 (0u)
#define Lips_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Lips__B_PWM__DISABLED 0
#define Lips__B_PWM__ASYNCHRONOUS 1
#define Lips__B_PWM__SINGLECYCLE 2
#define Lips__B_PWM__LATCHED 3
#define Lips__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Lips__B_PWM__DBMDISABLED 0
#define Lips__B_PWM__DBM_2_4_CLOCKS 1
#define Lips__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Lips__B_PWM__ONE_OUTPUT 0
#define Lips__B_PWM__TWO_OUTPUTS 1
#define Lips__B_PWM__DUAL_EDGE 2
#define Lips__B_PWM__CENTER_ALIGN 3
#define Lips__B_PWM__DITHER 5
#define Lips__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Lips__B_PWM__LESS_THAN 1
#define Lips__B_PWM__LESS_THAN_OR_EQUAL 2
#define Lips__B_PWM__GREATER_THAN 3
#define Lips__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Lips__B_PWM__EQUAL 0
#define Lips__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Lips_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Lips_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Lips_PWMModeIsCenterAligned) */
        #if (Lips_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Lips_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Lips_DeadBandMode == Lips__B_PWM__DBM_256_CLOCKS || \
            Lips_DeadBandMode == Lips__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Lips_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Lips_KillModeMinTime) */

        /* Backup control register */
        #if(Lips_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Lips_UseControl) */

    #endif /* (!Lips_UsingFixedFunction) */

}Lips_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Lips_Start(void) ;
void    Lips_Stop(void) ;

#if (Lips_UseStatus || Lips_UsingFixedFunction)
    void  Lips_SetInterruptMode(uint8 interruptMode) ;
    uint8 Lips_ReadStatusRegister(void) ;
#endif /* (Lips_UseStatus || Lips_UsingFixedFunction) */

#define Lips_GetInterruptSource() Lips_ReadStatusRegister()

#if (Lips_UseControl)
    uint8 Lips_ReadControlRegister(void) ;
    void  Lips_WriteControlRegister(uint8 control)
          ;
#endif /* (Lips_UseControl) */

#if (Lips_UseOneCompareMode)
   #if (Lips_CompareMode1SW)
       void    Lips_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Lips_CompareMode1SW) */
#else
    #if (Lips_CompareMode1SW)
        void    Lips_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Lips_CompareMode1SW) */
    #if (Lips_CompareMode2SW)
        void    Lips_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Lips_CompareMode2SW) */
#endif /* (Lips_UseOneCompareMode) */

#if (!Lips_UsingFixedFunction)
    uint16   Lips_ReadCounter(void) ;
    uint16 Lips_ReadCapture(void) ;

    #if (Lips_UseStatus)
            void Lips_ClearFIFO(void) ;
    #endif /* (Lips_UseStatus) */

    void    Lips_WriteCounter(uint16 counter)
            ;
#endif /* (!Lips_UsingFixedFunction) */

void    Lips_WritePeriod(uint16 period)
        ;
uint16 Lips_ReadPeriod(void) ;

#if (Lips_UseOneCompareMode)
    void    Lips_WriteCompare(uint16 compare)
            ;
    uint16 Lips_ReadCompare(void) ;
#else
    void    Lips_WriteCompare1(uint16 compare)
            ;
    uint16 Lips_ReadCompare1(void) ;
    void    Lips_WriteCompare2(uint16 compare)
            ;
    uint16 Lips_ReadCompare2(void) ;
#endif /* (Lips_UseOneCompareMode) */


#if (Lips_DeadBandUsed)
    void    Lips_WriteDeadTime(uint8 deadtime) ;
    uint8   Lips_ReadDeadTime(void) ;
#endif /* (Lips_DeadBandUsed) */

#if ( Lips_KillModeMinTime)
    void Lips_WriteKillTime(uint8 killtime) ;
    uint8 Lips_ReadKillTime(void) ;
#endif /* ( Lips_KillModeMinTime) */

void Lips_Init(void) ;
void Lips_Enable(void) ;
void Lips_Sleep(void) ;
void Lips_Wakeup(void) ;
void Lips_SaveConfig(void) ;
void Lips_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Lips_INIT_PERIOD_VALUE          (60000u)
#define Lips_INIT_COMPARE_VALUE1        (0u)
#define Lips_INIT_COMPARE_VALUE2        (0u)
#define Lips_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Lips_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lips_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lips_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lips_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Lips_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Lips_CTRL_CMPMODE2_SHIFT)
#define Lips_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Lips_CTRL_CMPMODE1_SHIFT)
#define Lips_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Lips_UsingFixedFunction)
   #define Lips_PERIOD_LSB              (*(reg16 *) Lips_PWMHW__PER0)
   #define Lips_PERIOD_LSB_PTR          ( (reg16 *) Lips_PWMHW__PER0)
   #define Lips_COMPARE1_LSB            (*(reg16 *) Lips_PWMHW__CNT_CMP0)
   #define Lips_COMPARE1_LSB_PTR        ( (reg16 *) Lips_PWMHW__CNT_CMP0)
   #define Lips_COMPARE2_LSB            (0x00u)
   #define Lips_COMPARE2_LSB_PTR        (0x00u)
   #define Lips_COUNTER_LSB             (*(reg16 *) Lips_PWMHW__CNT_CMP0)
   #define Lips_COUNTER_LSB_PTR         ( (reg16 *) Lips_PWMHW__CNT_CMP0)
   #define Lips_CAPTURE_LSB             (*(reg16 *) Lips_PWMHW__CAP0)
   #define Lips_CAPTURE_LSB_PTR         ( (reg16 *) Lips_PWMHW__CAP0)
   #define Lips_RT1                     (*(reg8 *)  Lips_PWMHW__RT1)
   #define Lips_RT1_PTR                 ( (reg8 *)  Lips_PWMHW__RT1)

#else
   #if (Lips_Resolution == 8u) /* 8bit - PWM */

       #if(Lips_PWMModeIsCenterAligned)
           #define Lips_PERIOD_LSB      (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Lips_PERIOD_LSB_PTR  ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Lips_PERIOD_LSB      (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Lips_PERIOD_LSB_PTR  ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Lips_PWMModeIsCenterAligned) */

       #define Lips_COMPARE1_LSB        (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Lips_COMPARE1_LSB_PTR    ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Lips_COMPARE2_LSB        (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Lips_COMPARE2_LSB_PTR    ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Lips_COUNTERCAP_LSB      (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Lips_COUNTERCAP_LSB_PTR  ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Lips_COUNTER_LSB         (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Lips_COUNTER_LSB_PTR     ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Lips_CAPTURE_LSB         (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Lips_CAPTURE_LSB_PTR     ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Lips_PWMModeIsCenterAligned)
               #define Lips_PERIOD_LSB      (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Lips_PERIOD_LSB_PTR  ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Lips_PERIOD_LSB      (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Lips_PERIOD_LSB_PTR  ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Lips_PWMModeIsCenterAligned) */

            #define Lips_COMPARE1_LSB       (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Lips_COMPARE1_LSB_PTR   ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Lips_COMPARE2_LSB       (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Lips_COMPARE2_LSB_PTR   ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Lips_COUNTERCAP_LSB     (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Lips_COUNTERCAP_LSB_PTR ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Lips_COUNTER_LSB        (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Lips_COUNTER_LSB_PTR    ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Lips_CAPTURE_LSB        (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Lips_CAPTURE_LSB_PTR    ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Lips_PWMModeIsCenterAligned)
               #define Lips_PERIOD_LSB      (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Lips_PERIOD_LSB_PTR  ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Lips_PERIOD_LSB      (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Lips_PERIOD_LSB_PTR  ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Lips_PWMModeIsCenterAligned) */

            #define Lips_COMPARE1_LSB       (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Lips_COMPARE1_LSB_PTR   ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Lips_COMPARE2_LSB       (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Lips_COMPARE2_LSB_PTR   ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Lips_COUNTERCAP_LSB     (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Lips_COUNTERCAP_LSB_PTR ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Lips_COUNTER_LSB        (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Lips_COUNTER_LSB_PTR    ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Lips_CAPTURE_LSB        (*(reg16 *) Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Lips_CAPTURE_LSB_PTR    ((reg16 *)  Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Lips_AUX_CONTROLDP1          (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Lips_AUX_CONTROLDP1_PTR      ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Lips_Resolution == 8) */

   #define Lips_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Lips_AUX_CONTROLDP0          (*(reg8 *)  Lips_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Lips_AUX_CONTROLDP0_PTR      ((reg8 *)   Lips_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Lips_UsingFixedFunction) */

#if(Lips_KillModeMinTime )
    #define Lips_KILLMODEMINTIME        (*(reg8 *)  Lips_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Lips_KILLMODEMINTIME_PTR    ((reg8 *)   Lips_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Lips_KillModeMinTime ) */

#if(Lips_DeadBandMode == Lips__B_PWM__DBM_256_CLOCKS)
    #define Lips_DEADBAND_COUNT         (*(reg8 *)  Lips_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Lips_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Lips_DEADBAND_LSB_PTR       ((reg8 *)   Lips_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Lips_DEADBAND_LSB           (*(reg8 *)  Lips_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Lips_DeadBandMode == Lips__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Lips_UsingFixedFunction)
        #define Lips_DEADBAND_COUNT         (*(reg8 *)  Lips_PWMHW__CFG0)
        #define Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Lips_PWMHW__CFG0)
        #define Lips_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Lips_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Lips_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Lips_DEADBAND_COUNT         (*(reg8 *)  Lips_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Lips_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Lips_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Lips_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Lips_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Lips_UsingFixedFunction) */
#endif /* (Lips_DeadBandMode == Lips__B_PWM__DBM_256_CLOCKS) */



#if (Lips_UsingFixedFunction)
    #define Lips_STATUS                 (*(reg8 *) Lips_PWMHW__SR0)
    #define Lips_STATUS_PTR             ((reg8 *) Lips_PWMHW__SR0)
    #define Lips_STATUS_MASK            (*(reg8 *) Lips_PWMHW__SR0)
    #define Lips_STATUS_MASK_PTR        ((reg8 *) Lips_PWMHW__SR0)
    #define Lips_CONTROL                (*(reg8 *) Lips_PWMHW__CFG0)
    #define Lips_CONTROL_PTR            ((reg8 *) Lips_PWMHW__CFG0)
    #define Lips_CONTROL2               (*(reg8 *) Lips_PWMHW__CFG1)
    #define Lips_CONTROL3               (*(reg8 *) Lips_PWMHW__CFG2)
    #define Lips_GLOBAL_ENABLE          (*(reg8 *) Lips_PWMHW__PM_ACT_CFG)
    #define Lips_GLOBAL_ENABLE_PTR      ( (reg8 *) Lips_PWMHW__PM_ACT_CFG)
    #define Lips_GLOBAL_STBY_ENABLE     (*(reg8 *) Lips_PWMHW__PM_STBY_CFG)
    #define Lips_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Lips_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Lips_BLOCK_EN_MASK          (Lips_PWMHW__PM_ACT_MSK)
    #define Lips_BLOCK_STBY_EN_MASK     (Lips_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Lips_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Lips_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Lips_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Lips_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Lips_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Lips_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Lips_CTRL_ENABLE            (uint8)((uint8)0x01u << Lips_CTRL_ENABLE_SHIFT)
    #define Lips_CTRL_RESET             (uint8)((uint8)0x01u << Lips_CTRL_RESET_SHIFT)
    #define Lips_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Lips_CTRL_CMPMODE2_SHIFT)
    #define Lips_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Lips_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Lips_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Lips_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Lips_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Lips_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Lips_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Lips_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Lips_STATUS_TC_INT_EN_MASK_SHIFT            (Lips_STATUS_TC_SHIFT - 4u)
    #define Lips_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Lips_STATUS_CMP1_INT_EN_MASK_SHIFT          (Lips_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Lips_STATUS_TC              (uint8)((uint8)0x01u << Lips_STATUS_TC_SHIFT)
    #define Lips_STATUS_CMP1            (uint8)((uint8)0x01u << Lips_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Lips_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Lips_STATUS_TC >> 4u)
    #define Lips_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Lips_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Lips_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Lips_RT1_MASK              (uint8)((uint8)0x03u << Lips_RT1_SHIFT)
    #define Lips_SYNC                  (uint8)((uint8)0x03u << Lips_RT1_SHIFT)
    #define Lips_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Lips_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Lips_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Lips_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Lips_SYNCDSI_SHIFT)


#else
    #define Lips_STATUS                (*(reg8 *)   Lips_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Lips_STATUS_PTR            ((reg8 *)    Lips_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Lips_STATUS_MASK           (*(reg8 *)   Lips_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Lips_STATUS_MASK_PTR       ((reg8 *)    Lips_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Lips_STATUS_AUX_CTRL       (*(reg8 *)   Lips_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Lips_CONTROL               (*(reg8 *)   Lips_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Lips_CONTROL_PTR           ((reg8 *)    Lips_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Lips_CTRL_ENABLE_SHIFT      (0x07u)
    #define Lips_CTRL_RESET_SHIFT       (0x06u)
    #define Lips_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Lips_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Lips_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Lips_CTRL_ENABLE            (uint8)((uint8)0x01u << Lips_CTRL_ENABLE_SHIFT)
    #define Lips_CTRL_RESET             (uint8)((uint8)0x01u << Lips_CTRL_RESET_SHIFT)
    #define Lips_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Lips_CTRL_CMPMODE2_SHIFT)
    #define Lips_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Lips_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Lips_STATUS_KILL_SHIFT          (0x05u)
    #define Lips_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Lips_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Lips_STATUS_TC_SHIFT            (0x02u)
    #define Lips_STATUS_CMP2_SHIFT          (0x01u)
    #define Lips_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Lips_STATUS_KILL_INT_EN_MASK_SHIFT          (Lips_STATUS_KILL_SHIFT)
    #define Lips_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Lips_STATUS_FIFONEMPTY_SHIFT)
    #define Lips_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Lips_STATUS_FIFOFULL_SHIFT)
    #define Lips_STATUS_TC_INT_EN_MASK_SHIFT            (Lips_STATUS_TC_SHIFT)
    #define Lips_STATUS_CMP2_INT_EN_MASK_SHIFT          (Lips_STATUS_CMP2_SHIFT)
    #define Lips_STATUS_CMP1_INT_EN_MASK_SHIFT          (Lips_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Lips_STATUS_KILL            (uint8)((uint8)0x00u << Lips_STATUS_KILL_SHIFT )
    #define Lips_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Lips_STATUS_FIFOFULL_SHIFT)
    #define Lips_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Lips_STATUS_FIFONEMPTY_SHIFT)
    #define Lips_STATUS_TC              (uint8)((uint8)0x01u << Lips_STATUS_TC_SHIFT)
    #define Lips_STATUS_CMP2            (uint8)((uint8)0x01u << Lips_STATUS_CMP2_SHIFT)
    #define Lips_STATUS_CMP1            (uint8)((uint8)0x01u << Lips_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Lips_STATUS_KILL_INT_EN_MASK            (Lips_STATUS_KILL)
    #define Lips_STATUS_FIFOFULL_INT_EN_MASK        (Lips_STATUS_FIFOFULL)
    #define Lips_STATUS_FIFONEMPTY_INT_EN_MASK      (Lips_STATUS_FIFONEMPTY)
    #define Lips_STATUS_TC_INT_EN_MASK              (Lips_STATUS_TC)
    #define Lips_STATUS_CMP2_INT_EN_MASK            (Lips_STATUS_CMP2)
    #define Lips_STATUS_CMP1_INT_EN_MASK            (Lips_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Lips_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Lips_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Lips_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Lips_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Lips_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Lips_UsingFixedFunction */

#endif  /* CY_PWM_Lips_H */


/* [] END OF FILE */
