/*****************************************************************************************************************************************************
 *	File name: func_main2.h
 *
 *	Description: MC2 main stuff
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#ifndef FUNC_MAIN1_H_
#define FUNC_MAIN1_H_

#include "std_types.h"


/*****************************************************************************************************************************************************
 *
 * 																		  DEFINISIONS
 *
*****************************************************************************************************************************************************/

#define	MATCH_COMPLETE	1
#define	MISS_MATCH	0

/*****************************************************************************************************************************************************
 *
 * 																 FUNCTIONS PROTOTYPES
 *
*****************************************************************************************************************************************************/

/*
 * Description: Receive pass from MC1 to check or save.
 */
void Receive_PassFromMC1( uint8 *pass );

/*
 * Description: Save pass received from MC1 in the EEPROM.
 */
void Save_PassToMem( uint8 *pass );

/*
 * Description: Read the pass saved in the EEPROM to check whether the user's pass is correct or incorrect.
 */
void Read_PassFromMem ( uint8 *pass );

/*
 * Description: Compare each digit in any 2 passwords, passed as arguments.
 */
uint8 Check_5Digits( uint8 *pass1, uint8 *pass2 );

/*
 * Description: Call back function of any timer.
 */
void Motor_RxCallBack( void );
void Buzzer_RxCallBack( void );

/*
 * Description: Get 2 passwords from the user, then use Check_5Digits function.
 */
void Comp_Passwords( uint8 *pass1, uint8 *pass2 );

/*
 * Description: Get the user's pass and the pass saved in the EEPROM, then use Check_5Digits function.
 */
uint8 Check_Pass( uint8 *pass1, uint8 *pass2 );


/****************************************************************************************************************************************************/
#endif
