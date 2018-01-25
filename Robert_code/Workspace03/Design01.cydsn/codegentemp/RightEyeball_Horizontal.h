/*******************************************************************************
* File Name: RightEyeball_Horizontal.h  
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

#if !defined(CY_PINS_RightEyeball_Horizontal_H) /* Pins RightEyeball_Horizontal_H */
#define CY_PINS_RightEyeball_Horizontal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RightEyeball_Horizontal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RightEyeball_Horizontal__PORT == 15 && ((RightEyeball_Horizontal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RightEyeball_Horizontal_Write(uint8 value);
void    RightEyeball_Horizontal_SetDriveMode(uint8 mode);
uint8   RightEyeball_Horizontal_ReadDataReg(void);
uint8   RightEyeball_Horizontal_Read(void);
void    RightEyeball_Horizontal_SetInterruptMode(uint16 position, uint16 mode);
uint8   RightEyeball_Horizontal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RightEyeball_Horizontal_SetDriveMode() function.
     *  @{
     */
        #define RightEyeball_Horizontal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RightEyeball_Horizontal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RightEyeball_Horizontal_DM_RES_UP          PIN_DM_RES_UP
        #define RightEyeball_Horizontal_DM_RES_DWN         PIN_DM_RES_DWN
        #define RightEyeball_Horizontal_DM_OD_LO           PIN_DM_OD_LO
        #define RightEyeball_Horizontal_DM_OD_HI           PIN_DM_OD_HI
        #define RightEyeball_Horizontal_DM_STRONG          PIN_DM_STRONG
        #define RightEyeball_Horizontal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RightEyeball_Horizontal_MASK               RightEyeball_Horizontal__MASK
#define RightEyeball_Horizontal_SHIFT              RightEyeball_Horizontal__SHIFT
#define RightEyeball_Horizontal_WIDTH              1u

/* Interrupt constants */
#if defined(RightEyeball_Horizontal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RightEyeball_Horizontal_SetInterruptMode() function.
     *  @{
     */
        #define RightEyeball_Horizontal_INTR_NONE      (uint16)(0x0000u)
        #define RightEyeball_Horizontal_INTR_RISING    (uint16)(0x0001u)
        #define RightEyeball_Horizontal_INTR_FALLING   (uint16)(0x0002u)
        #define RightEyeball_Horizontal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RightEyeball_Horizontal_INTR_MASK      (0x01u) 
#endif /* (RightEyeball_Horizontal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RightEyeball_Horizontal_PS                     (* (reg8 *) RightEyeball_Horizontal__PS)
/* Data Register */
#define RightEyeball_Horizontal_DR                     (* (reg8 *) RightEyeball_Horizontal__DR)
/* Port Number */
#define RightEyeball_Horizontal_PRT_NUM                (* (reg8 *) RightEyeball_Horizontal__PRT) 
/* Connect to Analog Globals */                                                  
#define RightEyeball_Horizontal_AG                     (* (reg8 *) RightEyeball_Horizontal__AG)                       
/* Analog MUX bux enable */
#define RightEyeball_Horizontal_AMUX                   (* (reg8 *) RightEyeball_Horizontal__AMUX) 
/* Bidirectional Enable */                                                        
#define RightEyeball_Horizontal_BIE                    (* (reg8 *) RightEyeball_Horizontal__BIE)
/* Bit-mask for Aliased Register Access */
#define RightEyeball_Horizontal_BIT_MASK               (* (reg8 *) RightEyeball_Horizontal__BIT_MASK)
/* Bypass Enable */
#define RightEyeball_Horizontal_BYP                    (* (reg8 *) RightEyeball_Horizontal__BYP)
/* Port wide control signals */                                                   
#define RightEyeball_Horizontal_CTL                    (* (reg8 *) RightEyeball_Horizontal__CTL)
/* Drive Modes */
#define RightEyeball_Horizontal_DM0                    (* (reg8 *) RightEyeball_Horizontal__DM0) 
#define RightEyeball_Horizontal_DM1                    (* (reg8 *) RightEyeball_Horizontal__DM1)
#define RightEyeball_Horizontal_DM2                    (* (reg8 *) RightEyeball_Horizontal__DM2) 
/* Input Buffer Disable Override */
#define RightEyeball_Horizontal_INP_DIS                (* (reg8 *) RightEyeball_Horizontal__INP_DIS)
/* LCD Common or Segment Drive */
#define RightEyeball_Horizontal_LCD_COM_SEG            (* (reg8 *) RightEyeball_Horizontal__LCD_COM_SEG)
/* Enable Segment LCD */
#define RightEyeball_Horizontal_LCD_EN                 (* (reg8 *) RightEyeball_Horizontal__LCD_EN)
/* Slew Rate Control */
#define RightEyeball_Horizontal_SLW                    (* (reg8 *) RightEyeball_Horizontal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RightEyeball_Horizontal_PRTDSI__CAPS_SEL       (* (reg8 *) RightEyeball_Horizontal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RightEyeball_Horizontal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RightEyeball_Horizontal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RightEyeball_Horizontal_PRTDSI__OE_SEL0        (* (reg8 *) RightEyeball_Horizontal__PRTDSI__OE_SEL0) 
#define RightEyeball_Horizontal_PRTDSI__OE_SEL1        (* (reg8 *) RightEyeball_Horizontal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RightEyeball_Horizontal_PRTDSI__OUT_SEL0       (* (reg8 *) RightEyeball_Horizontal__PRTDSI__OUT_SEL0) 
#define RightEyeball_Horizontal_PRTDSI__OUT_SEL1       (* (reg8 *) RightEyeball_Horizontal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RightEyeball_Horizontal_PRTDSI__SYNC_OUT       (* (reg8 *) RightEyeball_Horizontal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RightEyeball_Horizontal__SIO_CFG)
    #define RightEyeball_Horizontal_SIO_HYST_EN        (* (reg8 *) RightEyeball_Horizontal__SIO_HYST_EN)
    #define RightEyeball_Horizontal_SIO_REG_HIFREQ     (* (reg8 *) RightEyeball_Horizontal__SIO_REG_HIFREQ)
    #define RightEyeball_Horizontal_SIO_CFG            (* (reg8 *) RightEyeball_Horizontal__SIO_CFG)
    #define RightEyeball_Horizontal_SIO_DIFF           (* (reg8 *) RightEyeball_Horizontal__SIO_DIFF)
#endif /* (RightEyeball_Horizontal__SIO_CFG) */

/* Interrupt Registers */
#if defined(RightEyeball_Horizontal__INTSTAT)
    #define RightEyeball_Horizontal_INTSTAT            (* (reg8 *) RightEyeball_Horizontal__INTSTAT)
    #define RightEyeball_Horizontal_SNAP               (* (reg8 *) RightEyeball_Horizontal__SNAP)
    
	#define RightEyeball_Horizontal_0_INTTYPE_REG 		(* (reg8 *) RightEyeball_Horizontal__0__INTTYPE)
#endif /* (RightEyeball_Horizontal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RightEyeball_Horizontal_H */


/* [] END OF FILE */
