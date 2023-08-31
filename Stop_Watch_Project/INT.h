/*******************************************************************************************************************
 * File Name: INT.h
 * Date: 15/7/2023
 * Driver: ATmega32 Interrupt Driver Header File
 * Author: Youssef Zaki
 ******************************************************************************************************************/
#include "Standard_Types.h"

#ifndef INT0_H_
#define INT0_H_

/****************************************************************************************
 *                                      Types Declaration                               *
 ****************************************************************************************/

/* ISC01, ISC00 Bits Enable/Disable in MCUCR Register */
typedef enum
{
	INT0_LOW_LEVEL, INT0_ANY_LOGICAL_CHANGE, INT0_FALLING_EDGE, INT0_RISING_EDGE
}INT0_MCUCR_Config;

/* ISC11, ISC10 Bits Enable/Disable in MCUCR Register */
typedef enum
{
	INT1_LOW_LEVEL, INT1_ANY_LOGICAL_CHANGE, INT1_FALLING_EDGE, INT1_RISING_EDGE
}INT1_MCUCR_Config;

/* ISC2 Bit Enable/Disable in MCUCSR Register */
typedef enum
{
	INT2_FALLING_EDGE, INT2_RISING_EDGE
}INT2_MCUCSR_Config;

/****************************************************************************************
 *                                      Functions Prototypes                            *
 ****************************************************************************************/

/* Description:
 * 1. Configure PIN 2 in PORTD to be input pin.
 * 2. Configure MCUCR Register bits 0 & 1 (ISC01 & ISC00) according to level or edges (rising or falling).
 * 3. Configure GICR Register bit no.6 (INT0) to enable the external INT0 Request.
 */
void INT0_Init(INT0_MCUCR_Config INT0_Config);

/* Description:
 * 1. Configure PIN 3 in PORTD to be input pin.
 * 2. Configure MCUCR Register bits 2 & 3 (ISC11 & ISC10) according to level or edges (rising or falling).
 * 3. Configure GICR Register bit no.7 (INT1) to enable the external INT1 Request.
 */
void INT1_Init(INT1_MCUCR_Config INT1_Config);

/*
 * Description:
 * 1. Configure Pin2 at PORTB to be input pin.
 * 2. It is recommended to first disable INT2 by clearing its Interrupt Enable bit in the GICR Register.
 * 3. Choose if the falling edge or rising edge activates the interrupt through ISC2 pin in MCUCSR Register.
 * 4. Configure GICR Register bit no.6 (INT2) to enable the external INT2 Request.
 */
void INT2_Init(INT2_MCUCSR_Config INT2_Config);

/* Description:
 * "Disable the  INT0"
 * Disable of external Interrupt INT0 Request in GICR Register
 */
void INT0_DeInit(void);

/* Description:
 * "Disable the  INT1"
 * Disable of external Interrupt INT1 Request in GICR Register
 */
void INT1_DeInit(void);

/*
 * Description:
 * Disable of external Interrupt INT2 Request in GICR Register
 */
void INT2_DeInit(void);

#endif /* INT0_H_ */
