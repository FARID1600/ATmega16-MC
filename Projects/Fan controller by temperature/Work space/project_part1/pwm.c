/*********************************************************************************************************************
 *	File name: pwm.c
 *
 *	Description: part of the timer driver
 *
 *	Author: FARID
 *
 ********************************************************************************************************************/

#include "my_macros.h"
#include "my_gpio.h"
#include "pwm.h"
#include <avr/io.h>

/*********************************************************************************************************************
 *
 * 														 FUNCTIONS
 *
*********************************************************************************************************************/

/*
 * Description: Start the PWM to set the duty cycle.
 */
void PWM_Timer0_Start( uint8 duty_cycle )
{
	/* Initializing the timer value */
	TCNT0 = TIMER_INITIAL_VALUE;
	/* Set the compare value (duty_cycle/255)*100 is the actual duty percentage */
	OCR0 = duty_cycle;
	/* Set the pin as output */
	GPIO_setupPinDirection( PORTB_ID, PIN3_ID, PIN_OUTPUT );

	/* Fast PWM mode */
	SET_BIT( TCCR0, WGM00 );
	SET_BIT( TCCR0, WGM01 );

	/* Non-inverting mode */
	SET_BIT( TCCR0, COM01 );
	/* pre-scaler 8 (clk/8) */
	SET_BIT( TCCR0, CS01 );
}

/*******************************************************************************************************************/
