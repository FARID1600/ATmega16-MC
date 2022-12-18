/*****************************************************************************************************************************************************
 *	Module: DIO
 *
 *	File name: my_gpio.h
 *
 *	Description: Header file of the DIO
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#ifndef MY_DIO_H_
#define MY_DIO_H_
#include "std_types.h"

/*****************************************************************************************************************************************************
 *
 * 														  				DEFINISIONS
 *
*****************************************************************************************************************************************************/

/* Ports and pins quantity configurations */
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8
/* Ports configurations */
#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3
/* Pins configurations */
#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*****************************************************************************************************************************************************
 *
 * 													 				  TYPES DECLARATION
 *
*****************************************************************************************************************************************************/

typedef enum
{
	PIN_INPUT,PIN_OUTPUT	// I/P pin=0 & O/P=1
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF	// I/P port=0 for all the pins & O/P=1 for all the pins
}GPIO_PortDirectionType;

/*****************************************************************************************************************************************************
 *
 * 																	 FUNCTIONS PROTOTYPES
 *
*****************************************************************************************************************************************************/

/*
 * Description: Set the pin as input or output.
 */
void GPIO_setupPinDirection( uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction /* Input or Output*/ );

/*
 * Description: Write a value to a specific pin.
 */
void GPIO_writePin( uint8 port_num, uint8 pin_num, uint8 value );

/*
 * Description: Read a specific pin.
 */
uint8 GPIO_readPin( uint8 port_num, uint8 pin_num );

/*
 * Description: Set the port as input or output.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
 * Description: Write a value to a specific port.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description: Read a specific port.
 */
uint8 GPIO_readPort(uint8 port_num);

/***************************************************************************************************************************************************/
#endif
