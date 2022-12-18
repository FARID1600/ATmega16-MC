/*****************************************************************************************************************************************************
 *	Module: UART
 *
 *	File name: my_uart.h
 *
 *	Description: Header file of the UART
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#ifndef MY_KEYPAD_H_
#define MY_KEYPAD_H_

#include "std_types.h"

/*****************************************************************************************************************************************************
 *
 * 																		 TYPES DEFINISIONS
 *
 ****************************************************************************************************************************************************/

/* Choose the parity type */
typedef enum
{
	DISABLED, RESERVED, EVEN_PARITY, ODD_PARITY
}UART_ParityMode;

/* Choose the number of stop bits */
typedef enum
{
	ONE_BIT, TWO_BITS
}UART_StopBits;

/* #define NINE_BITS_MODE*/ /* Remove the comment off the #define if you're using 9-bits data (discussed in the following structure) */
typedef enum
{
	FIVE_BITS, SIX_BITS, SEVEN_BITS, EIGHT_BITS
	#ifdef NINE_BITS_MODE
	NINE_BITS
#endif
}UART_CharacterSize;

/* A structure to combine all the enums */
typedef struct
{
	uint32 baud_rate;
	UART_ParityMode	parity;
	UART_StopBits	stop;
	UART_CharacterSize	size;
}UART_ConfigType;

/*****************************************************************************************************************************************************
 *
 * 																	 FUNCTIONS PROTOTYPES
 *
*****************************************************************************************************************************************************/

void UART_init( const UART_ConfigType *Config_Ptr );

void UART_sendByte( const uint8 data );

uint8 UART_receiveByte( void );

void UART_sendString( const uint8 *Str );

void UART_receiveString( uint8 *Str );

/****************************************************************************************************************************************************/
#endif
