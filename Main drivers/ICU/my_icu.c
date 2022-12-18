/*****************************************************************************************************************************************************
 *	Module: KEYPAD
 *
 *	File name: KEYPAD.h
 *
 *	Description: Header file of the keypad
 *
 *	Author: FARID
 *
 ***************************************************************************************************************************************************/

#include "my_icu.h"
#include "my_macros.h"
#include <avr/io.h>
#include "my_gpio.h"
#include <avr/interrupt.h> /* For ICU ISR */

/**************************************** Global variable to hold the address of the call back function ********************************************/
static volatile void (*ICU_callBackPtr)(void) = NULL_PTR;
/*
 * NB: Volatile is used when we need to go and read the address pointed to by the pointer, or to change anything that's out of compiler reach. So
 * in general, use it with all pointers to functions.
 */

/****************************************************************************************************************************************************
 *
 * 																		  ISR FUNCTIONS
 *
****************************************************************************************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if( ICU_callBackPtr != NULL_PTR )
	{
		/* Call the Call Back function in the application after the edge is detected */
		( ICU_callBackPtr )(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/****************************************************************************************************************************************************
 *
 * 																	  FUNCTIONS DEFINITIONS
 *
****************************************************************************************************************************************************/

/*
 * Description: Function to initialize the ICU driver.
 */
void ICU_init(const Icu_ConfigType * Config_Ptr)
{
	/* Set the input pin (ICU is always set at PD6 pin) */
	GPIO_setupPinDirection( PORTD_ID, PIN6_ID, PIN_INPUT );

	/* NB: ICU always operates in normal  mode */

	/* Always set because there's no PWM mode */
	SET_BIT( TCCR1A, FOC1A );
	SET_BIT( TCCR1A, FOC1B);

	/* Set the edge type from the declared enum */
	TCCR1B = ( TCCR1B & 0xBF ) | ( ( Config_Ptr -> edge ) << 6 );

	/* Set the required clock */
	TCCR1B = ( TCCR1B & 0xF8) | ( Config_Ptr -> clock );

	/* Start counting from 0 */
	TCNT1 = 0;

	/* Enable the input capture interrupt flag */
	SET_BIT( TIMSK, TICIE1);

	/* It's updated to TCNT1 each time something happens to PD6 input pin */
	ICR1 = 0;
}

/*
 * Description: Function to update the callback function.
 */
void ICU_setCallBack(void(*ICU_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	ICU_callBackPtr = ICU_ptr;
}

/*
 * Description: Function to flip the edge detection of the ICU.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	/* Set the edge type from the declared enum */
	TCCR1B = ( TCCR1B & 0xBF ) | ( a_edgeType << 6 );
}

/*
 * Description: Function to copy the timer register, at the interrupt.
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the timer register.
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the ICU.
 */
void ICU_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	CLEAR_BIT( TIMSK, TICIE1 );
}
/**************************************************************************************************************************************************/


