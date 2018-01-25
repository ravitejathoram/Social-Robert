/*******************************************************************************
* File Name: EyeballVertical.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "EyeballVertical.h"

/* Error message for removed <resource> through optimization */
#ifdef EyeballVertical_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* EyeballVertical_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 EyeballVertical_initVar = 0u;


/*******************************************************************************
* Function Name: EyeballVertical_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EyeballVertical_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void EyeballVertical_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(EyeballVertical_initVar == 0u)
    {
        EyeballVertical_Init();
        EyeballVertical_initVar = 1u;
    }
    EyeballVertical_Enable();

}


/*******************************************************************************
* Function Name: EyeballVertical_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  EyeballVertical_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EyeballVertical_Init(void) 
{
    #if (EyeballVertical_UsingFixedFunction || EyeballVertical_UseControl)
        uint8 ctrl;
    #endif /* (EyeballVertical_UsingFixedFunction || EyeballVertical_UseControl) */

    #if(!EyeballVertical_UsingFixedFunction)
        #if(EyeballVertical_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 EyeballVertical_interruptState;
        #endif /* (EyeballVertical_UseStatus) */
    #endif /* (!EyeballVertical_UsingFixedFunction) */

    #if (EyeballVertical_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        EyeballVertical_CONTROL |= EyeballVertical_CFG0_MODE;
        #if (EyeballVertical_DeadBand2_4)
            EyeballVertical_CONTROL |= EyeballVertical_CFG0_DB;
        #endif /* (EyeballVertical_DeadBand2_4) */

        ctrl = EyeballVertical_CONTROL3 & ((uint8 )(~EyeballVertical_CTRL_CMPMODE1_MASK));
        EyeballVertical_CONTROL3 = ctrl | EyeballVertical_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        EyeballVertical_RT1 &= ((uint8)(~EyeballVertical_RT1_MASK));
        EyeballVertical_RT1 |= EyeballVertical_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        EyeballVertical_RT1 &= ((uint8)(~EyeballVertical_SYNCDSI_MASK));
        EyeballVertical_RT1 |= EyeballVertical_SYNCDSI_EN;

    #elif (EyeballVertical_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = EyeballVertical_CONTROL & ((uint8)(~EyeballVertical_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~EyeballVertical_CTRL_CMPMODE1_MASK));
        EyeballVertical_CONTROL = ctrl | EyeballVertical_DEFAULT_COMPARE2_MODE |
                                   EyeballVertical_DEFAULT_COMPARE1_MODE;
    #endif /* (EyeballVertical_UsingFixedFunction) */

    #if (!EyeballVertical_UsingFixedFunction)
        #if (EyeballVertical_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            EyeballVertical_AUX_CONTROLDP0 |= (EyeballVertical_AUX_CTRL_FIFO0_CLR);
        #else /* (EyeballVertical_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            EyeballVertical_AUX_CONTROLDP0 |= (EyeballVertical_AUX_CTRL_FIFO0_CLR);
            EyeballVertical_AUX_CONTROLDP1 |= (EyeballVertical_AUX_CTRL_FIFO0_CLR);
        #endif /* (EyeballVertical_Resolution == 8) */

        EyeballVertical_WriteCounter(EyeballVertical_INIT_PERIOD_VALUE);
    #endif /* (!EyeballVertical_UsingFixedFunction) */

    EyeballVertical_WritePeriod(EyeballVertical_INIT_PERIOD_VALUE);

        #if (EyeballVertical_UseOneCompareMode)
            EyeballVertical_WriteCompare(EyeballVertical_INIT_COMPARE_VALUE1);
        #else
            EyeballVertical_WriteCompare1(EyeballVertical_INIT_COMPARE_VALUE1);
            EyeballVertical_WriteCompare2(EyeballVertical_INIT_COMPARE_VALUE2);
        #endif /* (EyeballVertical_UseOneCompareMode) */

        #if (EyeballVertical_KillModeMinTime)
            EyeballVertical_WriteKillTime(EyeballVertical_MinimumKillTime);
        #endif /* (EyeballVertical_KillModeMinTime) */

        #if (EyeballVertical_DeadBandUsed)
            EyeballVertical_WriteDeadTime(EyeballVertical_INIT_DEAD_TIME);
        #endif /* (EyeballVertical_DeadBandUsed) */

    #if (EyeballVertical_UseStatus || EyeballVertical_UsingFixedFunction)
        EyeballVertical_SetInterruptMode(EyeballVertical_INIT_INTERRUPTS_MODE);
    #endif /* (EyeballVertical_UseStatus || EyeballVertical_UsingFixedFunction) */

    #if (EyeballVertical_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        EyeballVertical_GLOBAL_ENABLE |= EyeballVertical_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        EyeballVertical_CONTROL2 |= EyeballVertical_CTRL2_IRQ_SEL;
    #else
        #if(EyeballVertical_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            EyeballVertical_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            EyeballVertical_STATUS_AUX_CTRL |= EyeballVertical_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(EyeballVertical_interruptState);

            /* Clear the FIFO to enable the EyeballVertical_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            EyeballVertical_ClearFIFO();
        #endif /* (EyeballVertical_UseStatus) */
    #endif /* (EyeballVertical_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeballVertical_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void EyeballVertical_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (EyeballVertical_UsingFixedFunction)
        EyeballVertical_GLOBAL_ENABLE |= EyeballVertical_BLOCK_EN_MASK;
        EyeballVertical_GLOBAL_STBY_ENABLE |= EyeballVertical_BLOCK_STBY_EN_MASK;
    #endif /* (EyeballVertical_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (EyeballVertical_UseControl || EyeballVertical_UsingFixedFunction)
        EyeballVertical_CONTROL |= EyeballVertical_CTRL_ENABLE;
    #endif /* (EyeballVertical_UseControl || EyeballVertical_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeballVertical_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void EyeballVertical_Stop(void) 
{
    #if (EyeballVertical_UseControl || EyeballVertical_UsingFixedFunction)
        EyeballVertical_CONTROL &= ((uint8)(~EyeballVertical_CTRL_ENABLE));
    #endif /* (EyeballVertical_UseControl || EyeballVertical_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (EyeballVertical_UsingFixedFunction)
        EyeballVertical_GLOBAL_ENABLE &= ((uint8)(~EyeballVertical_BLOCK_EN_MASK));
        EyeballVertical_GLOBAL_STBY_ENABLE &= ((uint8)(~EyeballVertical_BLOCK_STBY_EN_MASK));
    #endif /* (EyeballVertical_UsingFixedFunction) */
}

