/*******************************************************************************
* File Name: Left_Eyeball_PM.c
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

#include "Left_Eyeball.h"

static Left_Eyeball_backupStruct Left_Eyeball_backup;


/*******************************************************************************
* Function Name: Left_Eyeball_SaveConfig
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
*  Left_Eyeball_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Left_Eyeball_SaveConfig(void) 
{

    #if(!Left_Eyeball_UsingFixedFunction)
        #if(!Left_Eyeball_PWMModeIsCenterAligned)
            Left_Eyeball_backup.PWMPeriod = Left_Eyeball_ReadPeriod();
        #endif /* (!Left_Eyeball_PWMModeIsCenterAligned) */
        Left_Eyeball_backup.PWMUdb = Left_Eyeball_ReadCounter();
        #if (Left_Eyeball_UseStatus)
            Left_Eyeball_backup.InterruptMaskValue = Left_Eyeball_STATUS_MASK;
        #endif /* (Left_Eyeball_UseStatus) */

        #if(Left_Eyeball_DeadBandMode == Left_Eyeball__B_PWM__DBM_256_CLOCKS || \
            Left_Eyeball_DeadBandMode == Left_Eyeball__B_PWM__DBM_2_4_CLOCKS)
            Left_Eyeball_backup.PWMdeadBandValue = Left_Eyeball_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Left_Eyeball_KillModeMinTime)
             Left_Eyeball_backup.PWMKillCounterPeriod = Left_Eyeball_ReadKillTime();
        #endif /* (Left_Eyeball_KillModeMinTime) */

        #if(Left_Eyeball_UseControl)
            Left_Eyeball_backup.PWMControlRegister = Left_Eyeball_ReadControlRegister();
        #endif /* (Left_Eyeball_UseControl) */
    #endif  /* (!Left_Eyeball_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Left_Eyeball_RestoreConfig
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
*  Left_Eyeball_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Left_Eyeball_RestoreConfig(void) 
{
        #if(!Left_Eyeball_UsingFixedFunction)
            #if(!Left_Eyeball_PWMModeIsCenterAligned)
                Left_Eyeball_WritePeriod(Left_Eyeball_backup.PWMPeriod);
            #endif /* (!Left_Eyeball_PWMModeIsCenterAligned) */

            Left_Eyeball_WriteCounter(Left_Eyeball_backup.PWMUdb);

            #if (Left_Eyeball_UseStatus)
                Left_Eyeball_STATUS_MASK = Left_Eyeball_backup.InterruptMaskValue;
            #endif /* (Left_Eyeball_UseStatus) */

            #if(Left_Eyeball_DeadBandMode == Left_Eyeball__B_PWM__DBM_256_CLOCKS || \
                Left_Eyeball_DeadBandMode == Left_Eyeball__B_PWM__DBM_2_4_CLOCKS)
                Left_Eyeball_WriteDeadTime(Left_Eyeball_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Left_Eyeball_KillModeMinTime)
                Left_Eyeball_WriteKillTime(Left_Eyeball_backup.PWMKillCounterPeriod);
            #endif /* (Left_Eyeball_KillModeMinTime) */

            #if(Left_Eyeball_UseControl)
                Left_Eyeball_WriteControlRegister(Left_Eyeball_backup.PWMControlRegister);
            #endif /* (Left_Eyeball_UseControl) */
        #endif  /* (!Left_Eyeball_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Left_Eyeball_Sleep
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
*  Left_Eyeball_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Left_Eyeball_Sleep(void) 
{
    #if(Left_Eyeball_UseControl)
        if(Left_Eyeball_CTRL_ENABLE == (Left_Eyeball_CONTROL & Left_Eyeball_CTRL_ENABLE))
        {
            /*Component is enabled */
            Left_Eyeball_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Left_Eyeball_backup.PWMEnableState = 0u;
        }
    #endif /* (Left_Eyeball_UseControl) */

    /* Stop component */
    Left_Eyeball_Stop();

    /* Save registers configuration */
    Left_Eyeball_SaveConfig();
}


/*******************************************************************************
* Function Name: Left_Eyeball_Wakeup
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
*  Left_Eyeball_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Left_Eyeball_Wakeup(void) 
{
     /* Restore registers values */
    Left_Eyeball_RestoreConfig();

    if(Left_Eyeball_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Left_Eyeball_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
