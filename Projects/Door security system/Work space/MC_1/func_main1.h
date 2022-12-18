/*****************************************************************************************************************************************************
 *	File name: func_main1.h
 *
 *	Description: MC1 main stuff
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

#define ENTERING	1
#define CHANGING	0


/*****************************************************************************************************************************************************
 *
 * 																 FUNCTIONS PROTOTYPES
 *
*****************************************************************************************************************************************************/

/*
 * Description: Function used to get the password from the user.
 */
void Enter_Pass( uint8 *pass );

/*
 * Description: Function used to create a new password.
 */
void Create_Pass( uint8 *pass, uint8 *Success );

/*
 * Description: Function used to send the password to the second MC, to save or to check.
 */
void Send_PassToMC2( uint8 *pass );

/*
 * Description: Call back function of any timer.
 */
void Display1_TxCallBack( void );
void Display2_TxCallBack( void );

/*
 * Description: Function used to check that the entered password matches the saved one.
 */
uint8 Check_Pass( uint8 *pass, uint8 state );

/****************************************************************************************************************************************************/
#endif
