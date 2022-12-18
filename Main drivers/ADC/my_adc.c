/********************************************************************************************************************
 *	Module: ADC
 *
 *	File name: my_adc.c
 *
 *	Description: source file of the ADC
 *
 *	Author: FARID
 *
 *******************************************************************************************************************/

#include "my_adc.h"
#include <avr/io.h> /* To use the ADC Registers */
#include "my_macros.h"

/*********************************************************************************************************************
 *
 * 														 FUNCTIONS
 *
*********************************************************************************************************************/

#ifdef ADC_ENABLE_INT
ISR(ADC_vect)
{
	/*
	 * Some code
	 */
}
#endif

/*
 * Description: Initialize the ADC driver.
 */
void ADC_init( const ADC_ConfigType *Config_Ptr )
{
	ADMUX = 0; /* Just an initialization to get rid of using CLEAR_BIT() */
	/* NB: MUX4:0  = 00000 to choose channel 0 as initialization */
	/* NB: setting a register to 0 is not valid in all registers, as it may ruin some parts */
	/* Select the required operating voltage */

	/* Select the voltage reference */
	ADMUX = ( ADMUX & 0x3F ) | ( ( Config_Ptr -> Vref ) << 6 );

	/* Enable the ADC */
	SET_BIT( ADCSRA, ADEN );

	/* Enable interrupts if required */
#ifdef ADC_ENABLE_INT
	SET_BIT( ADCSRA, ADIE );
#else
	CLEAR_BIT( ADCSRA, ADIE );
#endif
	/* Choose the scaling factor */
	ADCSRA = ( ADCSRA & 0xF8 ) | ( Config_Ptr -> prescaler );
	/*
	 * NB: I didn't use the SFIOR register as we are using no auto triggering.
	 */
}

/*
 * Description: Read analog data from a certain ADC channel and convert it to digital.
 */
uint16 ADC_readChannel( uint8 channel_num )
{
	channel_num &= 0x07;		/* Channel number cannot exceed 7 (0-7) */
	ADMUX = ( ADMUX & 0xE0 ) | channel_num;
	SET_BIT( ADCSRA, ADSC ); /* Start conversion */
	while(BIT_IS_CLEAR( ADCSRA, ADIF ) ); /* Wait for conversion to complete (ADIF = 1) */
	SET_BIT( ADCSRA, ADIF ); /* Clear ADIF by writing 1 */
	return ADC;
}

/*******************************************************************************************************************/
