/*******************************************************************************
* File Name: LeftNeck.h  
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

#if !defined(CY_PINS_LeftNeck_H) /* Pins LeftNeck_H */
#define CY_PINS_LeftNeck_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LeftNeck_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LeftNeck__PORT == 15 && ((LeftNeck__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LeftNeck_Write(uint8 value);
void    LeftNeck_SetDriveMode(uint8 mode);
uint8   LeftNeck_ReadDataReg(void);
uint8   LeftNeck_Read(void);
void    LeftNeck_SetInterruptMode(uint16 position, uint16 mode);
uint8   LeftNeck_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LeftNeck_SetDriveMode() function.
     *  @{
     */
        #define LeftNeck_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LeftNeck_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LeftNeck_DM_RES_UP          PIN_DM_RES_UP
        #define LeftNeck_DM_RES_DWN         PIN_DM_RES_DWN
        #define LeftNeck_DM_OD_LO           PIN_DM_OD_LO
        #define LeftNeck_DM_OD_HI           PIN_DM_OD_HI
        #define LeftNeck_DM_STRONG          PIN_DM_STRONG
        #define LeftNeck_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LeftNeck_MASK               LeftNeck__MASK
#define LeftNeck_SHIFT              LeftNeck__SHIFT
#define LeftNeck_WIDTH              1u

/* Interrupt constants */
#if defined(LeftNeck__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LeftNeck_SetInterruptMode() function.
     *  @{
     */
        #define LeftNeck_INTR_NONE      (uint16)(0x0000u)
        #define LeftNeck_INTR_RISING    (uint16)(0x0001u)
        #define LeftNeck_INTR_FALLING   (uint16)(0x0002u)
        #define LeftNeck_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LeftNeck_INTR_MASK      (0x01u) 
#endif /* (LeftNeck__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LeftNeck_PS                     (* (reg8 *) LeftNeck__PS)
/* Data Register */
#define LeftNeck_DR                     (* (reg8 *) LeftNeck__DR)
/* Port Number */
#define LeftNeck_PRT_NUM                (* (reg8 *) LeftNeck__PRT) 
/* Connect to Analog Globals */                                                  
#define LeftNeck_AG                     (* (reg8 *) LeftNeck__AG)                       
/* Analog MUX bux enable */
#define LeftNeck_AMUX                   (* (reg8 *) LeftNeck__AMUX) 
/* Bidirectional Enable */                                                        
#define LeftNeck_BIE                    (* (reg8 *) LeftNeck__BIE)
/* Bit-mask for Aliased Register Access */
#define LeftNeck_BIT_MASK               (* (reg8 *) LeftNeck__BIT_MASK)
/* Bypass Enable */
#define LeftNeck_BYP                    (* (reg8 *) LeftNeck__BYP)
/* Port wide control signals */                                                   
#define LeftNeck_CTL                    (* (reg8 *) LeftNeck__CTL)
/* Drive Modes */
#define LeftNeck_DM0                    (* (reg8 *) LeftNeck__DM0) 
#define LeftNeck_DM1                    (* (reg8 *) LeftNeck__DM1)
#define LeftNeck_DM2                    (* (reg8 *) LeftNeck__DM2) 
/* Input Buffer Disable Override */
#define LeftNeck_INP_DIS                (* (reg8 *) LeftNeck__INP_DIS)
/* LCD Common or Segment Drive */
#define LeftNeck_LCD_COM_SEG            (* (reg8 *) LeftNeck__LCD_COM_SEG)
/* Enable Segment LCD */
#define LeftNeck_LCD_EN                 (* (reg8 *) LeftNeck__LCD_EN)
/* Slew Rate Control */
#define LeftNeck_SLW                    (* (reg8 *) LeftNeck__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LeftNeck_PRTDSI__CAPS_SEL       (* (reg8 *) LeftNeck__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LeftNeck_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LeftNeck__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LeftNeck_PRTDSI__OE_SEL0        (* (reg8 *) LeftNeck__PRTDSI__OE_SEL0) 
#define LeftNeck_PRTDSI__OE_SEL1        (* (reg8 *) LeftNeck__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LeftNeck_PRTDSI__OUT_SEL0       (* (reg8 *) LeftNeck__PRTDSI__OUT_SEL0) 
#define LeftNeck_PRTDSI__OUT_SEL1       (* (reg8 *) LeftNeck__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LeftNeck_PRTDSI__SYNC_OUT       (* (reg8 *) LeftNeck__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LeftNeck__SIO_CFG)
    #define LeftNeck_SIO_HYST_EN        (* (reg8 *) LeftNeck__SIO_HYST_EN)
    #define LeftNeck_SIO_REG_HIFREQ     (* (reg8 *) LeftNeck__SIO_REG_HIFREQ)
    #define LeftNeck_SIO_CFG            (* (reg8 *) LeftNeck__SIO_CFG)
    #define LeftNeck_SIO_DIFF           (* (reg8 *) LeftNeck__SIO_DIFF)
#endif /* (LeftNeck__SIO_CFG) */

/* Interrupt Registers */
#if defined(LeftNeck__INTSTAT)
    #define LeftNeck_INTSTAT            (* (reg8 *) LeftNeck__INTSTAT)
    #define LeftNeck_SNAP               (* (reg8 *) LeftNeck__SNAP)
    
	#define LeftNeck_0_INTTYPE_REG 		(* (reg8 *) LeftNeck__0__INTTYPE)
#endif /* (LeftNeck__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LeftNeck_H */


/* [] END OF FILE */
