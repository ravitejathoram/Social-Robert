/*******************************************************************************
* File Name: Right_Eyeball_PM.c
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

#include "Right_Eyeball.h"

static Right_Eyeball_backupStruct Right_Eyeball_backup;


/*******************************************************************************
* Function Name: Right_Eyeball_SaveConfig
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
*  Right_Eyeball_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Right_Eyeball_SaveConfig(void) 
{

    #if(!Right_Eyeball_UsingFixedFunction)
        #if(!Right_Eyeball_PWMModeIsCenterAligned)
            Right_Eyeball_backup.PWMPeriod = Right_Eyeball_ReadPeriod();
        #endif /* (!Right_Eyeball_PWMModeIsCenterAligned) */
        Right_Eyeball_backup.PWMUdb = Right_Eyeball_ReadCounter();
        #if (Right_Eyeball_UseStatus)
            Right_Eyeball_backup.InterruptMaskValue = Right_Eyeball_STATUS_MASK;
        #endif /* (Right_Eyeball_UseStatus) */

        #if(Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_256_CLOCKS || \
            Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_2_4_CLOCKS)
            Right_Eyeball_backup.PWMdeadBandValue = Right_Eyeball_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Right_Eyeball_KillModeMinTime)
             Right_Eyeball_backup.PWMKillCounterPeriod = Right_Eyeball_ReadKillTime();
        #endif /* (Right_Eyeball_KillModeMinTime) */

        #if(Right_Eyeball_UseControl)
            Right_Eyeball_backup.PWMControlRegister = Right_Eyeball_ReadControlRegister();
        #endif /* (Right_Eyeball_UseControl) */
    #endif  /* (!Right_Eyeball_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Right_Eyeball_RestoreConfig
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
*  Right_Eyeball_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Right_Eyeball_RestoreConfig(void) 
{
        #if(!Right_Eyeball_UsingFixedFunction)
            #if(!Right_Eyeball_PWMModeIsCenterAligned)
                Right_Eyeball_WritePeriod(Right_Eyeball_backup.PWMPeriod);
            #endif /* (!Right_Eyeball_PWMModeIsCenterAligned) */

            Right_Eyeball_WriteCounter(Right_Eyeball_backup.PWMUdb);

            #if (Right_Eyeball_UseStatus)
                Right_Eyeball_STATUS_MASK = Right_Eyeball_backup.InterruptMaskValue;
            #endif /* (Right_Eyeball_UseStatus) */

            #if(Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_256_CLOCKS || \
                Right_Eyeball_DeadBandMode == Right_Eyeball__B_PWM__DBM_2_4_CLOCKS)
                Right_Eyeball_WriteDeadTime(Right_Eyeball_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Right_Eyeball_KillModeMinTime)
                Right_Eyeball_WriteKillTime(Right_Eyeball_backup.PWMKillCounterPeriod);
            #endif /* (Right_Eyeball_KillModeMinTime) */

            #if(Right_Eyeball_UseControl)
                Right_Eyeball_WriteControlRegister(Right_Eyeball_backup.PWMControlRegister);
            #endif /* (Right_Eyeball_UseControl) */
        #endif  /* (!Right_Eyeball_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Right_Eyeball_Sleep
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
*  Right_Eyeball_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Right_Eyeball_Sleep(void) 
{
    #if(Right_Eyeball_UseControl)
        if(Right_Eyeball_CTRL_ENABLE == (Right_Eyeball_CONTROL & Right_Eyeball_CTRL_ENABLE))
        {
            /*Component is enabled */
            Right_Eyeball_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Right_Eyeball_backup.PWMEnableState = 0u;
        }
    #endif /* (Right_Eyeball_UseControl) */

    /* Stop component */
    Right_Eyeball_Stop();

    /* Save registers configuration */
    Right_Eyeball_SaveConfig();
}


/*******************************************************************************
* Function Name: Right_Eyeball_Wakeup
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
*  Right_Eyeball_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Right_Eyeball_Wakeup(void) 
{
     /* Restore registers values */
    Right_Eyeball_RestoreConfig();

    if(Right_Eyeball_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Right_Eyeball_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
