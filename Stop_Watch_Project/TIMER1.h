/*******************************************************************************************************************
 * File Name: TIMER1.h
 * Date: 17/7/2023
 * Driver: ATmega32 Timer1 Driver Header File
 * Author: Youssef Zaki
 ******************************************************************************************************************/
#include "Standard_Types.h"

#ifndef TIMER1_H_
#define TIMER1_H_

/*******************************************************************************************
 *                                      Types Declaration                                  *
 *******************************************************************************************/

typedef enum
{
	No_Clock,
	Prescaler_1,
	Prescaler_8,
	Prescaler_64,
	Prescaler_256,
	Prescaler_1024,
	External_Clock_Falling_Edge,
	External_Clock_Rising_Edge
}Timer1_Prescaler;

typedef enum
{
	Normal_0,
	PWM_Phase_Correct_8_Bit_1,
	PWM_Phase_Correct_9_Bit_2,
	PWM_Phase_Correct_10_Bit_3,
	CTC_4,
	Fast_Pwm_8_Bit_5,
	Fast_Pwm_9_Bit_6,
	Fast_Pwm_10_Bit_7,
	PWM_Phase_and_Frequency_Correct_8,
	PWM_Phase_and_Frequency_Correct_9,
	PWM_Phase_Correct_10,
	PWM_Phase_Correct_11,
	CTC_12,
	Reserved_13,
	Fast_PWM_14,
	Fast_PWM_15
}Timer1_Mode;

typedef struct {
uint16 initial_value;
uint16 compare_value; /* it will be used in compare mode only. */
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * Initialization of Timer1 (Enable Timer1)
 * 1. Let the TCNT1 Register = The Start value of the timer1.
 * 2. Enable FOC1A bit in the TCCR1A Register.
 * 3. Configure TCCR1A & TCCR1B according to the required pre-scalar.
 * 4. Configure the TCCR1B Register according to the Timer1 Mode.
 * 5. Configure the TIMSK Register (Interrupt Mask) according to Timer1 Mode.
 * 6. In CTC Mode Let OCR1A = the compare value (TOP Value).
 */
void Timer1_NonPWm_Mode_Init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description:
 * The function responsible for trigger the Timer1 with the PWM Mode.
 * 1. Let the TCNT1A Register = The Start value of the timer.
 * 2. Disable FOC1A & FOC1B bits in the TCCR1A Register (FOC1A = 0, FOC1B = 0)
 * 3. Enable CS12:0 bits according to the required pre-scalar.
 * 4. Setup the direction for OC1A as output pin through the GPIO driver.
 * 5. Configuration the PWM Mode (Phase Correct or Fast)
 * 6. Setup the PWM mode with Non-Inverting.
 */
void Timer1_PWM_Mode_Init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description:
 * Function to
 * 1. calculate the OCR1A Value from required Duty Cycle.
 * 2. Put Compare and TOP values of (ICR1 or OCR1A) registers.
 */
void TIMER1_PWM_Start (uint16 Duty_Cycle);

/*
 * Description:
 * Function to disable the Timer1.
 */
void Timer1_DeInit(void);

/*
 * Description:
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
