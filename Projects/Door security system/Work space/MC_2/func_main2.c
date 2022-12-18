/*****************************************************************************************************************************************************
 *	File name: func_main1.c
 *
 *	Description: MC1 main stuff
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include "func_main2.h"
#include "my_uart.h"
#include "my_gpio.h"
#include "my_timer.h"
#include "eeprom.h"
#include <util/delay.h>

/*****************************************************************************************************************************************************
 *
 * 																		 FUNCTIONS
 *
*****************************************************************************************************************************************************/

/*
 * Description: Get the user's pass and the pass saved in the EEPROM, then use Check_5Digits function.
 */
uint8 Check_Pass( uint8 *pass1, uint8 *pass2 )
{
	uint8 test_result;
	Receive_PassFromMC1( pass1 );
	Read_PassFromMem ( pass2 );
	/* Compare the 2 passwords. */
	test_result = Check_5Digits( pass1, pass2 );
	/* Send the compare result. */
	UART_sendByte( test_result );
	_delay_ms(10);
	return test_result;
}

/*
 * Description: Get 2 passwords from the user, then use Check_5Digits function.
 */
void Comp_Passwords( uint8 *pass1, uint8 *pass2 )
{
	uint8 pass_match;
	/* don't skip the while loop that checks the password, until the 5 digits match. */
	do
	{
		/* Save the first password in a string. */
		Receive_PassFromMC1( pass1 );
		/* Save the second password in another string. */
		Receive_PassFromMC1( pass2 );
		/* Add the comparing result in the variable. */
		pass_match = Check_5Digits( pass1, pass2 );
		/* Tell the first MC whether the passwords match or not. */
		UART_sendByte( pass_match );
		_delay_ms(10);
	}
	while( pass_match != MATCH_COMPLETE );
}

/*
 * Description: Compare each digit in any 2 passwords, passed as arguments.
 */
uint8 Check_5Digits( uint8 *pass1, uint8 *pass2 )
{
	uint8 match_iterator = 0, match_detector = 0;
	/* A for loop that calculates the number of matching digits in the password */
	for( match_iterator = 0; match_iterator < 5 ; match_iterator++ )
	{
		if( pass1[match_iterator] == pass2[match_iterator] )
		{
			match_detector++;
		}
	}
	if ( match_detector == 5 )
		return MATCH_COMPLETE;
	else
		return MISS_MATCH;
}

/*
 * Description: Save pass received from MC1 in the EEPROM.
 */
void Save_PassToMem( uint8 *pass )
{
	EEPROM_writeByte( 0x0300, pass[0] );		//change address
	_delay_ms(10);
	EEPROM_writeByte( 0x0310, pass[1] );
	_delay_ms(10);
	EEPROM_writeByte( 0x0320, pass[2] );
	_delay_ms(10);
	EEPROM_writeByte( 0x0330, pass[3] );
	_delay_ms(10);
	EEPROM_writeByte( 0x0340, pass[4] );
	_delay_ms(10);
}

/*
 * Description: Read the pass saved in the EEPROM to check whether the user's pass is correct or incorrect.
 */
void Read_PassFromMem ( uint8 *pass )
{
	EEPROM_readByte( 0x0300, &pass[0] );
	EEPROM_readByte( 0x0310, &pass[1] );
	EEPROM_readByte( 0x0320, &pass[2] );
	EEPROM_readByte( 0x0330, &pass[3] );
	EEPROM_readByte( 0x0340, &pass[4] );
}

/*
 * Description: Receive pass from MC1 to check or save.
 */
void Receive_PassFromMC1( uint8 *pass )
{
	pass[0] = UART_receiveByte();
	pass[1] = UART_receiveByte();
	pass[2] = UART_receiveByte();
	pass[3] = UART_receiveByte();
	pass[4] = UART_receiveByte();
}


/****************************************************************************************************************************************************/
