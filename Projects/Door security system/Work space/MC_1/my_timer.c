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

static volatile void (*TIMER0_COMP)(void) = NULL_PTR;
static volatile void (*TIMER0_OVF)(void) = NULL_PTR;
static volatile void (*TIMER1_COMP)(void) = NULL_PTR;
static volatile void (*TIMER1_OVF)(void) = NULL_PTR;
static volatile void (*TIMER2_COMP)(void) = NULL_PTR;
static volatile void (*TIMER2_OVF)(void) = NULL_PTR;


/****************************************************************************************************************************************************
 *
 * 																		  ISR FUNCTIONS
 *
 ****************************************************************************************************************************************************/

/* Timer0 ISR for the overflow mode */
ISR( TIMER0_OVF_vect )
{
	if( TIMER0_OVF !=  NULL_PTR )
	{
		(*TIMER0_OVF)();
	}
}

/* Timer0 ISR for the compare mode */
ISR( TIMER0_COMP_vect )
{
	if( TIMER0_COMP !=  NULL_PTR )
	{
		(*TIMER0_COMP)();
	}
}

/* Timer1 ISR for the overflow mode */
ISR( TIMER1_OVF_vect )
{
	if( TIMER1_OVF !=  NULL_PTR )
	{
		(*TIMER1_OVF)();
	}
}

/* Timer0 ISR for the compare mode */
ISR( TIMER1_COMPA_vect )
{
	if( TIMER1_COMP !=  NULL_PTR )
	{
		(*TIMER1_COMP)();
	}
}

/* Timer2 ISR for the overflow mode */
ISR( TIMER2_OVF_vect )
{
	if( TIMER2_OVF !=  NULL_PTR )
	{
		(*TIMER2_OVF)();
	}
}

/* Timer2 ISR for the compare mode */
ISR( TIMER2_COMP_vect )
{
	if( TIMER2_COMP !=  NULL_PTR )
	{
		(*TIMER2_COMP)();
	}
}

/****************************************************************************************************************************************************
 *
 * 																	  FUNCTIONS DEFINITIONS
 *
 ****************************************************************************************************************************************************/

/* Function used by the ISR to call the call-back function in main */
void TIMER_setCallBack( void( *Timer_ptr )( void ), Timer_ID id, Timer_Mode mode )
{
	switch( id )
	{
	case TIMER0:
		if( mode == NORMAL )
		{
			/* Save the address of the Call back function in its global pointer */
			TIMER0_OVF = Timer_ptr;
		}
		else if( mode == COMP )
		{
			/* Save the address of the Call back function in its global pointer */
			TIMER0_COMP = Timer_ptr;
		}
		break;
	case TIMER1:
		if( mode == NORMAL )
		{
			/* Save the address of the Call back function in its global pointer */
			TIMER1_OVF = Timer_ptr;
		}
		else if( mode == COMP )
		{
			/* Save the address of the Call back function in its global pointer */
			TIMER1_COMP = Timer_ptr;
		}
		break;
	}
	if( ( id ) == TIMER0 )
	{

	}
	else if( ( id ) == TIMER2 )
	{
		if( ( mode ) == NORMAL )
		{
			/* Save the address of the Call back function in its global pointer */
			TIMER2_OVF = Timer_ptr;
		}
		else if( ( mode ) == COMP )
		{
			/* Save the address of the Call back function in its global pointer */
			TIMER2_COMP = Timer_ptr;
		}
	}
}

/*
 * Timer0 initial function:
 * NB: Set
 */
void Timer_Init( const Timer_Config *ConfigPtr )
{
	switch( ConfigPtr -> id )
	{
	case TIMER0:
		/* Set Timer initial value */
		TCNT0 = ( ConfigPtr -> init_value );
		/* Configure the timer control register
		 * (1) to get normal mode: shift zero for 3 times (do nothing). To get compare mode: shift 1 for 3 times.
		 * (2) Configure the pre-scaler.
		 * (3) Enable FOC0 to choose a non-PWM mode.
		 */
		TCCR0 = ( ( ConfigPtr -> mode ) << 3 ) | ( ConfigPtr -> prescaler ) | ( 1 << FOC0 );
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
		break;
	case TIMER1:
		/* Set Timer initial value */
		TCNT1 = ( ConfigPtr -> init_value );
		/* Enable FOC1A to choose a non-PWM mode. */
		SET_BIT( TCCR1A, FOC1A );
		/* Configure the timer control register
		 * (1) to get normal mode: shift zero for 3 times (do nothing). To get compare mode: shift 1 for 3 times.
		 * (2) Configure the pre-scaler.
		 */
		TCCR1B = ( ( ConfigPtr -> mode ) << 3 ) | ( ConfigPtr -> prescaler );
		if( ( ConfigPtr -> mode ) == NORMAL )
		{
			/* Enable Timer1 Overflow Interrupt */
			SET_BIT( TIMSK, TOIE1 );
		}
		else if( ( ConfigPtr -> mode ) == COMP )
		{
			/* Enable Timer1 compare Interrupt */
			SET_BIT( TIMSK, OCIE1A );
			/* Set Compare Value */
			OCR1A  = ( ConfigPtr -> comp_value );
		}
		break;
	case TIMER2:
		/* Set Timer initial value */
		TCNT2 = ( ConfigPtr -> init_value );
		/* Configure the timer control register
		 * (1) to get normal mode: shift zero for 3 times (do nothing). To get compare mode: shift 1 for 3 times.
		 * (2) Configure the pre-scaler.
		 * (3) Enable FOC2 to choose a non-PWM mode.
		 */
		TCCR2 = ( ( ConfigPtr -> mode ) << 3 ) | ( ConfigPtr -> prescaler ) | ( 1 << FOC0 );
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
		break;
	}
}

void TIMER_intDeInit( Timer_ID id )
{
	switch( id )
	{
	case TIMER0:
		/* Clear Timer0 Interrupts */
		TIMSK &= ~( 0x03 );
		break;
	case TIMER1:
		/* Clear Timer0 Overflow Interrupt */
		TIMSK &= ~( 0x3C );
		break;
	case TIMER2:
		/* Clear Timer0 Overflow Interrupt */
		TIMSK &= ~( 0xC0 );
		break;
	}
}

/**************************************************************************************************************************************************/
