/*****************************************************************************************************************************************************
 *	Module: ICU
 *
 *	File name: my_icu.h
 *
 *	Description: Header file of the icu
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/*****************************************************************************************************************************************************
 *
 * 																		 TYPES DEFINISIONS
 *
*****************************************************************************************************************************************************/

/* NB: ICU always operates in normal  mode, so we don't have to define modes */

typedef enum
{
	FALLING_EDGE, RISING_EDGE
}ICU_EdgeType;

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}ICU_Clock;

typedef struct
{
	ICU_Clock clock;
	ICU_EdgeType edge;
}ICU_ConfigType;

/*****************************************************************************************************************************************************
 *
 * 																	 FUNCTIONS PROTOTYPES
 *
*****************************************************************************************************************************************************/

/*
 * Description: Function to initialize the ICU driver.
 *
 */
void ICU_init(const ICU_ConfigType * Config_Ptr);

/*
 * Description: Function to update the callback function.
 *
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description: Function to flip the edge detection of the ICU.
 *
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType);

/*
 * Description: Function to copy the timer register, at the interrupt.
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the timer register.
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the ICU.
 */
void ICU_DeInit(void);

/***************************************************************************************************************************************************/
#endif
