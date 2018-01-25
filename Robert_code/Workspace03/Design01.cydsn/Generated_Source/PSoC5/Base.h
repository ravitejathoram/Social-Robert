/*******************************************************************************
* File Name: Base.h  
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

#if !defined(CY_PINS_Base_H) /* Pins Base_H */
#define CY_PINS_Base_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Base_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Base__PORT == 15 && ((Base__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Base_Write(uint8 value);
void    Base_SetDriveMode(uint8 mode);
uint8   Base_ReadDataReg(void);
uint8   Base_Read(void);
void    Base_SetInterruptMode(uint16 position, uint16 mode);
uint8   Base_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Base_SetDriveMode() function.
     *  @{
     */
        #define Base_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Base_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Base_DM_RES_UP          PIN_DM_RES_UP
        #define Base_DM_RES_DWN         PIN_DM_RES_DWN
        #define Base_DM_OD_LO           PIN_DM_OD_LO
        #define Base_DM_OD_HI           PIN_DM_OD_HI
        #define Base_DM_STRONG          PIN_DM_STRONG
        #define Base_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Base_MASK               Base__MASK
#define Base_SHIFT              Base__SHIFT
#define Base_WIDTH              1u

/* Interrupt constants */
#if defined(Base__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Base_SetInterruptMode() function.
     *  @{
     */
        #define Base_INTR_NONE      (uint16)(0x0000u)
        #define Base_INTR_RISING    (uint16)(0x0001u)
        #define Base_INTR_FALLING   (uint16)(0x0002u)
        #define Base_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Base_INTR_MASK      (0x01u) 
#endif /* (Base__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Base_PS                     (* (reg8 *) Base__PS)
/* Data Register */
#define Base_DR                     (* (reg8 *) Base__DR)
/* Port Number */
#define Base_PRT_NUM                (* (reg8 *) Base__PRT) 
/* Connect to Analog Globals */                                                  
#define Base_AG                     (* (reg8 *) Base__AG)                       
/* Analog MUX bux enable */
#define Base_AMUX                   (* (reg8 *) Base__AMUX) 
/* Bidirectional Enable */                                                        
#define Base_BIE                    (* (reg8 *) Base__BIE)
/* Bit-mask for Aliased Register Access */
#define Base_BIT_MASK               (* (reg8 *) Base__BIT_MASK)
/* Bypass Enable */
#define Base_BYP                    (* (reg8 *) Base__BYP)
/* Port wide control signals */                                                   
#define Base_CTL                    (* (reg8 *) Base__CTL)
/* Drive Modes */
#define Base_DM0                    (* (reg8 *) Base__DM0) 
#define Base_DM1                    (* (reg8 *) Base__DM1)
#define Base_DM2                    (* (reg8 *) Base__DM2) 
/* Input Buffer Disable Override */
#define Base_INP_DIS                (* (reg8 *) Base__INP_DIS)
/* LCD Common or Segment Drive */
#define Base_LCD_COM_SEG            (* (reg8 *) Base__LCD_COM_SEG)
/* Enable Segment LCD */
#define Base_LCD_EN                 (* (reg8 *) Base__LCD_EN)
/* Slew Rate Control */
#define Base_SLW                    (* (reg8 *) Base__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Base_PRTDSI__CAPS_SEL       (* (reg8 *) Base__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Base_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Base__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Base_PRTDSI__OE_SEL0        (* (reg8 *) Base__PRTDSI__OE_SEL0) 
#define Base_PRTDSI__OE_SEL1        (* (reg8 *) Base__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Base_PRTDSI__OUT_SEL0       (* (reg8 *) Base__PRTDSI__OUT_SEL0) 
#define Base_PRTDSI__OUT_SEL1       (* (reg8 *) Base__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Base_PRTDSI__SYNC_OUT       (* (reg8 *) Base__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Base__SIO_CFG)
    #define Base_SIO_HYST_EN        (* (reg8 *) Base__SIO_HYST_EN)
    #define Base_SIO_REG_HIFREQ     (* (reg8 *) Base__SIO_REG_HIFREQ)
    #define Base_SIO_CFG            (* (reg8 *) Base__SIO_CFG)
    #define Base_SIO_DIFF           (* (reg8 *) Base__SIO_DIFF)
#endif /* (Base__SIO_CFG) */

/* Interrupt Registers */
#if defined(Base__INTSTAT)
    #define Base_INTSTAT            (* (reg8 *) Base__INTSTAT)
    #define Base_SNAP               (* (reg8 *) Base__SNAP)
    
	#define Base_0_INTTYPE_REG 		(* (reg8 *) Base__0__INTTYPE)
#endif /* (Base__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Base_H */


/* [] END OF FILE */
