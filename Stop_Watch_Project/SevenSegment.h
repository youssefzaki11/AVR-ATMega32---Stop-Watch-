/*****************************************************************************************************************
 * File Name: SevenSegment.h
 * Date: 4/8/2023
 * Driver: 7-Segment Driver Header File
 * Author: Youssef Zaki
 ****************************************************************************************************************/
#include "Standard_Types.h"

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#define SEVEN_SEGMENT_MODE  SEVEN_SEGMENT_WITH_DECODER

#if ((SEVEN_SEGMENT_MODE != SEVEN_SEGMENT_WITH_DECODER) || (SEVEN_SEGMENT_MODE != SEVEN_SEGMENT_WITHOUT_DECODER))

#error " There is only Seven segment with decoder or seven segment without decoder"

#endif

/******************************************************************************************
 *                                    Macros Definitions                                  *
 ******************************************************************************************/

/* Setup 7-Segment Modes */
#define SEVEN_SEGMENT_WITH_DECODER                    0x00
#define SEVEN_SEGMENT_WITHOUT_DECODER                 0x01

/* Setup Micro-Controller PORT to connect with 7-Segment */
#define SEVEN_SEGMENT_PORT_ID                        PORTC_ID

/* Setup Micro-controller pins*/
#if (SEVEN_SEGMENT_MODE == SEVEN_SEGMENT_WITH_DECODER)

#define SEVEN_SEGMENT_PIN0_ID                        PIN0_ID
#define SEVEN_SEGMENT_PIN1_ID                        PIN1_ID
#define SEVEN_SEGMENT_PIN2_ID                        PIN2_ID
#define SEVEN_SEGMENT_PIN3_ID                        PIN3_ID

#elif (SEVEN_SEGMENT_MODE == SEVEN_SEGMENT_WITHOUT_DECODER)

/* Define the common cathode pin which enables the seven segment */
#define COMMON_PIN_PORT_ID                          PORTC_ID
#define COMMON_PIN_PIN_ID                           PIN6_ID

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
#define SEVEN_SEGMENT_PIN1_a                        PIN1_ID
#define SEVEN_SEGMENT_PIN2_b                        PIN2_ID
#define SEVEN_SEGMENT_PIN3_c                        PIN3_ID
#define SEVEN_SEGMENT_PIN4_d                        PIN4_ID
#define SEVEN_SEGMENT_PIN5_e                        PIN5_ID
#define SEVEN_SEGMENT_PIN6_f                        PIN6_ID
#define SEVEN_SEGMENT_PIN7_g                        PIN7_ID

#endif

/*******************************************************************************************
 *                                      Functions Prototypes                               *
 *******************************************************************************************/

/*
 * Description:
 * Initializing the Seven Segment Module in two cases:
 * 1. Without Decoder (Common Cathode)
 * 2. With Decoder (Common Anode)
 */
void SevenSegment_Init(void);

/*
 * Description:
 * Display of Seven Segment Value without using a decoder.
 */
void SevenSegment_Display_Without_Decoder(uint8 count);

#endif /* SEVENSEGMENT_H_ */
