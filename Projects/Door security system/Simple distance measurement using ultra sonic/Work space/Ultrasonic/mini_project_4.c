/*****************************************************************************************************************************************************
 *	File name: mini_project_4.c
 *
 *	Description: Project main file
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include "my_lcd.h"
#include "my_ultrasonic.h"
#include <util/delay.h>
#include <avr/io.h> /* To use the SREG register */

int main(void)
{
	/* Variable to read the distance between the ultrasonic and the obstacle*/
	uint16 us_distance;
	/* Enable the global interrupt */
	SREG |= (1<<7);
	/* Initialize the drivers */
	LCD_init();
	Ultrasonic_init();

	LCD_displayString( "Distance =    cm" );
	while(1)
	{
		/* Calculate the distance and store it in its variable */
		us_distance = Ultrasonic_readDistance();
		/* Move the cursor to write just before "cm" */
		LCD_moveCursor( 0, 11 );
		LCD_intgerToString( us_distance );
		/* To over write on the un-needed numbers */
		if( us_distance < 100)
		{
			LCD_displayCharacter( ' ' );
			if( us_distance < 10)
				LCD_displayCharacter( ' ' );
		}
	}
}
