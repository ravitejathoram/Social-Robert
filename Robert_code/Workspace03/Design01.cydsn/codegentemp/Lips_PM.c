/*******************************************************************************
* File Name: Lips_PM.c
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

#include "Lips.h"

static Lips_backupStruct Lips_backup;


/*******************************************************************************
* Function Name: Lips_SaveConfig
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
*  Lips_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Lips_SaveConfig(void) 
{

    #if(!Lips_UsingFixedFunction)
        #if(!Lips_PWMModeIsCenterAligned)
            Lips_backup.PWMPeriod = Lips_ReadPeriod();
        #endif /* (!Lips_PWMModeIsCenterAligned) */
        Lips_backup.PWMUdb = Lips_ReadCounter();
        #if (Lips_UseStatus)
            Lips_backup.InterruptMaskValue = Lips_STATUS_MASK;
        #endif /* (Lips_UseStatus) */

        #if(Lips_DeadBandMode == Lips__B_PWM__DBM_256_CLOCKS || \
            Lips_DeadBandMode == Lips__B_PWM__DBM_2_4_CLOCKS)
            Lips_backup.PWMdeadBandValue = Lips_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Lips_KillModeMinTime)
             Lips_backup.PWMKillCounterPeriod = Lips_ReadKillTime();
        #endif /* (Lips_KillModeMinTime) */

        #if(Lips_UseControl)
            Lips_backup.PWMControlRegister = Lips_ReadControlRegister();
        #endif /* (Lips_UseControl) */
    #endif  /* (!Lips_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Lips_RestoreConfig
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
*  Lips_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Lips_RestoreConfig(void) 
{
        #if(!Lips_UsingFixedFunction)
            #if(!Lips_PWMModeIsCenterAligned)
                Lips_WritePeriod(Lips_backup.PWMPeriod);
            #endif /* (!Lips_PWMModeIsCenterAligned) */

            Lips_WriteCounter(Lips_backup.PWMUdb);

            #if (Lips_UseStatus)
                Lips_STATUS_MASK = Lips_backup.InterruptMaskValue;
            #endif /* (Lips_UseStatus) */

            #if(Lips_DeadBandMode == Lips__B_PWM__DBM_256_CLOCKS || \
                Lips_DeadBandMode == Lips__B_PWM__DBM_2_4_CLOCKS)
                Lips_WriteDeadTime(Lips_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Lips_KillModeMinTime)
                Lips_WriteKillTime(Lips_backup.PWMKillCounterPeriod);
            #endif /* (Lips_KillModeMinTime) */

            #if(Lips_UseControl)
                Lips_WriteControlRegister(Lips_backup.PWMControlRegister);
            #endif /* (Lips_UseControl) */
        #endif  /* (!Lips_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Lips_Sleep
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
*  Lips_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Lips_Sleep(void) 
{
    #if(Lips_UseControl)
        if(Lips_CTRL_ENABLE == (Lips_CONTROL & Lips_CTRL_ENABLE))
        {
            /*Component is enabled */
            Lips_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Lips_backup.PWMEnableState = 0u;
        }
    #endif /* (Lips_UseControl) */

    /* Stop component */
    Lips_Stop();

    /* Save registers configuration */
    Lips_SaveConfig();
}


/*******************************************************************************
* Function Name: Lips_Wakeup
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
*  Lips_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Lips_Wakeup(void) 
{
     /* Restore registers values */
    Lips_RestoreConfig();

    if(Lips_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Lips_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
