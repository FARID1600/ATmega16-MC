/*****************************************************************************************************************************************************
 *	Module: Ultra-sonic
 *
 *	File name: my_ultrasonic.h
 *
 *	Description: header file of the ultra-sonic
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*****************************************************************************************************************************************************
 *
 * 																		 DEFINISIONS
 *
*****************************************************************************************************************************************************/

/* Set the trigger pin */
#define TRIGGER_PORT	PORTB_ID
#define TRIGGER_PIN		PIN5_ID

/* Set the echo pin */
#define ECHO_PORT		PORTD_ID
#define ECHO_PIN		PIN6_ID

/*****************************************************************************************************************************************************
 *
 * 																	 FUNCTIONS PROTOTYPES
 *
*****************************************************************************************************************************************************/

/*
 * Description: Initialize the ultra-sonic.
 */
void Ultrasonic_init( void );

/*
 * Description: Trigger the ultra-sonic to generate the 8 pulses and calculate the distance then.
 */
void Ultrasonic_Trigger( void );

/*
 * Description: Used to store the distance in a uint16 variable.
 */
uint16 Ultrasonic_readDistance( void );

/*
 * Description: Call back function to process the time with High, Low states and edges.
 */
void Ultrasonic_edgeProcessing( void );

/****************************************************************************************************************************************************/
#endif
