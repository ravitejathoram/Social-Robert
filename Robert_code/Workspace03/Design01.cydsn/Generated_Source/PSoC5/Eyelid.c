/*******************************************************************************
* File Name: Eyelid.c
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

#include "Eyelid.h"

/* Error message for removed <resource> through optimization */
#ifdef Eyelid_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* Eyelid_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 Eyelid_initVar = 0u;


/*******************************************************************************
* Function Name: Eyelid_Start
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
*  Eyelid_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Eyelid_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Eyelid_initVar == 0u)
    {
        Eyelid_Init();
        Eyelid_initVar = 1u;
    }
    Eyelid_Enable();

}


/*******************************************************************************
* Function Name: Eyelid_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Eyelid_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Eyelid_Init(void) 
{
    #if (Eyelid_UsingFixedFunction || Eyelid_UseControl)
        uint8 ctrl;
    #endif /* (Eyelid_UsingFixedFunction || Eyelid_UseControl) */

    #if(!Eyelid_UsingFixedFunction)
        #if(Eyelid_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 Eyelid_interruptState;
        #endif /* (Eyelid_UseStatus) */
    #endif /* (!Eyelid_UsingFixedFunction) */

    #if (Eyelid_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        Eyelid_CONTROL |= Eyelid_CFG0_MODE;
        #if (Eyelid_DeadBand2_4)
            Eyelid_CONTROL |= Eyelid_CFG0_DB;
        #endif /* (Eyelid_DeadBand2_4) */

        ctrl = Eyelid_CONTROL3 & ((uint8 )(~Eyelid_CTRL_CMPMODE1_MASK));
        Eyelid_CONTROL3 = ctrl | Eyelid_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Eyelid_RT1 &= ((uint8)(~Eyelid_RT1_MASK));
        Eyelid_RT1 |= Eyelid_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        Eyelid_RT1 &= ((uint8)(~Eyelid_SYNCDSI_MASK));
        Eyelid_RT1 |= Eyelid_SYNCDSI_EN;

    #elif (Eyelid_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = Eyelid_CONTROL & ((uint8)(~Eyelid_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~Eyelid_CTRL_CMPMODE1_MASK));
        Eyelid_CONTROL = ctrl | Eyelid_DEFAULT_COMPARE2_MODE |
                                   Eyelid_DEFAULT_COMPARE1_MODE;
    #endif /* (Eyelid_UsingFixedFunction) */

    #if (!Eyelid_UsingFixedFunction)
        #if (Eyelid_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            Eyelid_AUX_CONTROLDP0 |= (Eyelid_AUX_CTRL_FIFO0_CLR);
        #else /* (Eyelid_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            Eyelid_AUX_CONTROLDP0 |= (Eyelid_AUX_CTRL_FIFO0_CLR);
            Eyelid_AUX_CONTROLDP1 |= (Eyelid_AUX_CTRL_FIFO0_CLR);
        #endif /* (Eyelid_Resolution == 8) */

        Eyelid_WriteCounter(Eyelid_INIT_PERIOD_VALUE);
    #endif /* (!Eyelid_UsingFixedFunction) */

    Eyelid_WritePeriod(Eyelid_INIT_PERIOD_VALUE);

        #if (Eyelid_UseOneCompareMode)
            Eyelid_WriteCompare(Eyelid_INIT_COMPARE_VALUE1);
        #else
            Eyelid_WriteCompare1(Eyelid_INIT_COMPARE_VALUE1);
            Eyelid_WriteCompare2(Eyelid_INIT_COMPARE_VALUE2);
        #endif /* (Eyelid_UseOneCompareMode) */

        #if (Eyelid_KillModeMinTime)
            Eyelid_WriteKillTime(Eyelid_MinimumKillTime);
        #endif /* (Eyelid_KillModeMinTime) */

        #if (Eyelid_DeadBandUsed)
            Eyelid_WriteDeadTime(Eyelid_INIT_DEAD_TIME);
        #endif /* (Eyelid_DeadBandUsed) */

    #if (Eyelid_UseStatus || Eyelid_UsingFixedFunction)
        Eyelid_SetInterruptMode(Eyelid_INIT_INTERRUPTS_MODE);
    #endif /* (Eyelid_UseStatus || Eyelid_UsingFixedFunction) */

    #if (Eyelid_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        Eyelid_GLOBAL_ENABLE |= Eyelid_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        Eyelid_CONTROL2 |= Eyelid_CTRL2_IRQ_SEL;
    #else
        #if(Eyelid_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Eyelid_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Eyelid_STATUS_AUX_CTRL |= Eyelid_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(Eyelid_interruptState);

            /* Clear the FIFO to enable the Eyelid_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            Eyelid_ClearFIFO();
        #endif /* (Eyelid_UseStatus) */
    #endif /* (Eyelid_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Eyelid_Enable
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
void Eyelid_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Eyelid_UsingFixedFunction)
        Eyelid_GLOBAL_ENABLE |= Eyelid_BLOCK_EN_MASK;
        Eyelid_GLOBAL_STBY_ENABLE |= Eyelid_BLOCK_STBY_EN_MASK;
    #endif /* (Eyelid_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (Eyelid_UseControl || Eyelid_UsingFixedFunction)
        Eyelid_CONTROL |= Eyelid_CTRL_ENABLE;
    #endif /* (Eyelid_UseControl || Eyelid_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Eyelid_Stop
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
void Eyelid_Stop(void) 
{
    #if (Eyelid_UseControl || Eyelid_UsingFixedFunction)
        Eyelid_CONTROL &= ((uint8)(~Eyelid_CTRL_ENABLE));
    #endif /* (Eyelid_UseControl || Eyelid_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (Eyelid_UsingFixedFunction)
        Eyelid_GLOBAL_ENABLE &= ((uint8)(~Eyelid_BLOCK_EN_MASK));
        Eyelid_GLOBAL_STBY_ENABLE &= ((uint8)(~Eyelid_BLOCK_STBY_EN_MASK));
    #endif /* (Eyelid_UsingFixedFunction) */
}

