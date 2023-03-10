/********************************************************************************************************************
 *	File name: pwm.h
 *
 *	Description: part of the timer driver header file
 *
 *	Author: FARID
 *
 *******************************************************************************************************************/

#ifndef PWM_H_
#define PWM_H_

/*********************************************************************************************************************
 *
 * 														  DEFINISIONS
 *
*********************************************************************************************************************/

/* The value that the timer starts counting from till the duty cycle which is from 0 -> 255 */
#define TIMER_INITIAL_VALUE 0

/*********************************************************************************************************************
 *
 * 														FUNCTIONS PROTOTYPES
 *
*********************************************************************************************************************/

/*
 * Description: Start the PWM to set the duty cycle.
 */
void PWM_Timer0_Start( uint8 duty_cycle );

/********************************************************************************************************************/
#endif
