/*****************************************************************************************************************************************************
 *	File name: func_main1.c
 *
 *	Description: MC1 main stuff
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include "func_main1.h"
#include "my_uart.h"
#include "my_keypad.h"
#include "my_lcd.h"
#include "my_gpio.h"
#include "my_timer.h"
#include <util/delay.h>

/*****************************************************************************************************************************************************
 *
 * 																		 FUNCTIONS
 *
 *****************************************************************************************************************************************************/

/* A global variable to choose what do display after clearing the numbers written*/
uint8 clear_display = 0;

/*
 * Description: Function used to check that the entered password matches the saved one.
 */
uint8 Check_Pass( uint8 *pass, uint8 state )
{
	uint8 pass_check;
	LCD_clearScreen();
	if( state == ENTERING )
	{
		clear_display = 1;
		LCD_displayString( "Enter password" );
	}
	else
	{
		clear_display = 2;
		LCD_displayString( "Old password" );
	}
	LCD_moveCursor( 2, 0 );

	/* for not to display a minus or plus by mistake (The Enter_pass function asks for an input, so it may read my hold to '-' without a delay). */
	_delay_ms(400);
	/* Enter the old password */
	Enter_Pass( pass );
	/* Send the password to the second MC to compare it to that saved in its EEPROM. */
	Send_PassToMC2( pass );
	/* Find whether the 2 passwords match or not. */
	pass_check = UART_receiveByte();
	return pass_check;
}

/*
 * Description: Function used to send the password to the second MC, to save or to check.
 */
void Send_PassToMC2( uint8 *pass )
{
	uint8 pass_iterator = 0;
	for( pass_iterator = 0; pass_iterator < 5; pass_iterator++ )
	{
		UART_sendByte( pass[ pass_iterator ] );
		_delay_ms(10);
	}
}

/*
 * Description: Function used to create a new password.
 */
void Create_Pass( uint8 *pass, uint8 *Success )
{
	LCD_clearScreen();
	LCD_displayString( "Enter a password" );
	/* Function to store the password in the string, keypad_press. */
	Enter_Pass( pass );
	/* Send the password to compare with the next one. */
	Send_PassToMC2( pass );

	LCD_clearScreen();

	LCD_displayString( "Confirm password" );
	Enter_Pass( pass );
	/* Send the password to compare with the previous one. */
	Send_PassToMC2( pass );

	/* Receive the comparing result from the other MC */
	*Success = UART_receiveByte();
	/* If the 2-passwords match. */
	if( *Success == MATCH_COMPLETE )
	{
		LCD_clearScreen();
		/* Used to skip the while loop of the password creation. */
		*Success = MATCH_COMPLETE;
		LCD_displayString( "Matching success" );
	}
	else if ( *Success == MISS_MATCH )
	{
		LCD_clearScreen();
		LCD_displayString( "Matching failed" );
	}
	_delay_ms(2000);
}

/*
 * Description: Function used to get the password from the user.
 */
void Enter_Pass( uint8 *pass )
{
	uint8 pass_iterator = 0;
	/* pass_iterator<6 not 5 to check in the fifth digit if the user wants to clear the password */
	for( pass_iterator = 0; pass_iterator < 5; pass_iterator++ )
	{
		do{
			pass[ pass_iterator ] = KEYPAD_getPressedKey();
			/* This delay is used to display each half second only */
			_delay_ms(400);
			/* If ON/C button is pressed, clear the screen */
			if( pass[ pass_iterator ] == 13 /* ASCII of ON/C button */ )
			{
				LCD_clearScreen();
				if( clear_display == 0 )
					LCD_displayString( "Enter a password" );
				else if( clear_display == 1 )
				{
					LCD_displayString( "Enter password" );
					LCD_moveCursor( 2, 0 );
				}
				else if( clear_display == 2 )
				{
					LCD_displayString( "Old password" );
					LCD_moveCursor( 2, 0 );
				}
				/* A character which is > 9 for not to escape the do while loop and print pass[0]. */
				pass[0] = 10;
				/* Reset the for loop */
				pass_iterator = 0;
			}
		}
		while( pass[ pass_iterator ] > 9 );
		LCD_displayCharacter( '*' );
	}
	/* pass[5] is used to finish the function if the user pressed enter ('=') */
	while( pass[5] != '=' )
	{
		pass[5] = KEYPAD_getPressedKey();
		_delay_ms(400);
	}
	/* clear '=' from pass[5] for not to skip the previous while loop next function call. */
	pass[5] = '\0';
}

/****************************************************************************************************************************************************/
