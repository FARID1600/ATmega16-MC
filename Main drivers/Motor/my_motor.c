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
#include "pwm.h"

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

	/* Define the initial state of the motor to be off */
	/* PORTB = ( PORTB & 0xFC ) | STOP; */
	/* The previous step maybe used, but it's not important in our project as it is used in the next function. */
}

/*
 * Description: Choose the required speed and direction of rotation.
 */
void DcMotor_Rotate( DcMotor_State state, uint8 speed )
{
	PORTB = ( PORTB & 0xFC ) | state;
	/* 2.55 so that the max speed 100 becomes the top timer count (255) as it counts 256 ticks from 0 -> 255 */
	PWM_Timer0_Start( speed * 2.55 );
}

/*******************************************************************************************************************/
