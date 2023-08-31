/*************************************************************************************************************
 * [File]: StopWatchApplication.c
 * [Date]: 18/8/2023
 * [Objective]: Application for Stop-Watch based on six of seven segments to display the time.
 * [Drivers]: GPIO - External Interrupts - Timers - 7-Segment
 * [Author]: Youssef Ahmed Zaki
 *************************************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Common_Macros.h"
#include <util/delay.h>

/* MCAL Layer */
#include "GPIO.h"
#include "INT.h"
#include "TIMER1.h"

/* HAL Layer */
#include "SevenSegment.h"

/************************************************************************************************************
 *                                                Global Variables                                          *
 ************************************************************************************************************/
unsigned char SEC = 0;
unsigned char MIN = 0;
unsigned char HOUR = 0;

/************************************************************************************************************
 *                                                 STOP-WATCH TIMER                                         *
 ************************************************************************************************************/
/* ISR Code of the Timer1 */
ISR(TIMER1_COMPA_vect)
{
	SEC++;
	if (SEC == 60)
	{
		SEC = 0;
		MIN++;
	}
	if (MIN == 60)
	{
		MIN = 0;
		HOUR++;
	}
	if (HOUR == 24)
	{
		SEC = 0;
		MIN = 0;
		HOUR = 0;
	}
}

/************************************************************************************************************
 *                                                        RESET                                             *
 ************************************************************************************************************/
/* Interrupt0 ISR */
ISR(INT0_vect)
{
	SEC = 0;
	MIN = 0;
	HOUR = 0;
}

/************************************************************************************************************
 *                                                        PAUSE                                             *
 ************************************************************************************************************/
/* Interrupt1 ISR */
ISR(INT1_vect)
{
	/* As TCCR1B register contains clock bits, so make it Zero stops the timer */
	TCCR1B = 0;
}

/************************************************************************************************************
 *                                                        RESUME                                            *
 ************************************************************************************************************/
/* Interrupt2 ISR*/
ISR(INT2_vect)
{
	/* re-enable the TCCR1B register to continue counting */
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
}

/************************************************************************************************************
 *                                                    Main Application                                      *
 ************************************************************************************************************/
int main (void)
{
	/* Let pins [0:5] in PORTA as output pins to select the required 7-Segment to display the digit */
	GPIO_SetupPinDirection(PORTA_ID, PIN0_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(PORTA_ID, PIN1_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(PORTA_ID, PIN2_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(PORTA_ID, PIN3_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(PORTA_ID, PIN4_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(PORTA_ID, PIN5_ID, OUTPUT_PIN);

	/* INT0 and INT2 have "internal pull-up resistors", so we need to enable this pins to give them power */
	GPIO_WritePin(PORTD_ID, PIN2_ID, LOGIC_HIGH);
	GPIO_WritePin(PORTB_ID, PIN2_ID, LOGIC_HIGH);

	/*
	 * Timer1 Configuration:
	 * Initial Value = 0
	 * Compare Value = 1000 (to increment up to 1 second)
	 * Pre-scaler = F_CPU/1024
	 * Timer1 Mode: CTC Mode (TOP value in OCR1A Register)
	 * Tick of timer is every "one second" (T-timer)
	 */
	Timer1_ConfigType Timer1_Config = {0, 1000, Prescaler_1024, CTC_4};

	/* MCAL Drivers Initialization */
	INT0_Init(INT0_FALLING_EDGE);
	INT1_Init(INT1_RISING_EDGE);
	INT2_Init(INT2_FALLING_EDGE);
	Timer1_NonPWm_Mode_Init(&Timer1_Config);

	/* HAL Drivers Initialization */
	SevenSegment_Init();

	/* Activation of Global Interrupt Enable Bit (I-bit) to activate the interrupts */
	SET_BIT(SREG, PIN7_ID);

	while (1)
	{
		/*
		 * Loop on all six of 7-segments to enable them all time and display the required number on the selected one.
		 * Activate the required pin to select the required 7-segment.
		 * Display the required number on the required 7-segment.
		 * Delay 4 ms to prevent possible noises on 7-segment Screen.
		 */
		PORTA = (1<<PA0);
		PORTC = ((PORTC & 0xF0) | (SEC % 10));
		_delay_ms(4);
		PORTA = (1<<PA1);
		PORTC = ((PORTC & 0xF0) | (SEC / 10));
		_delay_ms(4);
		PORTA = (1<<PA2);
		PORTC = ((PORTC & 0xF0) | (MIN % 10));
		_delay_ms(4);
		PORTA = (1<<PA3);
		PORTC = ((PORTC & 0xF0) | (MIN / 10));
		_delay_ms(4);
		PORTA = (1<<PA4);
		PORTC = ((PORTC & 0xF0) | (HOUR % 10));
		_delay_ms(4);
		PORTA = (1<<PA5);
		PORTC = ((PORTC & 0xF0) | (HOUR / 10));
		_delay_ms(4);
	}
}


