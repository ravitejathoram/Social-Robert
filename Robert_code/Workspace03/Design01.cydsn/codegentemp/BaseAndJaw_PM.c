/*******************************************************************************
* File Name: BaseAndJaw_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BaseAndJaw.h"

static BaseAndJaw_backupStruct BaseAndJaw_backup;


/*******************************************************************************
* Function Name: BaseAndJaw_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BaseAndJaw_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BaseAndJaw_SaveConfig(void) 
{

    #if(!BaseAndJaw_UsingFixedFunction)
        #if(!BaseAndJaw_PWMModeIsCenterAligned)
            BaseAndJaw_backup.PWMPeriod = BaseAndJaw_ReadPeriod();
        #endif /* (!BaseAndJaw_PWMModeIsCenterAligned) */
        BaseAndJaw_backup.PWMUdb = BaseAndJaw_ReadCounter();
        #if (BaseAndJaw_UseStatus)
            BaseAndJaw_backup.InterruptMaskValue = BaseAndJaw_STATUS_MASK;
        #endif /* (BaseAndJaw_UseStatus) */

        #if(BaseAndJaw_DeadBandMode == BaseAndJaw__B_PWM__DBM_256_CLOCKS || \
            BaseAndJaw_DeadBandMode == BaseAndJaw__B_PWM__DBM_2_4_CLOCKS)
            BaseAndJaw_backup.PWMdeadBandValue = BaseAndJaw_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BaseAndJaw_KillModeMinTime)
             BaseAndJaw_backup.PWMKillCounterPeriod = BaseAndJaw_ReadKillTime();
        #endif /* (BaseAndJaw_KillModeMinTime) */

        #if(BaseAndJaw_UseControl)
            BaseAndJaw_backup.PWMControlRegister = BaseAndJaw_ReadControlRegister();
        #endif /* (BaseAndJaw_UseControl) */
    #endif  /* (!BaseAndJaw_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BaseAndJaw_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BaseAndJaw_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BaseAndJaw_RestoreConfig(void) 
{
        #if(!BaseAndJaw_UsingFixedFunction)
            #if(!BaseAndJaw_PWMModeIsCenterAligned)
                BaseAndJaw_WritePeriod(BaseAndJaw_backup.PWMPeriod);
            #endif /* (!BaseAndJaw_PWMModeIsCenterAligned) */

            BaseAndJaw_WriteCounter(BaseAndJaw_backup.PWMUdb);

            #if (BaseAndJaw_UseStatus)
                BaseAndJaw_STATUS_MASK = BaseAndJaw_backup.InterruptMaskValue;
            #endif /* (BaseAndJaw_UseStatus) */

            #if(BaseAndJaw_DeadBandMode == BaseAndJaw__B_PWM__DBM_256_CLOCKS || \
                BaseAndJaw_DeadBandMode == BaseAndJaw__B_PWM__DBM_2_4_CLOCKS)
                BaseAndJaw_WriteDeadTime(BaseAndJaw_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BaseAndJaw_KillModeMinTime)
                BaseAndJaw_WriteKillTime(BaseAndJaw_backup.PWMKillCounterPeriod);
            #endif /* (BaseAndJaw_KillModeMinTime) */

            #if(BaseAndJaw_UseControl)
                BaseAndJaw_WriteControlRegister(BaseAndJaw_backup.PWMControlRegister);
            #endif /* (BaseAndJaw_UseControl) */
        #endif  /* (!BaseAndJaw_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BaseAndJaw_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BaseAndJaw_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BaseAndJaw_Sleep(void) 
{
    #if(BaseAndJaw_UseControl)
        if(BaseAndJaw_CTRL_ENABLE == (BaseAndJaw_CONTROL & BaseAndJaw_CTRL_ENABLE))
        {
            /*Component is enabled */
            BaseAndJaw_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BaseAndJaw_backup.PWMEnableState = 0u;
        }
    #endif /* (BaseAndJaw_UseControl) */

    /* Stop component */
    BaseAndJaw_Stop();

    /* Save registers configuration */
    BaseAndJaw_SaveConfig();
}


/*******************************************************************************
* Function Name: BaseAndJaw_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BaseAndJaw_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BaseAndJaw_Wakeup(void) 
{
     /* Restore registers values */
    BaseAndJaw_RestoreConfig();

    if(BaseAndJaw_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BaseAndJaw_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
