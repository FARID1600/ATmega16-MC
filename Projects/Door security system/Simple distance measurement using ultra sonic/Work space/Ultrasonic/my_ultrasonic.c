/*****************************************************************************************************************************************************
 *	Module: Ultra-sonic
 *
 *	File name: my_ultrasonic.c
 *
 *	Description: Source file of the ultra-sonic
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include <util/delay.h>
#include "my_ultrasonic.h"
#include "my_icu.h"
#include "my_gpio.h"

/**************************************** Global variables to use in the call back function ********************************************/

static uint8 edge_count = 0;
static uint16 distance, high = 0;

/****************************************************************************************************************************************************
 *
 * 																	  FUNCTIONS DEFINITIONS
 *
 ****************************************************************************************************************************************************/

/*
 * Description: Call back function to process the time with High, Low states and edges.
 */
void Ultrasonic_edgeProcessing( void )
{
	edge_count++;
	if( edge_count == 1 )
	{
		/* Clear the ex timer value to start couting from now */
		ICU_clearTimerValue();
		/* Trigger the edge detector as the next edge is falling */
		ICU_setEdgeDetectionType( FALLING_EDGE );
	}
	else if( edge_count == 2 )
	{
		/* Store the timer value at the high time */
		high = ICU_getInputCaptureValue();
		/* Trigger the edge detector as the next edge is rising */
		ICU_setEdgeDetectionType( RISING_EDGE );
		/* Clear timer value so that we can do something else after the icu phase */
		ICU_clearTimerValue();
	}
}

/*
 * Description: Initialize the ultra-sonic.
 */
void Ultrasonic_init( void )
{
	/*ICU driver, frequency : CPU /8, edge type : rising*/
	ICU_ConfigType config = {F_CPU_8, RISING_EDGE};
	/* Initialize the ICU */
	ICU_init( &config );
	/* Send the required call back function to the ICU */
	ICU_setCallBack( Ultrasonic_edgeProcessing );
	/* Set the trigger pin as output pin */
	GPIO_setupPinDirection( TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT );
	//GPIO_setupPinDirection( ECHO_PORT, ECHO_PIN, PIN_INPUT );
}

/*
 * Description: Trigger the ultra-sonic to generate the 8 pulses and calculate the distance then.
 */
void Ultrasonic_Trigger( void )
{
	GPIO_writePin( TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH );
	_delay_us(10);
	GPIO_writePin( TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW );
}

/*
 * Description: Used to store the distance in a uint16 variable.
 */
uint16 Ultrasonic_readDistance( void )
{
	Ultrasonic_Trigger();
	if( edge_count == 2 )
	{
		/* Clear counter so that we can use this function again */
		edge_count = 0;
		distance = ( high / 58 ) + 1;
	}
	return distance;
}
/***************************************************************************************************************************************************/
