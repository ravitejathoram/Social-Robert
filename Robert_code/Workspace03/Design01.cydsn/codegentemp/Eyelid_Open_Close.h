/*******************************************************************************
* File Name: Eyelid_Open_Close.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Eyelid_Open_Close_H) /* Pins Eyelid_Open_Close_H */
#define CY_PINS_Eyelid_Open_Close_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Eyelid_Open_Close_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Eyelid_Open_Close__PORT == 15 && ((Eyelid_Open_Close__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Eyelid_Open_Close_Write(uint8 value);
void    Eyelid_Open_Close_SetDriveMode(uint8 mode);
uint8   Eyelid_Open_Close_ReadDataReg(void);
uint8   Eyelid_Open_Close_Read(void);
void    Eyelid_Open_Close_SetInterruptMode(uint16 position, uint16 mode);
uint8   Eyelid_Open_Close_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Eyelid_Open_Close_SetDriveMode() function.
     *  @{
     */
        #define Eyelid_Open_Close_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Eyelid_Open_Close_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Eyelid_Open_Close_DM_RES_UP          PIN_DM_RES_UP
        #define Eyelid_Open_Close_DM_RES_DWN         PIN_DM_RES_DWN
        #define Eyelid_Open_Close_DM_OD_LO           PIN_DM_OD_LO
        #define Eyelid_Open_Close_DM_OD_HI           PIN_DM_OD_HI
        #define Eyelid_Open_Close_DM_STRONG          PIN_DM_STRONG
        #define Eyelid_Open_Close_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Eyelid_Open_Close_MASK               Eyelid_Open_Close__MASK
#define Eyelid_Open_Close_SHIFT              Eyelid_Open_Close__SHIFT
#define Eyelid_Open_Close_WIDTH              1u

/* Interrupt constants */
#if defined(Eyelid_Open_Close__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Eyelid_Open_Close_SetInterruptMode() function.
     *  @{
     */
        #define Eyelid_Open_Close_INTR_NONE      (uint16)(0x0000u)
        #define Eyelid_Open_Close_INTR_RISING    (uint16)(0x0001u)
        #define Eyelid_Open_Close_INTR_FALLING   (uint16)(0x0002u)
        #define Eyelid_Open_Close_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Eyelid_Open_Close_INTR_MASK      (0x01u) 
#endif /* (Eyelid_Open_Close__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Eyelid_Open_Close_PS                     (* (reg8 *) Eyelid_Open_Close__PS)
/* Data Register */
#define Eyelid_Open_Close_DR                     (* (reg8 *) Eyelid_Open_Close__DR)
/* Port Number */
#define Eyelid_Open_Close_PRT_NUM                (* (reg8 *) Eyelid_Open_Close__PRT) 
/* Connect to Analog Globals */                                                  
#define Eyelid_Open_Close_AG                     (* (reg8 *) Eyelid_Open_Close__AG)                       
/* Analog MUX bux enable */
#define Eyelid_Open_Close_AMUX                   (* (reg8 *) Eyelid_Open_Close__AMUX) 
/* Bidirectional Enable */                                                        
#define Eyelid_Open_Close_BIE                    (* (reg8 *) Eyelid_Open_Close__BIE)
/* Bit-mask for Aliased Register Access */
#define Eyelid_Open_Close_BIT_MASK               (* (reg8 *) Eyelid_Open_Close__BIT_MASK)
/* Bypass Enable */
#define Eyelid_Open_Close_BYP                    (* (reg8 *) Eyelid_Open_Close__BYP)
/* Port wide control signals */                                                   
#define Eyelid_Open_Close_CTL                    (* (reg8 *) Eyelid_Open_Close__CTL)
/* Drive Modes */
#define Eyelid_Open_Close_DM0                    (* (reg8 *) Eyelid_Open_Close__DM0) 
#define Eyelid_Open_Close_DM1                    (* (reg8 *) Eyelid_Open_Close__DM1)
#define Eyelid_Open_Close_DM2                    (* (reg8 *) Eyelid_Open_Close__DM2) 
/* Input Buffer Disable Override */
#define Eyelid_Open_Close_INP_DIS                (* (reg8 *) Eyelid_Open_Close__INP_DIS)
/* LCD Common or Segment Drive */
#define Eyelid_Open_Close_LCD_COM_SEG            (* (reg8 *) Eyelid_Open_Close__LCD_COM_SEG)
/* Enable Segment LCD */
#define Eyelid_Open_Close_LCD_EN                 (* (reg8 *) Eyelid_Open_Close__LCD_EN)
/* Slew Rate Control */
#define Eyelid_Open_Close_SLW                    (* (reg8 *) Eyelid_Open_Close__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Eyelid_Open_Close_PRTDSI__CAPS_SEL       (* (reg8 *) Eyelid_Open_Close__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Eyelid_Open_Close_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Eyelid_Open_Close__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Eyelid_Open_Close_PRTDSI__OE_SEL0        (* (reg8 *) Eyelid_Open_Close__PRTDSI__OE_SEL0) 
#define Eyelid_Open_Close_PRTDSI__OE_SEL1        (* (reg8 *) Eyelid_Open_Close__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Eyelid_Open_Close_PRTDSI__OUT_SEL0       (* (reg8 *) Eyelid_Open_Close__PRTDSI__OUT_SEL0) 
#define Eyelid_Open_Close_PRTDSI__OUT_SEL1       (* (reg8 *) Eyelid_Open_Close__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Eyelid_Open_Close_PRTDSI__SYNC_OUT       (* (reg8 *) Eyelid_Open_Close__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Eyelid_Open_Close__SIO_CFG)
    #define Eyelid_Open_Close_SIO_HYST_EN        (* (reg8 *) Eyelid_Open_Close__SIO_HYST_EN)
    #define Eyelid_Open_Close_SIO_REG_HIFREQ     (* (reg8 *) Eyelid_Open_Close__SIO_REG_HIFREQ)
    #define Eyelid_Open_Close_SIO_CFG            (* (reg8 *) Eyelid_Open_Close__SIO_CFG)
    #define Eyelid_Open_Close_SIO_DIFF           (* (reg8 *) Eyelid_Open_Close__SIO_DIFF)
#endif /* (Eyelid_Open_Close__SIO_CFG) */

/* Interrupt Registers */
#if defined(Eyelid_Open_Close__INTSTAT)
    #define Eyelid_Open_Close_INTSTAT            (* (reg8 *) Eyelid_Open_Close__INTSTAT)
    #define Eyelid_Open_Close_SNAP               (* (reg8 *) Eyelid_Open_Close__SNAP)
    
	#define Eyelid_Open_Close_0_INTTYPE_REG 		(* (reg8 *) Eyelid_Open_Close__0__INTTYPE)
#endif /* (Eyelid_Open_Close__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Eyelid_Open_Close_H */


/* [] END OF FILE */
