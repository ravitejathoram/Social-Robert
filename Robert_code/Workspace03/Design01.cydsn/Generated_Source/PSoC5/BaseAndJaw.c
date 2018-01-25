/*******************************************************************************
* File Name: BaseAndJaw.c
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

#include "BaseAndJaw.h"

/* Error message for removed <resource> through optimization */
#ifdef BaseAndJaw_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* BaseAndJaw_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 BaseAndJaw_initVar = 0u;


/*******************************************************************************
* Function Name: BaseAndJaw_Start
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
*  BaseAndJaw_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void BaseAndJaw_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(BaseAndJaw_initVar == 0u)
    {
        BaseAndJaw_Init();
        BaseAndJaw_initVar = 1u;
    }
    BaseAndJaw_Enable();

}


/*******************************************************************************
* Function Name: BaseAndJaw_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  BaseAndJaw_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BaseAndJaw_Init(void) 
{
    #if (BaseAndJaw_UsingFixedFunction || BaseAndJaw_UseControl)
        uint8 ctrl;
    #endif /* (BaseAndJaw_UsingFixedFunction || BaseAndJaw_UseControl) */

    #if(!BaseAndJaw_UsingFixedFunction)
        #if(BaseAndJaw_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 BaseAndJaw_interruptState;
        #endif /* (BaseAndJaw_UseStatus) */
    #endif /* (!BaseAndJaw_UsingFixedFunction) */

    #if (BaseAndJaw_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        BaseAndJaw_CONTROL |= BaseAndJaw_CFG0_MODE;
        #if (BaseAndJaw_DeadBand2_4)
            BaseAndJaw_CONTROL |= BaseAndJaw_CFG0_DB;
        #endif /* (BaseAndJaw_DeadBand2_4) */

        ctrl = BaseAndJaw_CONTROL3 & ((uint8 )(~BaseAndJaw_CTRL_CMPMODE1_MASK));
        BaseAndJaw_CONTROL3 = ctrl | BaseAndJaw_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        BaseAndJaw_RT1 &= ((uint8)(~BaseAndJaw_RT1_MASK));
        BaseAndJaw_RT1 |= BaseAndJaw_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        BaseAndJaw_RT1 &= ((uint8)(~BaseAndJaw_SYNCDSI_MASK));
        BaseAndJaw_RT1 |= BaseAndJaw_SYNCDSI_EN;

    #elif (BaseAndJaw_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = BaseAndJaw_CONTROL & ((uint8)(~BaseAndJaw_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~BaseAndJaw_CTRL_CMPMODE1_MASK));
        BaseAndJaw_CONTROL = ctrl | BaseAndJaw_DEFAULT_COMPARE2_MODE |
                                   BaseAndJaw_DEFAULT_COMPARE1_MODE;
    #endif /* (BaseAndJaw_UsingFixedFunction) */

    #if (!BaseAndJaw_UsingFixedFunction)
        #if (BaseAndJaw_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            BaseAndJaw_AUX_CONTROLDP0 |= (BaseAndJaw_AUX_CTRL_FIFO0_CLR);
        #else /* (BaseAndJaw_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            BaseAndJaw_AUX_CONTROLDP0 |= (BaseAndJaw_AUX_CTRL_FIFO0_CLR);
            BaseAndJaw_AUX_CONTROLDP1 |= (BaseAndJaw_AUX_CTRL_FIFO0_CLR);
        #endif /* (BaseAndJaw_Resolution == 8) */

        BaseAndJaw_WriteCounter(BaseAndJaw_INIT_PERIOD_VALUE);
    #endif /* (!BaseAndJaw_UsingFixedFunction) */

    BaseAndJaw_WritePeriod(BaseAndJaw_INIT_PERIOD_VALUE);

        #if (BaseAndJaw_UseOneCompareMode)
            BaseAndJaw_WriteCompare(BaseAndJaw_INIT_COMPARE_VALUE1);
        #else
            BaseAndJaw_WriteCompare1(BaseAndJaw_INIT_COMPARE_VALUE1);
            BaseAndJaw_WriteCompare2(BaseAndJaw_INIT_COMPARE_VALUE2);
        #endif /* (BaseAndJaw_UseOneCompareMode) */

        #if (BaseAndJaw_KillModeMinTime)
            BaseAndJaw_WriteKillTime(BaseAndJaw_MinimumKillTime);
        #endif /* (BaseAndJaw_KillModeMinTime) */

        #if (BaseAndJaw_DeadBandUsed)
            BaseAndJaw_WriteDeadTime(BaseAndJaw_INIT_DEAD_TIME);
        #endif /* (BaseAndJaw_DeadBandUsed) */

    #if (BaseAndJaw_UseStatus || BaseAndJaw_UsingFixedFunction)
        BaseAndJaw_SetInterruptMode(BaseAndJaw_INIT_INTERRUPTS_MODE);
    #endif /* (BaseAndJaw_UseStatus || BaseAndJaw_UsingFixedFunction) */

    #if (BaseAndJaw_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        BaseAndJaw_GLOBAL_ENABLE |= BaseAndJaw_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        BaseAndJaw_CONTROL2 |= BaseAndJaw_CTRL2_IRQ_SEL;
    #else
        #if(BaseAndJaw_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            BaseAndJaw_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            BaseAndJaw_STATUS_AUX_CTRL |= BaseAndJaw_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(BaseAndJaw_interruptState);

            /* Clear the FIFO to enable the BaseAndJaw_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            BaseAndJaw_ClearFIFO();
        #endif /* (BaseAndJaw_UseStatus) */
    #endif /* (BaseAndJaw_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BaseAndJaw_Enable
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
void BaseAndJaw_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (BaseAndJaw_UsingFixedFunction)
        BaseAndJaw_GLOBAL_ENABLE |= BaseAndJaw_BLOCK_EN_MASK;
        BaseAndJaw_GLOBAL_STBY_ENABLE |= BaseAndJaw_BLOCK_STBY_EN_MASK;
    #endif /* (BaseAndJaw_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (BaseAndJaw_UseControl || BaseAndJaw_UsingFixedFunction)
        BaseAndJaw_CONTROL |= BaseAndJaw_CTRL_ENABLE;
    #endif /* (BaseAndJaw_UseControl || BaseAndJaw_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BaseAndJaw_Stop
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
void BaseAndJaw_Stop(void) 
{
    #if (BaseAndJaw_UseControl || BaseAndJaw_UsingFixedFunction)
        BaseAndJaw_CONTROL &= ((uint8)(~BaseAndJaw_CTRL_ENABLE));
    #endif /* (BaseAndJaw_UseControl || BaseAndJaw_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (BaseAndJaw_UsingFixedFunction)
        BaseAndJaw_GLOBAL_ENABLE &= ((uint8)(~BaseAndJaw_BLOCK_EN_MASK));
        BaseAndJaw_GLOBAL_STBY_ENABLE &= ((uint8)(~BaseAndJaw_BLOCK_STBY_EN_MASK));
    #endif /* (BaseAndJaw_UsingFixedFunction) */
}

