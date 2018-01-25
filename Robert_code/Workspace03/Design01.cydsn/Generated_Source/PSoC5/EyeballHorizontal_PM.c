/*******************************************************************************
* File Name: EyeballHorizontal_PM.c
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

#include "EyeballHorizontal.h"

static EyeballHorizontal_backupStruct EyeballHorizontal_backup;


/*******************************************************************************
* Function Name: EyeballHorizontal_SaveConfig
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
*  EyeballHorizontal_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EyeballHorizontal_SaveConfig(void) 
{

    #if(!EyeballHorizontal_UsingFixedFunction)
        #if(!EyeballHorizontal_PWMModeIsCenterAligned)
            EyeballHorizontal_backup.PWMPeriod = EyeballHorizontal_ReadPeriod();
        #endif /* (!EyeballHorizontal_PWMModeIsCenterAligned) */
        EyeballHorizontal_backup.PWMUdb = EyeballHorizontal_ReadCounter();
        #if (EyeballHorizontal_UseStatus)
            EyeballHorizontal_backup.InterruptMaskValue = EyeballHorizontal_STATUS_MASK;
        #endif /* (EyeballHorizontal_UseStatus) */

        #if(EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_256_CLOCKS || \
            EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_2_4_CLOCKS)
            EyeballHorizontal_backup.PWMdeadBandValue = EyeballHorizontal_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(EyeballHorizontal_KillModeMinTime)
             EyeballHorizontal_backup.PWMKillCounterPeriod = EyeballHorizontal_ReadKillTime();
        #endif /* (EyeballHorizontal_KillModeMinTime) */

        #if(EyeballHorizontal_UseControl)
            EyeballHorizontal_backup.PWMControlRegister = EyeballHorizontal_ReadControlRegister();
        #endif /* (EyeballHorizontal_UseControl) */
    #endif  /* (!EyeballHorizontal_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeballHorizontal_RestoreConfig
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
*  EyeballHorizontal_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EyeballHorizontal_RestoreConfig(void) 
{
        #if(!EyeballHorizontal_UsingFixedFunction)
            #if(!EyeballHorizontal_PWMModeIsCenterAligned)
                EyeballHorizontal_WritePeriod(EyeballHorizontal_backup.PWMPeriod);
            #endif /* (!EyeballHorizontal_PWMModeIsCenterAligned) */

            EyeballHorizontal_WriteCounter(EyeballHorizontal_backup.PWMUdb);

            #if (EyeballHorizontal_UseStatus)
                EyeballHorizontal_STATUS_MASK = EyeballHorizontal_backup.InterruptMaskValue;
            #endif /* (EyeballHorizontal_UseStatus) */

            #if(EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_256_CLOCKS || \
                EyeballHorizontal_DeadBandMode == EyeballHorizontal__B_PWM__DBM_2_4_CLOCKS)
                EyeballHorizontal_WriteDeadTime(EyeballHorizontal_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(EyeballHorizontal_KillModeMinTime)
                EyeballHorizontal_WriteKillTime(EyeballHorizontal_backup.PWMKillCounterPeriod);
            #endif /* (EyeballHorizontal_KillModeMinTime) */

            #if(EyeballHorizontal_UseControl)
                EyeballHorizontal_WriteControlRegister(EyeballHorizontal_backup.PWMControlRegister);
            #endif /* (EyeballHorizontal_UseControl) */
        #endif  /* (!EyeballHorizontal_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: EyeballHorizontal_Sleep
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
*  EyeballHorizontal_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void EyeballHorizontal_Sleep(void) 
{
    #if(EyeballHorizontal_UseControl)
        if(EyeballHorizontal_CTRL_ENABLE == (EyeballHorizontal_CONTROL & EyeballHorizontal_CTRL_ENABLE))
        {
            /*Component is enabled */
            EyeballHorizontal_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            EyeballHorizontal_backup.PWMEnableState = 0u;
        }
    #endif /* (EyeballHorizontal_UseControl) */

    /* Stop component */
    EyeballHorizontal_Stop();

    /* Save registers configuration */
    EyeballHorizontal_SaveConfig();
}


/*******************************************************************************
* Function Name: EyeballHorizontal_Wakeup
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
*  EyeballHorizontal_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EyeballHorizontal_Wakeup(void) 
{
     /* Restore registers values */
    EyeballHorizontal_RestoreConfig();

    if(EyeballHorizontal_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        EyeballHorizontal_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
