/*******************************************************************************
* File Name: RightNeck.h  
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

#if !defined(CY_PINS_RightNeck_H) /* Pins RightNeck_H */
#define CY_PINS_RightNeck_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RightNeck_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RightNeck__PORT == 15 && ((RightNeck__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RightNeck_Write(uint8 value);
void    RightNeck_SetDriveMode(uint8 mode);
uint8   RightNeck_ReadDataReg(void);
uint8   RightNeck_Read(void);
void    RightNeck_SetInterruptMode(uint16 position, uint16 mode);
uint8   RightNeck_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RightNeck_SetDriveMode() function.
     *  @{
     */
        #define RightNeck_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RightNeck_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RightNeck_DM_RES_UP          PIN_DM_RES_UP
        #define RightNeck_DM_RES_DWN         PIN_DM_RES_DWN
        #define RightNeck_DM_OD_LO           PIN_DM_OD_LO
        #define RightNeck_DM_OD_HI           PIN_DM_OD_HI
        #define RightNeck_DM_STRONG          PIN_DM_STRONG
        #define RightNeck_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RightNeck_MASK               RightNeck__MASK
#define RightNeck_SHIFT              RightNeck__SHIFT
#define RightNeck_WIDTH              1u

/* Interrupt constants */
#if defined(RightNeck__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RightNeck_SetInterruptMode() function.
     *  @{
     */
        #define RightNeck_INTR_NONE      (uint16)(0x0000u)
        #define RightNeck_INTR_RISING    (uint16)(0x0001u)
        #define RightNeck_INTR_FALLING   (uint16)(0x0002u)
        #define RightNeck_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RightNeck_INTR_MASK      (0x01u) 
#endif /* (RightNeck__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RightNeck_PS                     (* (reg8 *) RightNeck__PS)
/* Data Register */
#define RightNeck_DR                     (* (reg8 *) RightNeck__DR)
/* Port Number */
#define RightNeck_PRT_NUM                (* (reg8 *) RightNeck__PRT) 
/* Connect to Analog Globals */                                                  
#define RightNeck_AG                     (* (reg8 *) RightNeck__AG)                       
/* Analog MUX bux enable */
#define RightNeck_AMUX                   (* (reg8 *) RightNeck__AMUX) 
/* Bidirectional Enable */                                                        
#define RightNeck_BIE                    (* (reg8 *) RightNeck__BIE)
/* Bit-mask for Aliased Register Access */
#define RightNeck_BIT_MASK               (* (reg8 *) RightNeck__BIT_MASK)
/* Bypass Enable */
#define RightNeck_BYP                    (* (reg8 *) RightNeck__BYP)
/* Port wide control signals */                                                   
#define RightNeck_CTL                    (* (reg8 *) RightNeck__CTL)
/* Drive Modes */
#define RightNeck_DM0                    (* (reg8 *) RightNeck__DM0) 
#define RightNeck_DM1                    (* (reg8 *) RightNeck__DM1)
#define RightNeck_DM2                    (* (reg8 *) RightNeck__DM2) 
/* Input Buffer Disable Override */
#define RightNeck_INP_DIS                (* (reg8 *) RightNeck__INP_DIS)
/* LCD Common or Segment Drive */
#define RightNeck_LCD_COM_SEG            (* (reg8 *) RightNeck__LCD_COM_SEG)
/* Enable Segment LCD */
#define RightNeck_LCD_EN                 (* (reg8 *) RightNeck__LCD_EN)
/* Slew Rate Control */
#define RightNeck_SLW                    (* (reg8 *) RightNeck__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RightNeck_PRTDSI__CAPS_SEL       (* (reg8 *) RightNeck__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RightNeck_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RightNeck__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RightNeck_PRTDSI__OE_SEL0        (* (reg8 *) RightNeck__PRTDSI__OE_SEL0) 
#define RightNeck_PRTDSI__OE_SEL1        (* (reg8 *) RightNeck__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RightNeck_PRTDSI__OUT_SEL0       (* (reg8 *) RightNeck__PRTDSI__OUT_SEL0) 
#define RightNeck_PRTDSI__OUT_SEL1       (* (reg8 *) RightNeck__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RightNeck_PRTDSI__SYNC_OUT       (* (reg8 *) RightNeck__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RightNeck__SIO_CFG)
    #define RightNeck_SIO_HYST_EN        (* (reg8 *) RightNeck__SIO_HYST_EN)
    #define RightNeck_SIO_REG_HIFREQ     (* (reg8 *) RightNeck__SIO_REG_HIFREQ)
    #define RightNeck_SIO_CFG            (* (reg8 *) RightNeck__SIO_CFG)
    #define RightNeck_SIO_DIFF           (* (reg8 *) RightNeck__SIO_DIFF)
#endif /* (RightNeck__SIO_CFG) */

/* Interrupt Registers */
#if defined(RightNeck__INTSTAT)
    #define RightNeck_INTSTAT            (* (reg8 *) RightNeck__INTSTAT)
    #define RightNeck_SNAP               (* (reg8 *) RightNeck__SNAP)
    
	#define RightNeck_0_INTTYPE_REG 		(* (reg8 *) RightNeck__0__INTTYPE)
#endif /* (RightNeck__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RightNeck_H */


/* [] END OF FILE */
