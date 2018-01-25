/*******************************************************************************
* File Name: Eyelid_PM.c
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

#include "Eyelid.h"

static Eyelid_backupStruct Eyelid_backup;


/*******************************************************************************
* Function Name: Eyelid_SaveConfig
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
*  Eyelid_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Eyelid_SaveConfig(void) 
{

    #if(!Eyelid_UsingFixedFunction)
        #if(!Eyelid_PWMModeIsCenterAligned)
            Eyelid_backup.PWMPeriod = Eyelid_ReadPeriod();
        #endif /* (!Eyelid_PWMModeIsCenterAligned) */
        Eyelid_backup.PWMUdb = Eyelid_ReadCounter();
        #if (Eyelid_UseStatus)
            Eyelid_backup.InterruptMaskValue = Eyelid_STATUS_MASK;
        #endif /* (Eyelid_UseStatus) */

        #if(Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_256_CLOCKS || \
            Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_2_4_CLOCKS)
            Eyelid_backup.PWMdeadBandValue = Eyelid_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Eyelid_KillModeMinTime)
             Eyelid_backup.PWMKillCounterPeriod = Eyelid_ReadKillTime();
        #endif /* (Eyelid_KillModeMinTime) */

        #if(Eyelid_UseControl)
            Eyelid_backup.PWMControlRegister = Eyelid_ReadControlRegister();
        #endif /* (Eyelid_UseControl) */
    #endif  /* (!Eyelid_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Eyelid_RestoreConfig
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
*  Eyelid_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Eyelid_RestoreConfig(void) 
{
        #if(!Eyelid_UsingFixedFunction)
            #if(!Eyelid_PWMModeIsCenterAligned)
                Eyelid_WritePeriod(Eyelid_backup.PWMPeriod);
            #endif /* (!Eyelid_PWMModeIsCenterAligned) */

            Eyelid_WriteCounter(Eyelid_backup.PWMUdb);

            #if (Eyelid_UseStatus)
                Eyelid_STATUS_MASK = Eyelid_backup.InterruptMaskValue;
            #endif /* (Eyelid_UseStatus) */

            #if(Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_256_CLOCKS || \
                Eyelid_DeadBandMode == Eyelid__B_PWM__DBM_2_4_CLOCKS)
                Eyelid_WriteDeadTime(Eyelid_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Eyelid_KillModeMinTime)
                Eyelid_WriteKillTime(Eyelid_backup.PWMKillCounterPeriod);
            #endif /* (Eyelid_KillModeMinTime) */

            #if(Eyelid_UseControl)
                Eyelid_WriteControlRegister(Eyelid_backup.PWMControlRegister);
            #endif /* (Eyelid_UseControl) */
        #endif  /* (!Eyelid_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Eyelid_Sleep
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
*  Eyelid_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Eyelid_Sleep(void) 
{
    #if(Eyelid_UseControl)
        if(Eyelid_CTRL_ENABLE == (Eyelid_CONTROL & Eyelid_CTRL_ENABLE))
        {
            /*Component is enabled */
            Eyelid_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Eyelid_backup.PWMEnableState = 0u;
        }
    #endif /* (Eyelid_UseControl) */

    /* Stop component */
    Eyelid_Stop();

    /* Save registers configuration */
    Eyelid_SaveConfig();
}


/*******************************************************************************
* Function Name: Eyelid_Wakeup
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
*  Eyelid_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Eyelid_Wakeup(void) 
{
     /* Restore registers values */
    Eyelid_RestoreConfig();

    if(Eyelid_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Eyelid_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
