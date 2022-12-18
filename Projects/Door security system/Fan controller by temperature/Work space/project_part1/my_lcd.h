 /*******************************************************************************************************************
 *	Module: LCD
 *
 *	File name: my_lcd.h
 *
 *	Description: Header file of the LCD
 *
 *	Author: FARID
 *
 *******************************************************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/********************************************************************************************************************
 *
 * 																		  DEFINISIONS
 *
********************************************************************************************************************/
/* Define the mode */
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be equal to 4 or 8"
#endif

#if ( LCD_DATA_BITS_MODE == 4 )
#define LCD_LAST_PORT_PINS		/* Connect the 4-MSB of the data */
#undef LCD_LAST_PORT_PINS		/* Connect the 4-LSB of the data */

#ifdef LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID         PIN4_ID
#else
#define LCD_FIRST_DATA_PIN_ID         PIN0_ID
#endif

#endif

/* LCD HW Ports and Pins IDs */
#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_RW_PORT_ID                 PORTD_ID
#define LCD_RW_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTC_ID

/* LCD Commands */
#define LCD_ONE_LINE_EIGHT_BITS_MODE   0x30
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_ONE_LINE_FOUR_BITS_MODE	   0x20
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
/* Entry mode: Increment or decrement (I/D) the address counter after subsequent DD RAM read or write operations.
 * If S = 1 the display will be shifted. This makes it looks as if the cursor stands still and the display moves
 * when each character is written.
 */
#define LCD_ENTRY_MODE				   0x06
#define LCD_DISPLAY_OFF_CURSOR_OFF	   0X08
#define LCD_DISPLAY_ON_CURSOR_ON	   0X0E
#define LCD_DISPLAY_ON_CURSOR_OFF	   0X0C
#define LCD_DISPLAY_ON_CURSOR_BLINKING 0X0F
#define LCD_SHIFT_ENTIRE_DISPLAY_LEFT  0x18
#define LCD_SHIFT_ENTIRE_DISPLAY_RIGHT 0x1C
#define LCD_CURSOR_LEFT_BY_ONE_CHAR    0x10
#define LCD_CURSOR_RIGHT_BY_ONE_CHAR   0x14
#define LCD_CLEAR_COMMAND              0x01		/* Also clear DDRAM content with the screen */
#define LCD_SET_CURSOR_LOCATION        0x80		/* Set DDRAM address or cursor position on display */
/* Ptr to CGRAM: Set CGRAM address or set pointer to CGRAM location.
 * When we point to a character in the CGRAM, it will be display in the next display command.
 */
#define LCD_SET_PTR_TO_CGRAM_LOCATION  0x40
#define LCD_GO_TO_HOME                 0x02		/* Set DDRAM address to 00h and return cursor original position */
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E

/********************************************************************************************************************
 *
 * 													 FUNCTIONS PROTOTYPES
 *
********************************************************************************************************************/

/*
 * Description : Initialize the LCD.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init( void );

/*
 * Description : Send the required command to the screen.
 */
void LCD_sendCommand( uint8 command );

/*
 * Description : Display the required character on the screen.
 */
void LCD_displayCharacter( uint8 data );

/*
 * Description : Display the required string on the screen.
 */
void LCD_displayString( const char *Str );

/*
 * Description : Move the cursor to a specified row and column on the screen.
 */
void LCD_moveCursor( uint8 row, uint8 col );

/*
 * Description : Display the required string in a specified row and column on the screen.
 */
void LCD_displayStringRowColumn( uint8 row, uint8 col, const char *Str );

/*
 * Description : Display the required decimal value on the screen.
 */
void LCD_intgerToString( int data );

/*
 * Description : Send the clear screen command.
 */
void LCD_clearScreen( void );

/*******************************************************************************************************************/
#endif
