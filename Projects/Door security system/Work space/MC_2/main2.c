/*****************************************************************************************************************************************************
 *	Module: main of MC2
 *
 *	File name: main2.c
 *
 *	Description: main file of MC2
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include <avr/io.h>
#include "my_uart.h"
#include "my_gpio.h"
#include "my_i2c.h"
#include "my_motor.h"
#include "eeprom.h"
#include "my_timer.h"
#include "func_main2.h"
#include <util/delay.h>

/* Used to count time using the timer. */
uint16 rx_timer_counts = 0;

int main(void)
{
	/*
	 * Configure the UART:
	 * (1) Configure the bit rate.
	 * (2) Configure the parity mode.
	 * (3) Configure the number of stop bits.
	 * (4) Configure the number of bits mode.
	 */
	UART_ConfigType uart_receive_config = {9600, DISABLED, ONE_BIT, EIGHT_BITS};
	/*
	 * Configure the timer:
	 * (1) Configure the operating mode.
	 * (2) Configure the pre-scaler.
	 * (3) Configure the initial value.
	 * (4) Add the timer_ID.
	 * (5) Configure the comparing value, if compare mode.
	 */
	Timer_Config rx_config = {COMP, PS_1024, 0, TIMER1, 8000 };		/* Each interrupt is equivalent to a second */
	/*
	 * Configure the I2C:
	 * (1) Configure the bit rate.
	 * (2) Configure the address.
	 */
	TWI_CongigType twi_config = {BRATE_400K, 0x01};
	TWI_init( &twi_config );
	/* Array to receive password from MC1. */
	uint8 received_pass[5];
	/* Array to connect password to EEPROM. */
	uint8 comp_pass[5];
	/* A variable to find whether the user chose '+' or '-'. */
	uint8 user_choice = 0;
	/* A variable which identifies whether the 2 passwords are matching or not. */
	uint8 pass_match = 0;
	/* A variable to enable the buzzer at a certain condition */
	uint8 buzz = 0;
	/* Configure the buzzer pin as output pin */
	GPIO_setupPinDirection( PORTD_ID, PIN7_ID, PIN_OUTPUT);
	/* Turn the buzzer off */
	GPIO_writePin( PORTD_ID, PIN7_ID, LOGIC_LOW );
	/* Enable the global interrupts */
	SREG |= ( 1 << 7 );
	/* Initialize the required modules. */
	UART_init( &uart_receive_config );
	DcMotor_Init();
	/* Compare the 2 passwords received from the user */
	Comp_Passwords( received_pass, comp_pass);
	/* If the while loop is skipped, then the passwords match. So, save the password to the EEPROM. */
	Save_PassToMem( received_pass );
	while( 1 )
	{
		/* Variable to get notified by the user choice */
		user_choice = UART_receiveByte();
		switch( user_choice )
		{
		case '+':
			pass_match = Check_Pass( received_pass, comp_pass );
			if( pass_match == MATCH_COMPLETE )
			{
				/* Because the user may enter an incorrect pass for 1 or 2 times before getting it right. */
				buzz = 0;
				/* Rotate the motor in the clock wise direction */
				DcMotor_Rotate( CW );
				/* Send the call back function to the timer */
				TIMER_setCallBack( Motor_RxCallBack, TIMER1, COMP );
				/* Start the timer */
				Timer_Init( &rx_config );
				/* Wait x seconds */
				while( rx_timer_counts != 33 )
				{

				}
				rx_timer_counts = 0;
			}
			else if( pass_match == MISS_MATCH )
			{
				buzz++;
				if( buzz == 3 )
				{
					buzz = 2;
					GPIO_writePin( PORTD_ID, PIN7_ID, LOGIC_HIGH );
					/* Send the call back function to the timer */
					TIMER_setCallBack( Buzzer_RxCallBack, TIMER1, COMP );
					/* Start the timer */
					Timer_Init( &rx_config );
					/* Wait x seconds */
					while( rx_timer_counts != 60 )
					{

					}
					rx_timer_counts = 0;
				}
			}
			break;
		case '-':
			pass_match = Check_Pass( received_pass, comp_pass );
			if( pass_match == MATCH_COMPLETE )
			{
				/* Because the user may enter an incorrect pass for 1 or 2 times before getting it right. */
				buzz = 0;
				Comp_Passwords( received_pass, comp_pass);
				Save_PassToMem( received_pass );
			}
			else if( pass_match == MISS_MATCH )
			{
				buzz++;
				if( buzz == 3 )
				{
					/* to buzz again if the user entered a wrong pass after the buzzer stops. */
					buzz = 2;
					GPIO_writePin( PORTD_ID, PIN7_ID, LOGIC_HIGH );
					/* Send the call back function to the timer */
					TIMER_setCallBack( Buzzer_RxCallBack, TIMER1, COMP );
					/* Start the timer */
					Timer_Init( &rx_config );
					/* Wait x seconds */
					while( rx_timer_counts != 60 )
					{

					}
					rx_timer_counts = 0;
				}
			}
		}
	}
}

void Motor_RxCallBack( void )
{
	rx_timer_counts++;
	/* Wait x1 seconds */
	if( rx_timer_counts == 15 )
		DcMotor_Rotate( STOP );
	/* Wait x2+x1 seconds */
	else if( rx_timer_counts == 18 )
		DcMotor_Rotate( ACW );
	/* Wait x3+x2+x1 seconds */
	else if ( rx_timer_counts == 33)
	{
		/* Shut-down the motor and the timer */
		DcMotor_Rotate( STOP );
		TIMER_intDeInit(TIMER1);
	}
}

void Buzzer_RxCallBack( void )
{
	rx_timer_counts++;
	if ( rx_timer_counts == 33 )
	{
		/* Shut-down the buzzer and the timer */
		GPIO_writePin( PORTD_ID, PIN7_ID, LOGIC_LOW );
		TIMER_intDeInit(TIMER1);
	}
}