#if (Eyelid_UseOneCompareMode)
    #if (Eyelid_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Eyelid_SetCompareMode
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
        void Eyelid_SetCompareMode(uint8 comparemode) 
        {
            #if(Eyelid_UsingFixedFunction)

                #if(0 != Eyelid_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << Eyelid_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != Eyelid_CTRL_CMPMODE1_SHIFT) */

                Eyelid_CONTROL3 &= ((uint8)(~Eyelid_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                Eyelid_CONTROL3 |= comparemodemasked;

            #elif (Eyelid_UseControl)

                #if(0 != Eyelid_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << Eyelid_CTRL_CMPMODE1_SHIFT)) &
                                                Eyelid_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & Eyelid_CTRL_CMPMODE1_MASK;
                #endif /* (0 != Eyelid_CTRL_CMPMODE1_SHIFT) */

                #if(0 != Eyelid_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << Eyelid_CTRL_CMPMODE2_SHIFT)) &
                                               Eyelid_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & Eyelid_CTRL_CMPMODE2_MASK;
                #endif /* (0 != Eyelid_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                Eyelid_CONTROL &= ((uint8)(~(Eyelid_CTRL_CMPMODE1_MASK |
                                            Eyelid_CTRL_CMPMODE2_MASK)));
                Eyelid_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (Eyelid_UsingFixedFunction) */
        }
    #endif /* Eyelid_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (Eyelid_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Eyelid_SetCompareMode1
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
        void Eyelid_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != Eyelid_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << Eyelid_CTRL_CMPMODE1_SHIFT)) &
                                           Eyelid_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & Eyelid_CTRL_CMPMODE1_MASK;
            #endif /* (0 != Eyelid_CTRL_CMPMODE1_SHIFT) */

            #if (Eyelid_UseControl)
                Eyelid_CONTROL &= ((uint8)(~Eyelid_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                Eyelid_CONTROL |= comparemodemasked;
            #endif /* (Eyelid_UseControl) */
        }
    #endif /* Eyelid_CompareMode1SW */

#if (Eyelid_CompareMode2SW)


    /*******************************************************************************
    * Function Name: Eyelid_SetCompareMode2
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
    void Eyelid_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != Eyelid_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << Eyelid_CTRL_CMPMODE2_SHIFT)) &
                                                 Eyelid_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & Eyelid_CTRL_CMPMODE2_MASK;
        #endif /* (0 != Eyelid_CTRL_CMPMODE2_SHIFT) */

        #if (Eyelid_UseControl)
            Eyelid_CONTROL &= ((uint8)(~Eyelid_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            Eyelid_CONTROL |= comparemodemasked;
        #endif /* (Eyelid_UseControl) */
    }
    #endif /*Eyelid_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!Eyelid_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Eyelid_WriteCounter
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
    void Eyelid_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(Eyelid_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: Eyelid_ReadCounter
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
    uint16 Eyelid_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(Eyelid_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(Eyelid_CAPTURE_LSB_PTR));
    }

    #if (Eyelid_UseStatus)


        /*******************************************************************************
        * Function Name: Eyelid_ClearFIFO
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
        void Eyelid_ClearFIFO(void) 
        {
            while(0u != (Eyelid_ReadStatusRegister() & Eyelid_STATUS_FIFONEMPTY))
            {
                (void)Eyelid_ReadCapture();
            }
        }

    #endif /* Eyelid_UseStatus */

#endif /* !Eyelid_UsingFixedFunction */


/*******************************************************************************
* Function Name: Eyelid_WritePeriod
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
void Eyelid_WritePeriod(uint16 period) 
{
    #if(Eyelid_UsingFixedFunction)
        CY_SET_REG16(Eyelid_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(Eyelid_PERIOD_LSB_PTR, period);
    #endif /* (Eyelid_UsingFixedFunction) */
}

#if (Eyelid_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Eyelid_WriteCompare
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
    void Eyelid_WriteCompare(uint16 compare) \
                                       
    {
        #if(Eyelid_UsingFixedFunction)
            CY_SET_REG16(Eyelid_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Eyelid_COMPARE1_LSB_PTR, compare);
        #endif /* (Eyelid_UsingFixedFunction) */

        #if (Eyelid_PWMMode == Eyelid__B_PWM__DITHER)
            #if(Eyelid_UsingFixedFunction)
                CY_SET_REG16(Eyelid_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(Eyelid_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (Eyelid_UsingFixedFunction) */
        #endif /* (Eyelid_PWMMode == Eyelid__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: Eyelid_WriteCompare1
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
    void Eyelid_WriteCompare1(uint16 compare) \
                                        
    {
        #if(Eyelid_UsingFixedFunction)
            CY_SET_REG16(Eyelid_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Eyelid_COMPARE1_LSB_PTR, compare);
        #endif /* (Eyelid_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: Eyelid_WriteCompare2
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
    void Eyelid_WriteCompare2(uint16 compare) \
                                        
    {
        #if(Eyelid_UsingFixedFunction)
            CY_SET_REG16(Eyelid_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(Eyelid_COMPARE2_LSB_PTR, compare);
        #endif /* (Eyelid_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (Eyelid_DeadBandUsed)


    /*******************************************************************************
    * Function Name: Eyelid_WriteDeadTime
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
    void Eyelid_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!Eyelid_DeadBand2_4)
            CY_SET_REG8(Eyelid_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            Eyelid_DEADBAND_COUNT &= ((uint8)(~Eyelid_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(Eyelid_DEADBAND_COUNT_SHIFT)
                Eyelid_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << Eyelid_DEADBAND_COUNT_SHIFT)) &
                                                    Eyelid_DEADBAND_COUNT_MASK;
            #else
                Eyelid_DEADBAND_COUNT |= deadtime & Eyelid_DEADBAND_COUNT_MASK;
            #endif /* (Eyelid_DEADBAND_COUNT_SHIFT) */

        #endif /* (!Eyelid_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: Eyelid_ReadDeadTime
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
    uint8 Eyelid_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!Eyelid_DeadBand2_4)
            return (CY_GET_REG8(Eyelid_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(Eyelid_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(Eyelid_DEADBAND_COUNT & Eyelid_DEADBAND_COUNT_MASK)) >>
                                                                           Eyelid_DEADBAND_COUNT_SHIFT));
            #else
                return (Eyelid_DEADBAND_COUNT & Eyelid_DEADBAND_COUNT_MASK);
            #endif /* (Eyelid_DEADBAND_COUNT_SHIFT) */
        #endif /* (!Eyelid_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (Eyelid_UseStatus || Eyelid_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Eyelid_SetInterruptMode
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
    void Eyelid_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(Eyelid_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: Eyelid_ReadStatusRegister
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
    uint8 Eyelid_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(Eyelid_STATUS_PTR));
    }

#endif /* (Eyelid_UseStatus || Eyelid_UsingFixedFunction) */


#if (Eyelid_UseControl)


    /*******************************************************************************
    * Function Name: Eyelid_ReadControlRegister
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
    uint8 Eyelid_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(Eyelid_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: Eyelid_WriteControlRegister
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
    void Eyelid_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(Eyelid_CONTROL_PTR, control);
    }

#endif /* (Eyelid_UseControl) */


#if (!Eyelid_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Eyelid_ReadCapture
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
    uint16 Eyelid_ReadCapture(void) 
    {
        return (CY_GET_REG16(Eyelid_CAPTURE_LSB_PTR));
    }

#endif /* (!Eyelid_UsingFixedFunction) */


#if (Eyelid_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Eyelid_ReadCompare
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
    uint16 Eyelid_ReadCompare(void) 
    {
        #if(Eyelid_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(Eyelid_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(Eyelid_COMPARE1_LSB_PTR));
        #endif /* (Eyelid_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: Eyelid_ReadCompare1
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
    uint16 Eyelid_ReadCompare1(void) 
    {
        return (CY_GET_REG16(Eyelid_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: Eyelid_ReadCompare2
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
    uint16 Eyelid_ReadCompare2(void) 
    {
        return (CY_GET_REG16(Eyelid_COMPARE2_LSB_PTR));
    }

#endif /* (Eyelid_UseOneCompareMode) */


/*******************************************************************************
* Function Name: Eyelid_ReadPeriod
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
uint16 Eyelid_ReadPeriod(void) 
{
    #if(Eyelid_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Eyelid_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Eyelid_PERIOD_LSB_PTR));
    #endif /* (Eyelid_UsingFixedFunction) */
}

#if ( Eyelid_KillModeMinTime)


    /*******************************************************************************
    * Function Name: Eyelid_WriteKillTime
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
    void Eyelid_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(Eyelid_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: Eyelid_ReadKillTime
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
    uint8 Eyelid_ReadKillTime(void) 
    {
        return (CY_GET_REG8(Eyelid_KILLMODEMINTIME_PTR));
    }

#endif /* ( Eyelid_KillModeMinTime) */

/* [] END OF FILE */
