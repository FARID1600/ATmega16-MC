/********************************************************************************************************************
 *	Module: Motor
 *
 *	File name: my_motor.h
 *
 *	Description: source file of the motor
 *
 *	Author: FARID
 *
 *******************************************************************************************************************/
#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"

/*********************************************************************************************************************
 *
 * 														  DEFINISIONS
 *
*********************************************************************************************************************/

/* Motor states definitions for IN1/IN2 (Stop at 0/0, rotate clockwise at 0/1 & rotate anti-clockwise at 1/0) */
typedef enum{
	STOP , CW, ACW
}DcMotor_State;

/*********************************************************************************************************************
 *
 * 														FUNCTIONS PROTOTYPES
 *
*********************************************************************************************************************/

/*
 * Description: Start the motor.
 */
void DcMotor_Init(void);

/*
 * Description: Choose the required speed and direction of rotation.
 */
void DcMotor_Rotate( DcMotor_State state, uint8 speed);

/********************************************************************************************************************/
#endif
