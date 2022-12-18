/*****************************************************************************************************************************************************
 *	Module: main of MC1
 *
 *	File name: main1.c
 *
 *	Description: main file of MC1
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include <avr/io.h>
#include "my_uart.h"
#include "my_keypad.h"
#include "my_lcd.h"
#include "my_gpio.h"
#include "my_timer.h"
#include "func_main1.h"
#include <util/delay.h>

/* Used to count time using the timer. */
uint16 tx_timer_counts = 0;

int main(void)
{
	/*
	 * Configure the UART:
	 * (1) Configure the bit rate.
	 * (2) Configure the parity mode.
	 * (3) Configure the number of stop bits.
	 * (4) Configure the number of bits mode.
	 */
	UART_ConfigType uart_send_config = {9600, DISABLED, ONE_BIT, EIGHT_BITS};
	/*
	 * Configure the timer:
	 * (1) Configure the operating mode.
	 * (2) Configure the pre-scaler.
	 * (3) Configure the initial value.
	 * (4) Add the timer_ID.
	 * (5) Configure the comparing value, if compare mode.
	 * NB: For 1024 pre-scaler and 8Mhz frequency. Each overflow -> 0.032768 second, so we need 458 overflows to count 15 seconds.
	 */
	Timer_Config tx_config = {COMP, PS_1024, 0, TIMER1, 8000 };		/* Each interrupt is equivalent to a second */
	/* A string to write the 5-digits password and the enter ('=') in. */
	uint8 keypad_press[6];
	/* A variable used to detect whether the passwords match or not. */
	uint8 match_check = 0;
	/* A variable to find whether the user chose '+' or '-'. */
	uint8 door_options = 0;
	/* A variable used to know if the password is correct or not. */
	uint8 correct_pass;
	/* A variable to enable the buzzer at a certain condition */
	uint8 buzz = 0;
	/* Enable the global interrupts */
	SREG |= ( 1 << 7 );
	/* Initialize the required modules. */
	UART_init( &uart_send_config );
	LCD_init();

	/* Don't skip creating the password, unless matching happens. */
	do
	{
		Create_Pass( keypad_press, &match_check );
	}
	while( match_check != MATCH_COMPLETE );
	/* NB: When the 2 passwords match, the 2nd MC saves the pass in the EEPROM automatically. */

	while(1)
	{
		/* Clear the LCD. */
		LCD_clearScreen();
		LCD_displayString( "+: Open the door" );
		LCD_displayStringRowColumn( 2, 0, "-: Change pass" );
		/* Do nothing until the user enters the correct button */
		do
		{
			door_options = KEYPAD_getPressedKey();
		}
		while( !( ( door_options == '+' ) | ( door_options == '-' ) ) );

		/* Tell the second MC what the user chose. */
		UART_sendByte( door_options );
		_delay_ms(10);

		switch( door_options )
		{
		case '+':
			correct_pass = Check_Pass( keypad_press, ENTERING );
			if( correct_pass == MATCH_COMPLETE )
			{
				/* Because the user may enter an incorrect pass for 1 or 2 times before getting it right. */
				buzz = 0;
				LCD_clearScreen();
				LCD_displayString( "Door is opening " );
				/* Send the call back function to the timer */
				TIMER_setCallBack( Display1_TxCallBack, TIMER1, COMP );
				/* Start the timer */
				Timer_Init( &tx_config );
				/* Wait x seconds */
				while( tx_timer_counts != 33 )
				{

				}
				tx_timer_counts = 0;
			}
			else if( correct_pass == MISS_MATCH )
			{
				buzz++;
				LCD_clearScreen();
				if( buzz != 3 )
				{
				LCD_displayString( "Incorrect pass" );
				_delay_ms(2000);
				}
				if( buzz == 3 )
				{
					buzz = 2;
					LCD_displayString( "Door is disabled" );
					/* Send the call back function to the timer */
					TIMER_setCallBack( Display2_TxCallBack, TIMER1, COMP );
					/* Start the timer */
					Timer_Init( &tx_config );
					/* Wait x seconds */
					while( tx_timer_counts != 60 )
					{

					}
					tx_timer_counts = 0;
				}
			}
			break;
		case '-':
		{
			correct_pass = Check_Pass( keypad_press, CHANGING );
			if( correct_pass == MATCH_COMPLETE )
			{
				/* Because the user may enter an incorrect pass for 1 or 2 times before getting it right. */
				buzz = 0;
				LCD_clearScreen();
				do
				{
					Create_Pass( keypad_press, &match_check );
				}
				while( match_check != MATCH_COMPLETE );
				LCD_displayString( "Pass Changed" );
				_delay_ms(2000);
			}
			else if( correct_pass == MISS_MATCH )
			{
				buzz++;
				LCD_clearScreen();
				if( buzz != 3 )
				{
				LCD_displayString( "Incorrect pass" );
				_delay_ms(2000);
				}
				if( buzz == 3 )
				{
					buzz = 2;
					/* Send the call back function to the timer */
					TIMER_setCallBack( Display2_TxCallBack, TIMER1, COMP );
					/* Start the timer */
					Timer_Init( &tx_config );
					LCD_displayString( "Door is disabled" );
					/* Wait x seconds */
					while( tx_timer_counts != 60 )
					{

					}
					tx_timer_counts = 0;
				}
			}
		}
		}
	}
}

/*
 * Description: Call back function of any timer.
 */
void Display1_TxCallBack( void )
{
	tx_timer_counts++;
	/* Wait x1 seconds */
	if( tx_timer_counts == 15 )
	{
		LCD_clearScreen();
	}
	/* Wait x2+x1 seconds */
	else if( tx_timer_counts == 18 )
	{
		LCD_displayString( "Door is closing" );
	}
	/* Wait x3+x2+x1 seconds */
	else if ( tx_timer_counts == 33)
	{
		/* Shut-down the timer */
		TIMER_intDeInit(TIMER1);
	}
}

void Display2_TxCallBack( void )
{
	tx_timer_counts++;
	if ( tx_timer_counts == 34 )
	{
		/* Shut-down the timer */
		TIMER_intDeInit(TIMER1);
	}
}
