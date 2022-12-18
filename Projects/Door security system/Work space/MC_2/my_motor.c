/********************************************************************************************************************
 *	Module: Motor
 *
 *	File name: my_motor.c
 *
 *	Description: source file of the motor
 *
 *	Author: FARID
 *
 *******************************************************************************************************************/

#include "my_gpio.h"
#include "my_motor.h"
#include <avr/io.h>

/********************************************************************************************************************
 *
 * 														 FUNCTIONS
 *
********************************************************************************************************************/

/*
 * Description: Start the motor.
 */
void DcMotor_Init(void)
{
	/* Configure the 2 output pins */
	GPIO_setupPinDirection( PORTB_ID, PIN0_ID, PIN_OUTPUT );
	GPIO_setupPinDirection( PORTB_ID, PIN1_ID, PIN_OUTPUT );

	/* Motor initial state is STOP. */
	PORTB = ( PORTB & 0xFC ) | STOP;
}

/*
 * Description: Choose the required speed and direction of rotation.
 */
void DcMotor_Rotate( DcMotor_State state )
{
	PORTB = ( PORTB & 0xFC ) | state;
}

/*******************************************************************************************************************/
