/*************************************************************************************************************
 * [File Name]: mini_proj2.c
 * [Author]: Youssef Zaki
 * [Date Created]: 28-Sep-2022
 * [Description]: Developing a system that controls the stop-watch time and displays it on 7-segments by using
 * GPIO, Timers, External Interrupts, and 7-Segment.
 * Micro-controller: ATmega32.
 *************************************************************************************************************/
#include <AVR/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* Definition of Seconds, Minutes and Hours variables */
unsigned char SEC = 0;
unsigned char MIN = 0;
unsigned char HOUR = 0;

/* Description of the Function:
 * 1. We Shall use F_timer = 1 Second, because every increment = 1 second in the stop watch
 * 2. from F_timer = (F_CPU)/2*N*(1+OCR1A), we get  OCR1A = 62500 at N = 1024
 * 3. So, we need the TCNT1 = Compare Match value = 1000 to count 1 second  */

/* Settings of Timer 1 - CTC Mode */
void Timer1_CTC (void)
{
	TCNT1 = 0; /* let the Timer 1 starts from ZERO */
	OCR1A = 1000; /* Compare Value to which the timer should rise a flag and counts again. */
	TCCR1A |= (1<<FOC1A); /* Enable Force Output Compare for Compare unit A */

	/* Configuration for Normal Mode:
	 * COM1A1 = 0, COM1A0 = 0, COM1B1 = 0, COM1B0 = 0
	 * Configuration for CTC Mode:
	 * WGM10 = 0, WGM11 = 0, WGM12 = 1 */

	TIMSK |= (1<<OCIE1A); /* Timer1, Output Compare A Match Interrupt Enable */

	/* Configuration of F_CPU/8 Pre-scalar for TCCR1B Register -> CS11 = 1, CS10 = 0, CS12 = 0 */
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
}

/* ISR Code of the Timer 1 of mode A */
ISR(TIMER1_COMPA_vect)
{
	SEC++;
	if (SEC == 60) /* Check if the seconds = 60 */
	{
		MIN++;
		SEC = 0;
	}
	if (MIN == 60) /* Check if the minutes = 60 */
	{
		HOUR++;
		MIN = 0;
	}
	if ( HOUR == 24) /*check if the clock becomes complete */
	{
		/* Repeat the timer */
		HOUR = 0;
	}
}
/************************************************************************************************************
                                           *                    *
                                           *        RESET       *
                                           *                    *
 ***********************************************************************************************************/

/* Settings of the interrupt 0 (INT0) */
void Init_INT0 (void)
{
	DDRD &= ~(1<<PD2); /* let pin 2 in PORTD as input pin */
	PORTD |= (1<<PD2); /* Enable pull up resistor at this pin */

	 /* Configuration of the MCUCR Register:
	  * Falling Edge: ISC01 = 1, ISC00 = 0
	  */
	MCUCR |= (1<<ISC01);

	/* Configuration of GICR (Control) Register:
	 * INT0 = 1
	 */
	GICR |= (1<<INT0);

	/* Configuration of SREG Register:
	 * I-Bit = 1 (Global Interrupt Enable)
	 */
	SREG |= (1<<7);
}

/* Set the ISR Code for INT0 */
ISR(INT0_vect)
{
	SEC = 0;
	MIN = 0;
	HOUR = 0;
}
/************************************************************************************************************
                                           *                    *
                                           *        PAUSE       *
                                           *                    *
 ***********************************************************************************************************/

/* Settings of the Interrupt 1 (INT1) */
void Init_INT1 (void)
{
	DDRD &= ~(1<<PD3); /* let pin 3 in PORTD as input pin */

	 /* Configuration of the MCUCR Register:
	  * Rising Edge: ISC11 = 1, ISC10 = 1
	  */
	MCUCR |= (1<<ISC10);
	MCUCR |= (1<<ISC11);

	/* Configuration of GICR (Control) Register:
	 * INT1 = 1
	 */
	GICR |= (1<<INT1);

	/* Configuration of SREG Register:
	 * I-Bit = 1 (Global Interrupt Enable)
	 */
	SREG |= (1<<7);
}

/* set the ISR for INT1 to Pause the Timer 1 */
ISR(INT1_vect)
{
	/* we can disable any register to disable the interrupt request */
	TCCR1B = 0;
}
/************************************************************************************************************
                                           *                    *
                                           *        RESUME      *
                                           *                    *
************************************************************************************************************/

/* Settings of the Interrupt 2 (INT2) */
void Init_INT2 (void)
{
	DDRB &= ~(1<<PB2); /* Make Pin 2 in PORTB as input pin  */
	PORTB |= (1<<PB2); /* give pin 2 in PORTB Logic 1 */

	 /* Configuration of the MCUCR Register:
	  * Falling Edge: ISC2 = 0 for Falling Edge
	  */
	MCUCSR &= ~(1<<ISC2);

	/* Configuration of GICR (Control) Register:
	 * INT2 = 1
	 */
	GICR |= (1<<INT2);

	/* Configuration of SREG Register:
	 * I-Bit = 1 (Global Interrupt Enable)
	 */
	SREG |= (1<<7);
}

/* set the ISR for INT2 to resume the counter */
ISR(INT2_vect)
{
	/* We can re-enable the register again to generate an interrupt request */
	TCCR1B |= ((1 << WGM12) | (1 << CS10) | (1 << CS12));
}
int main (void)
{
	Init_INT0();
	Init_INT1();
	Init_INT2();
	Timer1_CTC();

	DDRC |= 0x0F;   /* let the first 4 pins in PORTC as Output pins */
	DDRA |= 0x3F;   /* let the first 6 pins in PORTA as Output pins */
	SREG |= (1<<7);

	while (1)
	{
		/* Operating the timer by:
		 * continuous looping of all six 7-segments to be always ON
		 */
		PORTA = (1 << 0);
		PORTC = (PORTC & 0xF0) | (SEC % 10); /* to get the ones in sec */
		_delay_ms(4);
		PORTA = (1 << 1);
		PORTC = (PORTC & 0xF0) | (SEC / 10); /* to get the units in sec */
		_delay_ms(4);
		PORTA = (1 << 2);
		PORTC = (PORTC & 0xF0) | (MIN % 10); /* to get the ones in min */
		_delay_ms(4);
		PORTA = (1 << 3);
		PORTC = (PORTC & 0xF0) | (MIN / 10); /* to get the units in min */
		_delay_ms(4);
		PORTA = (1 << 4);
		PORTC = (PORTC & 0xF0) | (HOUR % 10); /* to get the ones in hour */
		_delay_ms(4);
		PORTA = (1 << 5);
		PORTC = (PORTC & 0xF0) | (HOUR / 10); /* to get the units in hour */
		_delay_ms(4);
	}
}

