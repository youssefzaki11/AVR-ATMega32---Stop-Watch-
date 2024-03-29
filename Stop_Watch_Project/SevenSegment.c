/*****************************************************************************************************************
 * File Name: SevenSegment.c
 * Date: 4/8/2023
 * Driver: 7-Segment Driver Source File
 * Author: Youssef Zaki
 ****************************************************************************************************************/
#include "SevenSegment.h"
#include "Common_Macros.h"
#include "GPIO.h"

/****************************************************************************************
 *                                     Functions Definitions                            *
 ****************************************************************************************/

/*
 * Description:
 * Initializing the Seven Segment Module in two cases:
 * 1. Without Decoder (Common Cathode)
 * 2. With Decoder (Common Anode)
 */
void SevenSegment_Init(void)
{

#if (SEVEN_SEGMENT_MODE == SEVEN_SEGMENT_WITHOUT_DECODER)

	/* Setup the pins from 1 to 7 as output pins and enable them to be connected with 7-Segment */
	GPIO_SetupPortDirection(SEVEN_SEGMENT_PORT_ID, OUTPUT_PORT);
	GPIO_WritePORT(SEVEN_SEGMENT_PORT_ID, 0xFE);

	/* Setup the common pin which enables the common cathode 7-segment */
	GPIO_SetupPinDirection(COMMON_PIN_PORT_ID, COMMON_PIN_PIN_ID, OUTPUT_PIN);
	GPIO_WritePin(COMMON_PIN_PORT_ID, COMMON_PIN_PIN_ID, LOGIC_HIGH);

#elif (SEVEN_SEGMENT_MODE == SEVEN_SEGMENT_WITH_DECODER)

	/* Setup the 4 pins required to connect with decoder as output pins */
	GPIO_SetupPinDirection(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN0_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_ID, OUTPUT_PIN);
	GPIO_SetupPinDirection(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_ID, OUTPUT_PIN);

#endif
}

#if (SEVEN_SEGMENT_MODE == SEVEN_SEGMENT_WITHOUT_DECODER)

/*
 * Description:
 * Display of Seven Segment Value without using a decoder.
 */
void SevenSegment_Display_Without_Decoder(uint8 count)
{
	/*
	 * Common cathode seven segment with Etamini32 board
	 * 0 -> PA0
	 * a -> PA1
	 * b -> PA2
	 * c -> PA3
	 * d -> PA4
	 * e -> PA5
	 * f -> PA6
	 * g -> PA7
	 */
	switch(count)
	{
	case 0:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_LOW);
		break;
	case 1:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_LOW);
		break;
	case 2:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_HIGH);
		break;
	case 3:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_HIGH);
		break;
	case 4:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_HIGH);
		break;
	case 5:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_HIGH);
		break;
	case 6:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_HIGH);
		break;
	case 7:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_LOW);
		break;
	case 8:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_HIGH);
		break;
	case 9:
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN1_a, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN2_b, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN3_c, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN4_d, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN5_e, LOGIC_LOW);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN6_f, LOGIC_HIGH);
		GPIO_WritePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_PIN7_g, LOGIC_HIGH);
		break;
	}

}
#endif