#if (BaseAndJaw_UseOneCompareMode)
    #if (BaseAndJaw_CompareMode1SW)


        /*******************************************************************************
        * Function Name: BaseAndJaw_SetCompareMode
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
        void BaseAndJaw_SetCompareMode(uint8 comparemode) 
        {
            #if(BaseAndJaw_UsingFixedFunction)

                #if(0 != BaseAndJaw_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << BaseAndJaw_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != BaseAndJaw_CTRL_CMPMODE1_SHIFT) */

                BaseAndJaw_CONTROL3 &= ((uint8)(~BaseAndJaw_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                BaseAndJaw_CONTROL3 |= comparemodemasked;

            #elif (BaseAndJaw_UseControl)

                #if(0 != BaseAndJaw_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << BaseAndJaw_CTRL_CMPMODE1_SHIFT)) &
                                                BaseAndJaw_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & BaseAndJaw_CTRL_CMPMODE1_MASK;
                #endif /* (0 != BaseAndJaw_CTRL_CMPMODE1_SHIFT) */

                #if(0 != BaseAndJaw_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << BaseAndJaw_CTRL_CMPMODE2_SHIFT)) &
                                               BaseAndJaw_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & BaseAndJaw_CTRL_CMPMODE2_MASK;
                #endif /* (0 != BaseAndJaw_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                BaseAndJaw_CONTROL &= ((uint8)(~(BaseAndJaw_CTRL_CMPMODE1_MASK |
                                            BaseAndJaw_CTRL_CMPMODE2_MASK)));
                BaseAndJaw_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (BaseAndJaw_UsingFixedFunction) */
        }
    #endif /* BaseAndJaw_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (BaseAndJaw_CompareMode1SW)


        /*******************************************************************************
        * Function Name: BaseAndJaw_SetCompareMode1
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
        void BaseAndJaw_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != BaseAndJaw_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << BaseAndJaw_CTRL_CMPMODE1_SHIFT)) &
                                           BaseAndJaw_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & BaseAndJaw_CTRL_CMPMODE1_MASK;
            #endif /* (0 != BaseAndJaw_CTRL_CMPMODE1_SHIFT) */

            #if (BaseAndJaw_UseControl)
                BaseAndJaw_CONTROL &= ((uint8)(~BaseAndJaw_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                BaseAndJaw_CONTROL |= comparemodemasked;
            #endif /* (BaseAndJaw_UseControl) */
        }
    #endif /* BaseAndJaw_CompareMode1SW */

#if (BaseAndJaw_CompareMode2SW)


    /*******************************************************************************
    * Function Name: BaseAndJaw_SetCompareMode2
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
    void BaseAndJaw_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != BaseAndJaw_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << BaseAndJaw_CTRL_CMPMODE2_SHIFT)) &
                                                 BaseAndJaw_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & BaseAndJaw_CTRL_CMPMODE2_MASK;
        #endif /* (0 != BaseAndJaw_CTRL_CMPMODE2_SHIFT) */

        #if (BaseAndJaw_UseControl)
            BaseAndJaw_CONTROL &= ((uint8)(~BaseAndJaw_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            BaseAndJaw_CONTROL |= comparemodemasked;
        #endif /* (BaseAndJaw_UseControl) */
    }
    #endif /*BaseAndJaw_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!BaseAndJaw_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BaseAndJaw_WriteCounter
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
    void BaseAndJaw_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(BaseAndJaw_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadCounter
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
    uint16 BaseAndJaw_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(BaseAndJaw_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(BaseAndJaw_CAPTURE_LSB_PTR));
    }

    #if (BaseAndJaw_UseStatus)


        /*******************************************************************************
        * Function Name: BaseAndJaw_ClearFIFO
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
        void BaseAndJaw_ClearFIFO(void) 
        {
            while(0u != (BaseAndJaw_ReadStatusRegister() & BaseAndJaw_STATUS_FIFONEMPTY))
            {
                (void)BaseAndJaw_ReadCapture();
            }
        }

    #endif /* BaseAndJaw_UseStatus */

#endif /* !BaseAndJaw_UsingFixedFunction */


/*******************************************************************************
* Function Name: BaseAndJaw_WritePeriod
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
void BaseAndJaw_WritePeriod(uint16 period) 
{
    #if(BaseAndJaw_UsingFixedFunction)
        CY_SET_REG16(BaseAndJaw_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(BaseAndJaw_PERIOD_LSB_PTR, period);
    #endif /* (BaseAndJaw_UsingFixedFunction) */
}

#if (BaseAndJaw_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: BaseAndJaw_WriteCompare
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
    void BaseAndJaw_WriteCompare(uint16 compare) \
                                       
    {
        #if(BaseAndJaw_UsingFixedFunction)
            CY_SET_REG16(BaseAndJaw_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(BaseAndJaw_COMPARE1_LSB_PTR, compare);
        #endif /* (BaseAndJaw_UsingFixedFunction) */

        #if (BaseAndJaw_PWMMode == BaseAndJaw__B_PWM__DITHER)
            #if(BaseAndJaw_UsingFixedFunction)
                CY_SET_REG16(BaseAndJaw_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(BaseAndJaw_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (BaseAndJaw_UsingFixedFunction) */
        #endif /* (BaseAndJaw_PWMMode == BaseAndJaw__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: BaseAndJaw_WriteCompare1
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
    void BaseAndJaw_WriteCompare1(uint16 compare) \
                                        
    {
        #if(BaseAndJaw_UsingFixedFunction)
            CY_SET_REG16(BaseAndJaw_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(BaseAndJaw_COMPARE1_LSB_PTR, compare);
        #endif /* (BaseAndJaw_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: BaseAndJaw_WriteCompare2
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
    void BaseAndJaw_WriteCompare2(uint16 compare) \
                                        
    {
        #if(BaseAndJaw_UsingFixedFunction)
            CY_SET_REG16(BaseAndJaw_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(BaseAndJaw_COMPARE2_LSB_PTR, compare);
        #endif /* (BaseAndJaw_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (BaseAndJaw_DeadBandUsed)


    /*******************************************************************************
    * Function Name: BaseAndJaw_WriteDeadTime
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
    void BaseAndJaw_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!BaseAndJaw_DeadBand2_4)
            CY_SET_REG8(BaseAndJaw_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            BaseAndJaw_DEADBAND_COUNT &= ((uint8)(~BaseAndJaw_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(BaseAndJaw_DEADBAND_COUNT_SHIFT)
                BaseAndJaw_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << BaseAndJaw_DEADBAND_COUNT_SHIFT)) &
                                                    BaseAndJaw_DEADBAND_COUNT_MASK;
            #else
                BaseAndJaw_DEADBAND_COUNT |= deadtime & BaseAndJaw_DEADBAND_COUNT_MASK;
            #endif /* (BaseAndJaw_DEADBAND_COUNT_SHIFT) */

        #endif /* (!BaseAndJaw_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadDeadTime
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
    uint8 BaseAndJaw_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!BaseAndJaw_DeadBand2_4)
            return (CY_GET_REG8(BaseAndJaw_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(BaseAndJaw_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(BaseAndJaw_DEADBAND_COUNT & BaseAndJaw_DEADBAND_COUNT_MASK)) >>
                                                                           BaseAndJaw_DEADBAND_COUNT_SHIFT));
            #else
                return (BaseAndJaw_DEADBAND_COUNT & BaseAndJaw_DEADBAND_COUNT_MASK);
            #endif /* (BaseAndJaw_DEADBAND_COUNT_SHIFT) */
        #endif /* (!BaseAndJaw_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (BaseAndJaw_UseStatus || BaseAndJaw_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BaseAndJaw_SetInterruptMode
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
    void BaseAndJaw_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(BaseAndJaw_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadStatusRegister
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
    uint8 BaseAndJaw_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(BaseAndJaw_STATUS_PTR));
    }

#endif /* (BaseAndJaw_UseStatus || BaseAndJaw_UsingFixedFunction) */


#if (BaseAndJaw_UseControl)


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadControlRegister
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
    uint8 BaseAndJaw_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(BaseAndJaw_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: BaseAndJaw_WriteControlRegister
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
    void BaseAndJaw_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(BaseAndJaw_CONTROL_PTR, control);
    }

#endif /* (BaseAndJaw_UseControl) */


#if (!BaseAndJaw_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadCapture
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
    uint16 BaseAndJaw_ReadCapture(void) 
    {
        return (CY_GET_REG16(BaseAndJaw_CAPTURE_LSB_PTR));
    }

#endif /* (!BaseAndJaw_UsingFixedFunction) */


#if (BaseAndJaw_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadCompare
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
    uint16 BaseAndJaw_ReadCompare(void) 
    {
        #if(BaseAndJaw_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(BaseAndJaw_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(BaseAndJaw_COMPARE1_LSB_PTR));
        #endif /* (BaseAndJaw_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadCompare1
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
    uint16 BaseAndJaw_ReadCompare1(void) 
    {
        return (CY_GET_REG16(BaseAndJaw_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadCompare2
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
    uint16 BaseAndJaw_ReadCompare2(void) 
    {
        return (CY_GET_REG16(BaseAndJaw_COMPARE2_LSB_PTR));
    }

#endif /* (BaseAndJaw_UseOneCompareMode) */


/*******************************************************************************
* Function Name: BaseAndJaw_ReadPeriod
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
uint16 BaseAndJaw_ReadPeriod(void) 
{
    #if(BaseAndJaw_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(BaseAndJaw_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(BaseAndJaw_PERIOD_LSB_PTR));
    #endif /* (BaseAndJaw_UsingFixedFunction) */
}

#if ( BaseAndJaw_KillModeMinTime)


    /*******************************************************************************
    * Function Name: BaseAndJaw_WriteKillTime
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
    void BaseAndJaw_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(BaseAndJaw_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: BaseAndJaw_ReadKillTime
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
    uint8 BaseAndJaw_ReadKillTime(void) 
    {
        return (CY_GET_REG8(BaseAndJaw_KILLMODEMINTIME_PTR));
    }

#endif /* ( BaseAndJaw_KillModeMinTime) */

/* [] END OF FILE */
