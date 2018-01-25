/*******************************************************************************
* File Name: LeftLip.h  
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

#if !defined(CY_PINS_LeftLip_H) /* Pins LeftLip_H */
#define CY_PINS_LeftLip_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LeftLip_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LeftLip__PORT == 15 && ((LeftLip__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LeftLip_Write(uint8 value);
void    LeftLip_SetDriveMode(uint8 mode);
uint8   LeftLip_ReadDataReg(void);
uint8   LeftLip_Read(void);
void    LeftLip_SetInterruptMode(uint16 position, uint16 mode);
uint8   LeftLip_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LeftLip_SetDriveMode() function.
     *  @{
     */
        #define LeftLip_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LeftLip_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LeftLip_DM_RES_UP          PIN_DM_RES_UP
        #define LeftLip_DM_RES_DWN         PIN_DM_RES_DWN
        #define LeftLip_DM_OD_LO           PIN_DM_OD_LO
        #define LeftLip_DM_OD_HI           PIN_DM_OD_HI
        #define LeftLip_DM_STRONG          PIN_DM_STRONG
        #define LeftLip_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LeftLip_MASK               LeftLip__MASK
#define LeftLip_SHIFT              LeftLip__SHIFT
#define LeftLip_WIDTH              1u

/* Interrupt constants */
#if defined(LeftLip__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LeftLip_SetInterruptMode() function.
     *  @{
     */
        #define LeftLip_INTR_NONE      (uint16)(0x0000u)
        #define LeftLip_INTR_RISING    (uint16)(0x0001u)
        #define LeftLip_INTR_FALLING   (uint16)(0x0002u)
        #define LeftLip_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LeftLip_INTR_MASK      (0x01u) 
#endif /* (LeftLip__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LeftLip_PS                     (* (reg8 *) LeftLip__PS)
/* Data Register */
#define LeftLip_DR                     (* (reg8 *) LeftLip__DR)
/* Port Number */
#define LeftLip_PRT_NUM                (* (reg8 *) LeftLip__PRT) 
/* Connect to Analog Globals */                                                  
#define LeftLip_AG                     (* (reg8 *) LeftLip__AG)                       
/* Analog MUX bux enable */
#define LeftLip_AMUX                   (* (reg8 *) LeftLip__AMUX) 
/* Bidirectional Enable */                                                        
#define LeftLip_BIE                    (* (reg8 *) LeftLip__BIE)
/* Bit-mask for Aliased Register Access */
#define LeftLip_BIT_MASK               (* (reg8 *) LeftLip__BIT_MASK)
/* Bypass Enable */
#define LeftLip_BYP                    (* (reg8 *) LeftLip__BYP)
/* Port wide control signals */                                                   
#define LeftLip_CTL                    (* (reg8 *) LeftLip__CTL)
/* Drive Modes */
#define LeftLip_DM0                    (* (reg8 *) LeftLip__DM0) 
#define LeftLip_DM1                    (* (reg8 *) LeftLip__DM1)
#define LeftLip_DM2                    (* (reg8 *) LeftLip__DM2) 
/* Input Buffer Disable Override */
#define LeftLip_INP_DIS                (* (reg8 *) LeftLip__INP_DIS)
/* LCD Common or Segment Drive */
#define LeftLip_LCD_COM_SEG            (* (reg8 *) LeftLip__LCD_COM_SEG)
/* Enable Segment LCD */
#define LeftLip_LCD_EN                 (* (reg8 *) LeftLip__LCD_EN)
/* Slew Rate Control */
#define LeftLip_SLW                    (* (reg8 *) LeftLip__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LeftLip_PRTDSI__CAPS_SEL       (* (reg8 *) LeftLip__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LeftLip_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LeftLip__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LeftLip_PRTDSI__OE_SEL0        (* (reg8 *) LeftLip__PRTDSI__OE_SEL0) 
#define LeftLip_PRTDSI__OE_SEL1        (* (reg8 *) LeftLip__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LeftLip_PRTDSI__OUT_SEL0       (* (reg8 *) LeftLip__PRTDSI__OUT_SEL0) 
#define LeftLip_PRTDSI__OUT_SEL1       (* (reg8 *) LeftLip__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LeftLip_PRTDSI__SYNC_OUT       (* (reg8 *) LeftLip__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LeftLip__SIO_CFG)
    #define LeftLip_SIO_HYST_EN        (* (reg8 *) LeftLip__SIO_HYST_EN)
    #define LeftLip_SIO_REG_HIFREQ     (* (reg8 *) LeftLip__SIO_REG_HIFREQ)
    #define LeftLip_SIO_CFG            (* (reg8 *) LeftLip__SIO_CFG)
    #define LeftLip_SIO_DIFF           (* (reg8 *) LeftLip__SIO_DIFF)
#endif /* (LeftLip__SIO_CFG) */

/* Interrupt Registers */
#if defined(LeftLip__INTSTAT)
    #define LeftLip_INTSTAT            (* (reg8 *) LeftLip__INTSTAT)
    #define LeftLip_SNAP               (* (reg8 *) LeftLip__SNAP)
    
	#define LeftLip_0_INTTYPE_REG 		(* (reg8 *) LeftLip__0__INTTYPE)
#endif /* (LeftLip__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LeftLip_H */


/* [] END OF FILE */
