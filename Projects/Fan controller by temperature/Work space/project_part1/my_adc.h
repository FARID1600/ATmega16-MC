/*********************************************************************************************************************
 *	Module: ADC
 *
 *	File name: my_adc.h
 *
 *	Description: Header file of the ADC
 *
 *	Author: FARID
 *
 ********************************************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*********************************************************************************************************************
 *
 * 																		  DEFINISIONS
 *
*********************************************************************************************************************/

/* The ADC maximum value is 2^10 = 1024 (0 -> 1023) as it is 10 bits */
#define ADC_MAXIMUM_VALUE    1023
/* This value depends on the hardware */
#define ADC_REfERENCE_VOLT 	 2.56

/* Choose the required reference volatage suitable to the hardware */
typedef enum{
	VREF_OFF, AVCC, RESERVED, HALF_AVCC
}ADC_ReferenceVoltage;

/* Choose the pre-scaler */
typedef enum{
	TWO, TWO_AGAIN, FOUR, EIGHT, SIXTEEN, THIRTY_TWO, SIXTY_FOUR, ONE_TWENTY_EIGHT
}ADC_Prescaler;

/* A structure to capture all the required enums for this module */
typedef struct{
	ADC_ReferenceVoltage Vref;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*
 * Enable the ADC interrupts (ADIF).
*/
#define ADC_ENABLE_INT
/* Remove the undef if you want to enable interrupts */
#undef ADC_ENABLE_INT

/*********************************************************************************************************************
 *
 * 														FUNCTIONS PROTOTYPES
 *
*********************************************************************************************************************/

/*
 * Description: Initialize the ADC driver.
 */
void ADC_init( const ADC_ConfigType *Config_Ptr );

/*
 * Description: Read analog data from a certain ADC channel and convert it to digital.
 */
uint16 ADC_readChannel( uint8 channel_num );

/********************************************************************************************************************/
#endif
