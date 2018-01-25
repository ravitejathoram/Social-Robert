/*******************************************************************************
* File Name: EyeballVertical_PM.c
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

#include "EyeballVertical.h"

static EyeballVertical_backupStruct EyeballVertical_backup;


/*******************************************************************************
* Function Name: EyeballVertical_SaveConfig
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
*  EyeballVertical_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EyeballVertical_SaveConfig(void) 
{

    #if(!EyeballVertical_UsingFixedFunction)
        #if(!EyeballVertical_PWMModeIsCenterAligned)
            EyeballVertical_backup.PWMPeriod = EyeballVertical_ReadPeriod();
        #endif /* (!EyeballVertical_PWMModeIsCenterAligned) */
        EyeballVertical_backup.PWMUdb = EyeballVertical_ReadCounter();
        #if (EyeballVertical_UseStatus)
            EyeballVertical_backup.InterruptMaskValue = EyeballVertical_STATUS_MASK;
        #endif /* (EyeballVertical_UseStatus) */

        #if(EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_256_CLOCKS || \
            EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_2_4_CLOCKS)
            EyeballVertical_backup.PWMdeadBandValue = EyeballVertical_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(EyeballVertical_KillModeMinTime)
             EyeballVertical_backup.PWMKillCounterPeriod = EyeballVertical_ReadKillTime();
        #endif /* (EyeballVertical_KillModeMinTime) */

        #if(EyeballVertical_UseControl)
            EyeballVertical_backup.PWMControlRegister = EyeballVertical_ReadControlRegister();
        #endif /* (EyeballVertical_UseControl) */
    #endif  /* (!EyeballVertical_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeballVertical_RestoreConfig
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
*  EyeballVertical_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EyeballVertical_RestoreConfig(void) 
{
        #if(!EyeballVertical_UsingFixedFunction)
            #if(!EyeballVertical_PWMModeIsCenterAligned)
                EyeballVertical_WritePeriod(EyeballVertical_backup.PWMPeriod);
            #endif /* (!EyeballVertical_PWMModeIsCenterAligned) */

            EyeballVertical_WriteCounter(EyeballVertical_backup.PWMUdb);

            #if (EyeballVertical_UseStatus)
                EyeballVertical_STATUS_MASK = EyeballVertical_backup.InterruptMaskValue;
            #endif /* (EyeballVertical_UseStatus) */

            #if(EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_256_CLOCKS || \
                EyeballVertical_DeadBandMode == EyeballVertical__B_PWM__DBM_2_4_CLOCKS)
                EyeballVertical_WriteDeadTime(EyeballVertical_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(EyeballVertical_KillModeMinTime)
                EyeballVertical_WriteKillTime(EyeballVertical_backup.PWMKillCounterPeriod);
            #endif /* (EyeballVertical_KillModeMinTime) */

            #if(EyeballVertical_UseControl)
                EyeballVertical_WriteControlRegister(EyeballVertical_backup.PWMControlRegister);
            #endif /* (EyeballVertical_UseControl) */
        #endif  /* (!EyeballVertical_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: EyeballVertical_Sleep
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
*  EyeballVertical_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void EyeballVertical_Sleep(void) 
{
    #if(EyeballVertical_UseControl)
        if(EyeballVertical_CTRL_ENABLE == (EyeballVertical_CONTROL & EyeballVertical_CTRL_ENABLE))
        {
            /*Component is enabled */
            EyeballVertical_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            EyeballVertical_backup.PWMEnableState = 0u;
        }
    #endif /* (EyeballVertical_UseControl) */

    /* Stop component */
    EyeballVertical_Stop();

    /* Save registers configuration */
    EyeballVertical_SaveConfig();
}


/*******************************************************************************
* Function Name: EyeballVertical_Wakeup
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
*  EyeballVertical_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EyeballVertical_Wakeup(void) 
{
     /* Restore registers values */
    EyeballVertical_RestoreConfig();

    if(EyeballVertical_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        EyeballVertical_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
