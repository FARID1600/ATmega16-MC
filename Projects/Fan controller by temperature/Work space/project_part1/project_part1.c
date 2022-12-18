/********************************************************************************************************************
 *	Module: main
 *
 *	File name: project_part1.c
 *
 *	Description: Combine the project files to work
 *
 *	Author: FARID
 *
 *******************************************************************************************************************/

#include "my_lcd.h"
#include "my_adc.h"
#include "lm35_sensor.h"
#include "my_motor.h"
#include "pwm.h"

int main(void)
{
	/* A variable used to store the temperature sensor readings */
	uint8 current_temp;
	/* Initialize config variable of type structure */
	ADC_ConfigType config = {HALF_AVCC, EIGHT};
	/* This step is not important as the PWM funcion is used within the motor files */
	PWM_Timer0_Start( 0 );
	/* Initialize the DC motor */
	DcMotor_Init();
	/* Initialize the LCD */
	LCD_init();
	/* Sens the declared structure to the ADC init function  */
	ADC_init( &config );
	LCD_displayString( "Temp. =    C" );
	while(1)
	{
		current_temp = LM35_getTemperature();
		/* Let the motor work before displaying the LCD as it has more priority */
		if ( current_temp < 30 )
			DcMotor_Rotate( STOP, 0 );
		else if ( current_temp < 60 )
			DcMotor_Rotate( CW, 25 );
		else if ( current_temp < 90 )
			DcMotor_Rotate( CW, 50 );
		else if ( current_temp < 120 )
			DcMotor_Rotate( CW, 75 );
		else if ( current_temp >= 120 )
			DcMotor_Rotate( CW, 100 );
		/* move the cursor 2 steps after the = sign */
		LCD_moveCursor( 0, 8 );
		/* Display the temperature sensor */
		LCD_intgerToString( current_temp );
		/* These if condition are used for proper displaying after shifting from 3 displayed numbers to less */
		if( current_temp < 100)
			LCD_displayCharacter( ' ' );
		if( current_temp < 10)
			LCD_displayCharacter( ' ' );
	}
}
