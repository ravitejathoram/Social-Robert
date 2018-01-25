/*******************************************************************************
* File Name: EyelidVertical.h  
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

#if !defined(CY_PINS_EyelidVertical_H) /* Pins EyelidVertical_H */
#define CY_PINS_EyelidVertical_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EyelidVertical_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EyelidVertical__PORT == 15 && ((EyelidVertical__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    EyelidVertical_Write(uint8 value);
void    EyelidVertical_SetDriveMode(uint8 mode);
uint8   EyelidVertical_ReadDataReg(void);
uint8   EyelidVertical_Read(void);
void    EyelidVertical_SetInterruptMode(uint16 position, uint16 mode);
uint8   EyelidVertical_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the EyelidVertical_SetDriveMode() function.
     *  @{
     */
        #define EyelidVertical_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define EyelidVertical_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define EyelidVertical_DM_RES_UP          PIN_DM_RES_UP
        #define EyelidVertical_DM_RES_DWN         PIN_DM_RES_DWN
        #define EyelidVertical_DM_OD_LO           PIN_DM_OD_LO
        #define EyelidVertical_DM_OD_HI           PIN_DM_OD_HI
        #define EyelidVertical_DM_STRONG          PIN_DM_STRONG
        #define EyelidVertical_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define EyelidVertical_MASK               EyelidVertical__MASK
#define EyelidVertical_SHIFT              EyelidVertical__SHIFT
#define EyelidVertical_WIDTH              1u

/* Interrupt constants */
#if defined(EyelidVertical__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in EyelidVertical_SetInterruptMode() function.
     *  @{
     */
        #define EyelidVertical_INTR_NONE      (uint16)(0x0000u)
        #define EyelidVertical_INTR_RISING    (uint16)(0x0001u)
        #define EyelidVertical_INTR_FALLING   (uint16)(0x0002u)
        #define EyelidVertical_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define EyelidVertical_INTR_MASK      (0x01u) 
#endif /* (EyelidVertical__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EyelidVertical_PS                     (* (reg8 *) EyelidVertical__PS)
/* Data Register */
#define EyelidVertical_DR                     (* (reg8 *) EyelidVertical__DR)
/* Port Number */
#define EyelidVertical_PRT_NUM                (* (reg8 *) EyelidVertical__PRT) 
/* Connect to Analog Globals */                                                  
#define EyelidVertical_AG                     (* (reg8 *) EyelidVertical__AG)                       
/* Analog MUX bux enable */
#define EyelidVertical_AMUX                   (* (reg8 *) EyelidVertical__AMUX) 
/* Bidirectional Enable */                                                        
#define EyelidVertical_BIE                    (* (reg8 *) EyelidVertical__BIE)
/* Bit-mask for Aliased Register Access */
#define EyelidVertical_BIT_MASK               (* (reg8 *) EyelidVertical__BIT_MASK)
/* Bypass Enable */
#define EyelidVertical_BYP                    (* (reg8 *) EyelidVertical__BYP)
/* Port wide control signals */                                                   
#define EyelidVertical_CTL                    (* (reg8 *) EyelidVertical__CTL)
/* Drive Modes */
#define EyelidVertical_DM0                    (* (reg8 *) EyelidVertical__DM0) 
#define EyelidVertical_DM1                    (* (reg8 *) EyelidVertical__DM1)
#define EyelidVertical_DM2                    (* (reg8 *) EyelidVertical__DM2) 
/* Input Buffer Disable Override */
#define EyelidVertical_INP_DIS                (* (reg8 *) EyelidVertical__INP_DIS)
/* LCD Common or Segment Drive */
#define EyelidVertical_LCD_COM_SEG            (* (reg8 *) EyelidVertical__LCD_COM_SEG)
/* Enable Segment LCD */
#define EyelidVertical_LCD_EN                 (* (reg8 *) EyelidVertical__LCD_EN)
/* Slew Rate Control */
#define EyelidVertical_SLW                    (* (reg8 *) EyelidVertical__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EyelidVertical_PRTDSI__CAPS_SEL       (* (reg8 *) EyelidVertical__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EyelidVertical_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EyelidVertical__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EyelidVertical_PRTDSI__OE_SEL0        (* (reg8 *) EyelidVertical__PRTDSI__OE_SEL0) 
#define EyelidVertical_PRTDSI__OE_SEL1        (* (reg8 *) EyelidVertical__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EyelidVertical_PRTDSI__OUT_SEL0       (* (reg8 *) EyelidVertical__PRTDSI__OUT_SEL0) 
#define EyelidVertical_PRTDSI__OUT_SEL1       (* (reg8 *) EyelidVertical__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EyelidVertical_PRTDSI__SYNC_OUT       (* (reg8 *) EyelidVertical__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(EyelidVertical__SIO_CFG)
    #define EyelidVertical_SIO_HYST_EN        (* (reg8 *) EyelidVertical__SIO_HYST_EN)
    #define EyelidVertical_SIO_REG_HIFREQ     (* (reg8 *) EyelidVertical__SIO_REG_HIFREQ)
    #define EyelidVertical_SIO_CFG            (* (reg8 *) EyelidVertical__SIO_CFG)
    #define EyelidVertical_SIO_DIFF           (* (reg8 *) EyelidVertical__SIO_DIFF)
#endif /* (EyelidVertical__SIO_CFG) */

/* Interrupt Registers */
#if defined(EyelidVertical__INTSTAT)
    #define EyelidVertical_INTSTAT            (* (reg8 *) EyelidVertical__INTSTAT)
    #define EyelidVertical_SNAP               (* (reg8 *) EyelidVertical__SNAP)
    
	#define EyelidVertical_0_INTTYPE_REG 		(* (reg8 *) EyelidVertical__0__INTTYPE)
#endif /* (EyelidVertical__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EyelidVertical_H */


/* [] END OF FILE */