#if (EyeballVertical_UseOneCompareMode)
    #if (EyeballVertical_CompareMode1SW)


        /*******************************************************************************
        * Function Name: EyeballVertical_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void EyeballVertical_SetCompareMode(uint8 comparemode) 
        {
            #if(EyeballVertical_UsingFixedFunction)

                #if(0 != EyeballVertical_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyeballVertical_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != EyeballVertical_CTRL_CMPMODE1_SHIFT) */

                EyeballVertical_CONTROL3 &= ((uint8)(~EyeballVertical_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                EyeballVertical_CONTROL3 |= comparemodemasked;

            #elif (EyeballVertical_UseControl)

                #if(0 != EyeballVertical_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << EyeballVertical_CTRL_CMPMODE1_SHIFT)) &
                                                EyeballVertical_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & EyeballVertical_CTRL_CMPMODE1_MASK;
                #endif /* (0 != EyeballVertical_CTRL_CMPMODE1_SHIFT) */

                #if(0 != EyeballVertical_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << EyeballVertical_CTRL_CMPMODE2_SHIFT)) &
                                               EyeballVertical_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & EyeballVertical_CTRL_CMPMODE2_MASK;
                #endif /* (0 != EyeballVertical_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                EyeballVertical_CONTROL &= ((uint8)(~(EyeballVertical_CTRL_CMPMODE1_MASK |
                                            EyeballVertical_CTRL_CMPMODE2_MASK)));
                EyeballVertical_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (EyeballVertical_UsingFixedFunction) */
        }
    #endif /* EyeballVertical_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (EyeballVertical_CompareMode1SW)


        /*******************************************************************************
        * Function Name: EyeballVertical_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void EyeballVertical_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != EyeballVertical_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyeballVertical_CTRL_CMPMODE1_SHIFT)) &
                                           EyeballVertical_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & EyeballVertical_CTRL_CMPMODE1_MASK;
            #endif /* (0 != EyeballVertical_CTRL_CMPMODE1_SHIFT) */

            #if (EyeballVertical_UseControl)
                EyeballVertical_CONTROL &= ((uint8)(~EyeballVertical_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                EyeballVertical_CONTROL |= comparemodemasked;
            #endif /* (EyeballVertical_UseControl) */
        }
    #endif /* EyeballVertical_CompareMode1SW */

#if (EyeballVertical_CompareMode2SW)


    /*******************************************************************************
    * Function Name: EyeballVertical_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeballVertical_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != EyeballVertical_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyeballVertical_CTRL_CMPMODE2_SHIFT)) &
                                                 EyeballVertical_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & EyeballVertical_CTRL_CMPMODE2_MASK;
        #endif /* (0 != EyeballVertical_CTRL_CMPMODE2_SHIFT) */

        #if (EyeballVertical_UseControl)
            EyeballVertical_CONTROL &= ((uint8)(~EyeballVertical_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            EyeballVertical_CONTROL |= comparemodemasked;
        #endif /* (EyeballVertical_UseControl) */
    }
    #endif /*EyeballVertical_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!EyeballVertical_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyeballVertical_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void EyeballVertical_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(EyeballVertical_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 EyeballVertical_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(EyeballVertical_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(EyeballVertical_CAPTURE_LSB_PTR));
    }

    #if (EyeballVertical_UseStatus)


        /*******************************************************************************
        * Function Name: EyeballVertical_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void EyeballVertical_ClearFIFO(void) 
        {
            while(0u != (EyeballVertical_ReadStatusRegister() & EyeballVertical_STATUS_FIFONEMPTY))
            {
                (void)EyeballVertical_ReadCapture();
            }
        }

    #endif /* EyeballVertical_UseStatus */

#endif /* !EyeballVertical_UsingFixedFunction */


/*******************************************************************************
* Function Name: EyeballVertical_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void EyeballVertical_WritePeriod(uint16 period) 
{
    #if(EyeballVertical_UsingFixedFunction)
        CY_SET_REG16(EyeballVertical_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(EyeballVertical_PERIOD_LSB_PTR, period);
    #endif /* (EyeballVertical_UsingFixedFunction) */
}

