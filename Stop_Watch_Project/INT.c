/*******************************************************************************************************************
 * File Name: INT.c
 * Date: 15/7/2023
 * Driver: ATmega32 Interrupt Driver Source File
 * Author: Youssef Zaki
 ******************************************************************************************************************/
#include <avr/io.h>
#include "INT.h"
#include "GPIO.h"
#include "Common_Macros.h"

/****************************************************************************************
 *                                      Functions Definitions                           *
 ****************************************************************************************/

/* Description:
 * 1. Configure PIN 2 in PORTD to be input pin.
 * 2. Configure MCUCR Register bits 0 & 1 (ISC01 & ISC00) according to level or edges (rising or falling).
 * 3. Configure GICR Register bit no.6 (INT0) to enable the external INT0 Request..
 */
void INT0_Init(INT0_MCUCR_Config INT0_Config)
{
	CLEAR_BIT(DDRD, PIN2_ID);

	switch (INT0_Config)
	{
	case INT0_LOW_LEVEL:
		CLEAR_BIT(MCUCR, ISC01);
		CLEAR_BIT(MCUCR, ISC00);
		break;

	case INT0_ANY_LOGICAL_CHANGE:
		CLEAR_BIT(MCUCR, ISC01);
		SET_BIT(MCUCR, ISC00);
		break;

	case INT0_FALLING_EDGE:
		SET_BIT(MCUCR, ISC01);
		CLEAR_BIT(MCUCR, ISC00);
		break;

	case INT0_RISING_EDGE:
		SET_BIT(MCUCR, ISC01);
		SET_BIT(MCUCR, ISC00);
		break;
	}
	SET_BIT(GICR, INT0);
}

/* Description:
 * 1. Configure PIN 3 in PORTD to be input pin.
 * 2. Configure MCUCR Register bits 2 & 3 (ISC11 & ISC10) according to level or edges (rising or falling).
 * 3. Configure GICR Register bit no.7 (INT1) to enable the external INT1 Request.
 */
void INT1_Init(INT1_MCUCR_Config INT1_Config)
{
	CLEAR_BIT(DDRD, PIN3_ID);

	switch (INT1_Config)
	{
	case INT1_LOW_LEVEL:
		CLEAR_BIT(MCUCR, ISC11);
		CLEAR_BIT(MCUCR, ISC10);
		break;

	case INT1_ANY_LOGICAL_CHANGE:
		CLEAR_BIT(MCUCR, ISC11);
		SET_BIT(MCUCR, ISC10);
		break;

	case INT1_FALLING_EDGE:
		SET_BIT(MCUCR, ISC11);
		CLEAR_BIT(MCUCR, ISC10);
		break;

	case INT1_RISING_EDGE:
		SET_BIT(MCUCR, ISC11);
		SET_BIT(MCUCR, ISC10);
		break;
	}
	SET_BIT(GICR, INT1);
}

/*
 * Description:
 * 1. Configure Pin2 at PORTB to be input pin.
 * 2. It is recommended to first disable INT2 by clearing its Interrupt Enable bit in the GICR Register.
 * 3. Choose if the falling edge or rising edge activates the interrupt through ISC2 pin in MCUCSR Register.
 * 4. Configure GICR Register bit no.6 (INT2) to enable the external INT2 Request.
 */
void INT2_Init(INT2_MCUCSR_Config INT2_Config)
{
	CLEAR_BIT(DDRB, PIN2_ID);

	CLEAR_BIT(GICR, INT2);

	MCUCSR = (MCUCSR & 0xBF) | (INT2_Config << ISC2);

	SET_BIT(GICR, INT2);
}

/* Description:
 * "Disable the  INT0"
 * Disable of external Interrupt INT0 Request in GICR Register
 */
void INT0_DeInit(void)
{
	CLEAR_BIT(GICR, INT0);
}

/* Description:
 * "Disable the  INT1"
 * Disable of external Interrupt INT1 Request in GICR Register
 */
void INT1_DeInit(void)
{
	CLEAR_BIT(GICR, INT1);
}

/*
 * Description:
 * Disable of external Interrupt INT2 Request in GICR Register
 */
void INT2_DeInit(void)
{
	CLEAR_BIT(GICR, INT2);
}
