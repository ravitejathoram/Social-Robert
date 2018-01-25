/*******************************************************************************
* File Name: Lips.c
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

#include "Lips.h"

/* Error message for removed <resource> through optimization */
#ifdef Lips_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* Lips_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 Lips_initVar = 0u;


/*******************************************************************************
* Function Name: Lips_Start
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
*  Lips_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Lips_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Lips_initVar == 0u)
    {
        Lips_Init();
        Lips_initVar = 1u;
    }
    Lips_Enable();

}


/*******************************************************************************
* Function Name: Lips_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Lips_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Lips_Init(void) 
{
    #if (Lips_UsingFixedFunction || Lips_UseControl)
        uint8 ctrl;
    #endif /* (Lips_UsingFixedFunction || Lips_UseControl) */

    #if(!Lips_UsingFixedFunction)
        #if(Lips_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 Lips_interruptState;
        #endif /* (Lips_UseStatus) */
    #endif /* (!Lips_UsingFixedFunction) */

    #if (Lips_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        Lips_CONTROL |= Lips_CFG0_MODE;
        #if (Lips_DeadBand2_4)
            Lips_CONTROL |= Lips_CFG0_DB;
        #endif /* (Lips_DeadBand2_4) */

        ctrl = Lips_CONTROL3 & ((uint8 )(~Lips_CTRL_CMPMODE1_MASK));
        Lips_CONTROL3 = ctrl | Lips_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Lips_RT1 &= ((uint8)(~Lips_RT1_MASK));
        Lips_RT1 |= Lips_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        Lips_RT1 &= ((uint8)(~Lips_SYNCDSI_MASK));
        Lips_RT1 |= Lips_SYNCDSI_EN;

    #elif (Lips_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = Lips_CONTROL & ((uint8)(~Lips_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~Lips_CTRL_CMPMODE1_MASK));
        Lips_CONTROL = ctrl | Lips_DEFAULT_COMPARE2_MODE |
                                   Lips_DEFAULT_COMPARE1_MODE;
    #endif /* (Lips_UsingFixedFunction) */

    #if (!Lips_UsingFixedFunction)
        #if (Lips_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            Lips_AUX_CONTROLDP0 |= (Lips_AUX_CTRL_FIFO0_CLR);
        #else /* (Lips_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            Lips_AUX_CONTROLDP0 |= (Lips_AUX_CTRL_FIFO0_CLR);
            Lips_AUX_CONTROLDP1 |= (Lips_AUX_CTRL_FIFO0_CLR);
        #endif /* (Lips_Resolution == 8) */

        Lips_WriteCounter(Lips_INIT_PERIOD_VALUE);
    #endif /* (!Lips_UsingFixedFunction) */

    Lips_WritePeriod(Lips_INIT_PERIOD_VALUE);

        #if (Lips_UseOneCompareMode)
            Lips_WriteCompare(Lips_INIT_COMPARE_VALUE1);
        #else
            Lips_WriteCompare1(Lips_INIT_COMPARE_VALUE1);
            Lips_WriteCompare2(Lips_INIT_COMPARE_VALUE2);
        #endif /* (Lips_UseOneCompareMode) */

        #if (Lips_KillModeMinTime)
            Lips_WriteKillTime(Lips_MinimumKillTime);
        #endif /* (Lips_KillModeMinTime) */

        #if (Lips_DeadBandUsed)
            Lips_WriteDeadTime(Lips_INIT_DEAD_TIME);
        #endif /* (Lips_DeadBandUsed) */

    #if (Lips_UseStatus || Lips_UsingFixedFunction)
        Lips_SetInterruptMode(Lips_INIT_INTERRUPTS_MODE);
    #endif /* (Lips_UseStatus || Lips_UsingFixedFunction) */

    #if (Lips_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        Lips_GLOBAL_ENABLE |= Lips_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        Lips_CONTROL2 |= Lips_CTRL2_IRQ_SEL;
    #else
        #if(Lips_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Lips_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Lips_STATUS_AUX_CTRL |= Lips_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(Lips_interruptState);

            /* Clear the FIFO to enable the Lips_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            Lips_ClearFIFO();
        #endif /* (Lips_UseStatus) */
    #endif /* (Lips_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Lips_Enable
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
void Lips_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Lips_UsingFixedFunction)
        Lips_GLOBAL_ENABLE |= Lips_BLOCK_EN_MASK;
        Lips_GLOBAL_STBY_ENABLE |= Lips_BLOCK_STBY_EN_MASK;
    #endif /* (Lips_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (Lips_UseControl || Lips_UsingFixedFunction)
        Lips_CONTROL |= Lips_CTRL_ENABLE;
    #endif /* (Lips_UseControl || Lips_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Lips_Stop
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
void Lips_Stop(void) 
{
    #if (Lips_UseControl || Lips_UsingFixedFunction)
        Lips_CONTROL &= ((uint8)(~Lips_CTRL_ENABLE));
    #endif /* (Lips_UseControl || Lips_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (Lips_UsingFixedFunction)
        Lips_GLOBAL_ENABLE &= ((uint8)(~Lips_BLOCK_EN_MASK));
        Lips_GLOBAL_STBY_ENABLE &= ((uint8)(~Lips_BLOCK_STBY_EN_MASK));
    #endif /* (Lips_UsingFixedFunction) */
}

