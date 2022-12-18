/*****************************************************************************************************************************************************
 *	Module: TIMER
 *
 *	File name: my_timer.c
 *
 *	Description: source file of the timer
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include <avr/interrupt.h>
#include <avr/io.h>
#include "my_macros.h"

#include"my_timer.h"

/**************************************** Global variable to hold the address of the call back function ********************************************/

static volatile void (*TIMER_callBackPtr)(void) = NULL_PTR;

/****************************************************************************************************************************************************
 *
 * 																		  ISR FUNCTIONS
 *
 ****************************************************************************************************************************************************/

/* Timer0 ISR for the overflow mode */
ISR( TIMER0_OVF_vect )
{
	if( TIMER_callBackPtr !=  NULL_PTR )
	{
	(*TIMER_callBackPtr)();
	}
}

/* Timer0 ISR for the compare mode */
ISR( TIMER0_COMP_vect )				///////////////////////////////////////
{
	if( TIMER_callBackPtr !=  NULL_PTR )
	{
	(*TIMER_callBackPtr)();
	}
}

/* Timer2 ISR for the overflow mode */
ISR( TIMER2_OVF_vect )
{
	if( TIMER_callBackPtr !=  NULL_PTR )
	{
	(*TIMER_callBackPtr)();
	}
}

/* Timer2 ISR for the compare mode */
ISR( TIMER2_COMP_vect )
{
	if( TIMER_callBackPtr !=  NULL_PTR )
	{
	(*TIMER_callBackPtr)();
	}
}

/****************************************************************************************************************************************************
 *
 * 																	  FUNCTIONS DEFINITIONS
 *
 ****************************************************************************************************************************************************/

/* Function used by the ISR to call the call-back function in main */
void TIMER_setCallBack( void( *Timer_ptr )( void ) )
{
	/* Save the address of the Call back function in a global variable */
	TIMER_callBackPtr = Timer_ptr;
}

/*
 * Timer0 initial function:
 * NB: Set
 */
void Timer0_Init( const Timer_Config *ConfigPtr )
{
	/* Set Timer initial value to 0 */
	TCNT0 = ( ConfigPtr -> init_value );

	if( ( ConfigPtr -> mode ) == NORMAL )
	{
		/* Enable Timer0 Overflow Interrupt */
		SET_BIT( TIMSK, TOIE0 );
	}
	else if( ( ConfigPtr -> mode ) == COMP )
	{
		/* Enable Timer0 compare Interrupt */
		SET_BIT( TIMSK, OCIE0 );
		/* Set Compare Value */
		OCR0  = ( ConfigPtr -> comp_value );
	}

	/* Configure the timer control register
	 * (1) to get normal mode: shift zero for 3 times (do nothing). To get compare mode: shift 1 for 3 times.
	 * (2) Configure the pre-scaler.
	 * (3) Enable FOC0 to choose a non-PWM mode.
	 */
	TCCR0 = ( ( ConfigPtr -> mode ) << 3 ) | ( ConfigPtr -> prescaler ) | ( 1 << FOC0 );
}

/* Timer2 initial function */
void Timer2_Init( const Timer_Config *ConfigPtr )
{
	/* Set Timer initial value to 0 */
	TCNT2 = ( ConfigPtr -> init_value );

	if( ( ConfigPtr -> mode ) == NORMAL )
	{
		/* Enable Timer0 Overflow Interrupt */
		SET_BIT( TIMSK, TOIE2 );
	}
	else if( ( ConfigPtr -> mode ) == COMP )
	{
		/* Enable Timer0 compare Interrupt */
		SET_BIT( TIMSK, OCIE2 );
		/* Set Compare Value */
		OCR2  = ( ConfigPtr -> comp_value );
	}

	/* Configure the timer control register
	 * (1) to get normal mode: shift zero for 3 times (do nothing). To get compare mode: shift 1 for 3 times.
	 * (2) Configure the pre-scaler.
	 * (3) Enable FOC2 to choose a non-PWM mode.
	 */
	TCCR0 = ( ( ConfigPtr -> mode ) << 3 ) | ( ConfigPtr -> prescaler ) | ( 1 << FOC0 );
}

/**************************************************************************************************************************************************/
