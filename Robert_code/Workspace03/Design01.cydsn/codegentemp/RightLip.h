/*******************************************************************************
* File Name: RightLip.h  
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

#if !defined(CY_PINS_RightLip_H) /* Pins RightLip_H */
#define CY_PINS_RightLip_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RightLip_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RightLip__PORT == 15 && ((RightLip__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RightLip_Write(uint8 value);
void    RightLip_SetDriveMode(uint8 mode);
uint8   RightLip_ReadDataReg(void);
uint8   RightLip_Read(void);
void    RightLip_SetInterruptMode(uint16 position, uint16 mode);
uint8   RightLip_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RightLip_SetDriveMode() function.
     *  @{
     */
        #define RightLip_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RightLip_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RightLip_DM_RES_UP          PIN_DM_RES_UP
        #define RightLip_DM_RES_DWN         PIN_DM_RES_DWN
        #define RightLip_DM_OD_LO           PIN_DM_OD_LO
        #define RightLip_DM_OD_HI           PIN_DM_OD_HI
        #define RightLip_DM_STRONG          PIN_DM_STRONG
        #define RightLip_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RightLip_MASK               RightLip__MASK
#define RightLip_SHIFT              RightLip__SHIFT
#define RightLip_WIDTH              1u

/* Interrupt constants */
#if defined(RightLip__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RightLip_SetInterruptMode() function.
     *  @{
     */
        #define RightLip_INTR_NONE      (uint16)(0x0000u)
        #define RightLip_INTR_RISING    (uint16)(0x0001u)
        #define RightLip_INTR_FALLING   (uint16)(0x0002u)
        #define RightLip_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RightLip_INTR_MASK      (0x01u) 
#endif /* (RightLip__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RightLip_PS                     (* (reg8 *) RightLip__PS)
/* Data Register */
#define RightLip_DR                     (* (reg8 *) RightLip__DR)
/* Port Number */
#define RightLip_PRT_NUM                (* (reg8 *) RightLip__PRT) 
/* Connect to Analog Globals */                                                  
#define RightLip_AG                     (* (reg8 *) RightLip__AG)                       
/* Analog MUX bux enable */
#define RightLip_AMUX                   (* (reg8 *) RightLip__AMUX) 
/* Bidirectional Enable */                                                        
#define RightLip_BIE                    (* (reg8 *) RightLip__BIE)
/* Bit-mask for Aliased Register Access */
#define RightLip_BIT_MASK               (* (reg8 *) RightLip__BIT_MASK)
/* Bypass Enable */
#define RightLip_BYP                    (* (reg8 *) RightLip__BYP)
/* Port wide control signals */                                                   
#define RightLip_CTL                    (* (reg8 *) RightLip__CTL)
/* Drive Modes */
#define RightLip_DM0                    (* (reg8 *) RightLip__DM0) 
#define RightLip_DM1                    (* (reg8 *) RightLip__DM1)
#define RightLip_DM2                    (* (reg8 *) RightLip__DM2) 
/* Input Buffer Disable Override */
#define RightLip_INP_DIS                (* (reg8 *) RightLip__INP_DIS)
/* LCD Common or Segment Drive */
#define RightLip_LCD_COM_SEG            (* (reg8 *) RightLip__LCD_COM_SEG)
/* Enable Segment LCD */
#define RightLip_LCD_EN                 (* (reg8 *) RightLip__LCD_EN)
/* Slew Rate Control */
#define RightLip_SLW                    (* (reg8 *) RightLip__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RightLip_PRTDSI__CAPS_SEL       (* (reg8 *) RightLip__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RightLip_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RightLip__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RightLip_PRTDSI__OE_SEL0        (* (reg8 *) RightLip__PRTDSI__OE_SEL0) 
#define RightLip_PRTDSI__OE_SEL1        (* (reg8 *) RightLip__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RightLip_PRTDSI__OUT_SEL0       (* (reg8 *) RightLip__PRTDSI__OUT_SEL0) 
#define RightLip_PRTDSI__OUT_SEL1       (* (reg8 *) RightLip__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RightLip_PRTDSI__SYNC_OUT       (* (reg8 *) RightLip__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RightLip__SIO_CFG)
    #define RightLip_SIO_HYST_EN        (* (reg8 *) RightLip__SIO_HYST_EN)
    #define RightLip_SIO_REG_HIFREQ     (* (reg8 *) RightLip__SIO_REG_HIFREQ)
    #define RightLip_SIO_CFG            (* (reg8 *) RightLip__SIO_CFG)
    #define RightLip_SIO_DIFF           (* (reg8 *) RightLip__SIO_DIFF)
#endif /* (RightLip__SIO_CFG) */

/* Interrupt Registers */
#if defined(RightLip__INTSTAT)
    #define RightLip_INTSTAT            (* (reg8 *) RightLip__INTSTAT)
    #define RightLip_SNAP               (* (reg8 *) RightLip__SNAP)
    
	#define RightLip_0_INTTYPE_REG 		(* (reg8 *) RightLip__0__INTTYPE)
#endif /* (RightLip__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RightLip_H */


/* [] END OF FILE */