#if (Lips_UseOneCompareMode)
    #if (Lips_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Lips_SetCompareMode
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
        void Lips_SetCompareMode(uint8 comparemode) 
        {
            #if(Lips_UsingFixedFunction)

                #if(0 != Lips_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << Lips_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != Lips_CTRL_CMPMODE1_SHIFT) */

                Lips_CONTROL3 &= ((uint8)(~Lips_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                Lips_CONTROL3 |= comparemodemasked;

            #elif (Lips_UseControl)

                #if(0 != Lips_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << Lips_CTRL_CMPMODE1_SHIFT)) &
                                                Lips_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & Lips_CTRL_CMPMODE1_MASK;
                #endif /* (0 != Lips_CTRL_CMPMODE1_SHIFT) */

                #if(0 != Lips_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << Lips_CTRL_CMPMODE2_SHIFT)) &
                                               Lips_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & Lips_CTRL_CMPMODE2_MASK;
                #endif /* (0 != Lips_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                Lips_CONTROL &= ((uint8)(~(Lips_CTRL_CMPMODE1_MASK |
                                            Lips_CTRL_CMPMODE2_MASK)));
                Lips_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (Lips_UsingFixedFunction) */
        }
    #endif /* Lips_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (Lips_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Lips_SetCompareMode1
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
        void Lips_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != Lips_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << Lips_CTRL_CMPMODE1_SHIFT)) &
                                           Lips_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & Lips_CTRL_CMPMODE1_MASK;
            #endif /* (0 != Lips_CTRL_CMPMODE1_SHIFT) */

            #if (Lips_UseControl)
                Lips_CONTROL &= ((uint8)(~Lips_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                Lips_CONTROL |= comparemodemasked;
            #endif /* (Lips_UseControl) */
        }
    #endif /* Lips_CompareMode1SW */

#if (Lips_CompareMode2SW)


    /*******************************************************************************
    * Function Name: Lips_SetCompareMode2
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
    void Lips_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != Lips_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << Lips_CTRL_CMPMODE2_SHIFT)) &
                                                 Lips_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & Lips_CTRL_CMPMODE2_MASK;
        #endif /* (0 != Lips_CTRL_CMPMODE2_SHIFT) */

        #if (Lips_UseControl)
            Lips_CONTROL &= ((uint8)(~Lips_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            Lips_CONTROL |= comparemodemasked;
        #endif /* (Lips_UseControl) */
    }
    #endif /*Lips_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!Lips_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Lips_WriteCounter
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
    void Lips_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(Lips_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: Lips_ReadCounter
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
    uint16 Lips_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(Lips_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(Lips_CAPTURE_LSB_PTR));
    }

    #if (Lips_UseStatus)


        /*******************************************************************************
        * Function Name: Lips_ClearFIFO
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
        void Lips_ClearFIFO(void) 
        {
            while(0u != (Lips_ReadStatusRegister() & Lips_STATUS_FIFONEMPTY))
            {
                (void)Lips_ReadCapture();
            }
        }

    #endif /* Lips_UseStatus */

#endif /* !Lips_UsingFixedFunction */


/*******************************************************************************
* Function Name: Lips_WritePeriod
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
void Lips_WritePeriod(uint16 period) 
{
    #if(Lips_UsingFixedFunction)
        CY_SET_REG16(Lips_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(Lips_PERIOD_LSB_PTR, period);
    #endif /* (Lips_UsingFixedFunction) */
}

#if (Lips_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Lips_WriteCompare
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
    void Lips_WriteCompare(uint16 compare) \
                                       
    {
        #if(Lips_UsingFixedFunction)
            CY_SET_REG16(Lips_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Lips_COMPARE1_LSB_PTR, compare);
        #endif /* (Lips_UsingFixedFunction) */

        #if (Lips_PWMMode == Lips__B_PWM__DITHER)
            #if(Lips_UsingFixedFunction)
                CY_SET_REG16(Lips_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(Lips_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (Lips_UsingFixedFunction) */
        #endif /* (Lips_PWMMode == Lips__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: Lips_WriteCompare1
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
    void Lips_WriteCompare1(uint16 compare) \
                                        
    {
        #if(Lips_UsingFixedFunction)
            CY_SET_REG16(Lips_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Lips_COMPARE1_LSB_PTR, compare);
        #endif /* (Lips_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: Lips_WriteCompare2
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
    void Lips_WriteCompare2(uint16 compare) \
                                        
    {
        #if(Lips_UsingFixedFunction)
            CY_SET_REG16(Lips_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(Lips_COMPARE2_LSB_PTR, compare);
        #endif /* (Lips_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (Lips_DeadBandUsed)


    /*******************************************************************************
    * Function Name: Lips_WriteDeadTime
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
    void Lips_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!Lips_DeadBand2_4)
            CY_SET_REG8(Lips_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            Lips_DEADBAND_COUNT &= ((uint8)(~Lips_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(Lips_DEADBAND_COUNT_SHIFT)
                Lips_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << Lips_DEADBAND_COUNT_SHIFT)) &
                                                    Lips_DEADBAND_COUNT_MASK;
            #else
                Lips_DEADBAND_COUNT |= deadtime & Lips_DEADBAND_COUNT_MASK;
            #endif /* (Lips_DEADBAND_COUNT_SHIFT) */

        #endif /* (!Lips_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: Lips_ReadDeadTime
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
    uint8 Lips_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!Lips_DeadBand2_4)
            return (CY_GET_REG8(Lips_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(Lips_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(Lips_DEADBAND_COUNT & Lips_DEADBAND_COUNT_MASK)) >>
                                                                           Lips_DEADBAND_COUNT_SHIFT));
            #else
                return (Lips_DEADBAND_COUNT & Lips_DEADBAND_COUNT_MASK);
            #endif /* (Lips_DEADBAND_COUNT_SHIFT) */
        #endif /* (!Lips_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (Lips_UseStatus || Lips_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Lips_SetInterruptMode
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
    void Lips_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(Lips_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: Lips_ReadStatusRegister
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
    uint8 Lips_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(Lips_STATUS_PTR));
    }

#endif /* (Lips_UseStatus || Lips_UsingFixedFunction) */


#if (Lips_UseControl)


    /*******************************************************************************
    * Function Name: Lips_ReadControlRegister
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
    uint8 Lips_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(Lips_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: Lips_WriteControlRegister
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
    void Lips_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(Lips_CONTROL_PTR, control);
    }

#endif /* (Lips_UseControl) */


#if (!Lips_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Lips_ReadCapture
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
    uint16 Lips_ReadCapture(void) 
    {
        return (CY_GET_REG16(Lips_CAPTURE_LSB_PTR));
    }

#endif /* (!Lips_UsingFixedFunction) */


#if (Lips_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Lips_ReadCompare
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
    uint16 Lips_ReadCompare(void) 
    {
        #if(Lips_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(Lips_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(Lips_COMPARE1_LSB_PTR));
        #endif /* (Lips_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: Lips_ReadCompare1
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
    uint16 Lips_ReadCompare1(void) 
    {
        return (CY_GET_REG16(Lips_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: Lips_ReadCompare2
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
    uint16 Lips_ReadCompare2(void) 
    {
        return (CY_GET_REG16(Lips_COMPARE2_LSB_PTR));
    }

#endif /* (Lips_UseOneCompareMode) */


/*******************************************************************************
* Function Name: Lips_ReadPeriod
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
uint16 Lips_ReadPeriod(void) 
{
    #if(Lips_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Lips_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Lips_PERIOD_LSB_PTR));
    #endif /* (Lips_UsingFixedFunction) */
}

#if ( Lips_KillModeMinTime)


    /*******************************************************************************
    * Function Name: Lips_WriteKillTime
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
    void Lips_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(Lips_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: Lips_ReadKillTime
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
    uint8 Lips_ReadKillTime(void) 
    {
        return (CY_GET_REG8(Lips_KILLMODEMINTIME_PTR));
    }

#endif /* ( Lips_KillModeMinTime) */

/* [] END OF FILE */
