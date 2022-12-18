/****************************************************************************************************************************************************
 *	Module: UART
 *
 *	File name: my_uart.c
 *
 *	Description: Source file of the UART
 *
 *	Author: FARID
 *
 ***************************************************************************************************************************************************/

#include <avr/io.h>
#include "my_uart.h"
#include "my_macros.h"

/*
 * Description: Initialize the UART.
 */
void UART_init( const UART_ConfigType *Config_Ptr )
{
	uint16 UBRR_value = 0;
	/* Enable the double transmission speed */
	UCSRA |= ( 1 << U2X );
	/* Enable the transmitter and receiver */
	UCSRB |= ( 1 << TXEN ) | ( 1 << RXEN );
	/*
	 * (1) Enable writing in the UCSRC register.
	 * (2) Configure the parity bit (Disable, even, odd).
	 * (3) Configure the stop bits (1 or 2).
	 * (4) Configure the character size.
	 */
	UCSRC |= ( 1 << URSEL ) | ( ( Config_Ptr -> parity ) << 4 ) | ( ( Config_Ptr -> stop ) << 3 ) | ( ( Config_Ptr -> size ) << 1 );
	/* Calculate the UBRR register value in the double speed mode. */
	UBRR_value = ( uint16 ) ( ( ( F_CPU / ( ( Config_Ptr -> baud_rate ) * 8UL ) ) ) - 1 );
	/*Assign the UBRR value correctly in the UBRRH and UBRRL registers by adding the 8_LSB to UBRRL and 4-MSB in UBRRH. */
	UBRRL = UBRR_value;
	UBRRH = ( UBRR_value >> 4 );
}

/*
 * Description: Send a byte to the receiver.
 */
void UART_sendByte( const uint8 data )
{
	/* Make sure that the UDR register is empty (the receiver have received the data). */
	while( BIT_IS_CLEAR( UCSRA, UDRE ) );
	/* Send the data to the UDRR register to get read by the receiver. */
	UDR = data;
}

/*
 * Description: Receive a byte from the transmitter.
 */
uint8 UART_receiveByte( void )
{
	/* This flag is set, when there is data to be received. */
	while( BIT_IS_CLEAR( UCSRA, RXC ) );
	/* Read the UDR data. The RXC flag is cleared automatically */
	return UDR;
}

/*
 * Description: Send a string to the receiver.
 */
void UART_sendString( const uint8 *Str )
{
	uint8 i = 0;
	/* Send the whole string */
	while ( Str[i] != '\0' )
	{
	UART_sendByte( Str[i] );
	i++;
	}
}

/*
 * Description: Receive a string from the transmitter.
 */
void UART_receiveString( uint8 *Str )
{
	uint8 i = 0;
	/* Receive the first byte to save time if we have only 1 character*/
	Str[i] = UART_receiveByte;
	/* Receive the whole string until '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	/* After receiving the whole string, replace the extra '#' by null */
	Str[i] = '\0';
}