#if (EyeballVertical_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: EyeballVertical_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void EyeballVertical_WriteCompare(uint16 compare) \
                                       
    {
        #if(EyeballVertical_UsingFixedFunction)
            CY_SET_REG16(EyeballVertical_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(EyeballVertical_COMPARE1_LSB_PTR, compare);
        #endif /* (EyeballVertical_UsingFixedFunction) */

        #if (EyeballVertical_PWMMode == EyeballVertical__B_PWM__DITHER)
            #if(EyeballVertical_UsingFixedFunction)
                CY_SET_REG16(EyeballVertical_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(EyeballVertical_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (EyeballVertical_UsingFixedFunction) */
        #endif /* (EyeballVertical_PWMMode == EyeballVertical__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: EyeballVertical_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeballVertical_WriteCompare1(uint16 compare) \
                                        
    {
        #if(EyeballVertical_UsingFixedFunction)
            CY_SET_REG16(EyeballVertical_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(EyeballVertical_COMPARE1_LSB_PTR, compare);
        #endif /* (EyeballVertical_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: EyeballVertical_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeballVertical_WriteCompare2(uint16 compare) \
                                        
    {
        #if(EyeballVertical_UsingFixedFunction)
            CY_SET_REG16(EyeballVertical_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(EyeballVertical_COMPARE2_LSB_PTR, compare);
        #endif /* (EyeballVertical_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (EyeballVertical_DeadBandUsed)


    /*******************************************************************************
    * Function Name: EyeballVertical_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeballVertical_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!EyeballVertical_DeadBand2_4)
            CY_SET_REG8(EyeballVertical_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            EyeballVertical_DEADBAND_COUNT &= ((uint8)(~EyeballVertical_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(EyeballVertical_DEADBAND_COUNT_SHIFT)
                EyeballVertical_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << EyeballVertical_DEADBAND_COUNT_SHIFT)) &
                                                    EyeballVertical_DEADBAND_COUNT_MASK;
            #else
                EyeballVertical_DEADBAND_COUNT |= deadtime & EyeballVertical_DEADBAND_COUNT_MASK;
            #endif /* (EyeballVertical_DEADBAND_COUNT_SHIFT) */

        #endif /* (!EyeballVertical_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 EyeballVertical_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!EyeballVertical_DeadBand2_4)
            return (CY_GET_REG8(EyeballVertical_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(EyeballVertical_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(EyeballVertical_DEADBAND_COUNT & EyeballVertical_DEADBAND_COUNT_MASK)) >>
                                                                           EyeballVertical_DEADBAND_COUNT_SHIFT));
            #else
                return (EyeballVertical_DEADBAND_COUNT & EyeballVertical_DEADBAND_COUNT_MASK);
            #endif /* (EyeballVertical_DEADBAND_COUNT_SHIFT) */
        #endif /* (!EyeballVertical_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (EyeballVertical_UseStatus || EyeballVertical_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyeballVertical_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeballVertical_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(EyeballVertical_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 EyeballVertical_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(EyeballVertical_STATUS_PTR));
    }

#endif /* (EyeballVertical_UseStatus || EyeballVertical_UsingFixedFunction) */


#if (EyeballVertical_UseControl)


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 EyeballVertical_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(EyeballVertical_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: EyeballVertical_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeballVertical_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(EyeballVertical_CONTROL_PTR, control);
    }

#endif /* (EyeballVertical_UseControl) */


#if (!EyeballVertical_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 EyeballVertical_ReadCapture(void) 
    {
        return (CY_GET_REG16(EyeballVertical_CAPTURE_LSB_PTR));
    }

#endif /* (!EyeballVertical_UsingFixedFunction) */


#if (EyeballVertical_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 EyeballVertical_ReadCompare(void) 
    {
        #if(EyeballVertical_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(EyeballVertical_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(EyeballVertical_COMPARE1_LSB_PTR));
        #endif /* (EyeballVertical_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 EyeballVertical_ReadCompare1(void) 
    {
        return (CY_GET_REG16(EyeballVertical_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 EyeballVertical_ReadCompare2(void) 
    {
        return (CY_GET_REG16(EyeballVertical_COMPARE2_LSB_PTR));
    }

#endif /* (EyeballVertical_UseOneCompareMode) */


/*******************************************************************************
* Function Name: EyeballVertical_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 EyeballVertical_ReadPeriod(void) 
{
    #if(EyeballVertical_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(EyeballVertical_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(EyeballVertical_PERIOD_LSB_PTR));
    #endif /* (EyeballVertical_UsingFixedFunction) */
}

#if ( EyeballVertical_KillModeMinTime)


    /*******************************************************************************
    * Function Name: EyeballVertical_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeballVertical_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(EyeballVertical_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: EyeballVertical_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 EyeballVertical_ReadKillTime(void) 
    {
        return (CY_GET_REG8(EyeballVertical_KILLMODEMINTIME_PTR));
    }

#endif /* ( EyeballVertical_KillModeMinTime) */

/* [] END OF FILE */
