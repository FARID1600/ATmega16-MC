/*********************************************************************************************************************
 *	Module: AVR_MACROS
 *
 *	File name: AVR_MACROS.h
 *
 *	Description: Commonly used macros
 *
 *	Author: FARID
 *
 ********************************************************************************************************************/

#ifndef MY_MACROS_H_
#define MY_MACROS_H_

/*********************************************************************************************************************
 *
 * 																		  DEFINISIONS
 *
*********************************************************************************************************************/

#define	SET_BIT( REG, PIN_NUM )	( (REG) |= ( 1 << (PIN_NUM) ) )

#define CLEAR_BIT( REG, PIN_NUM )	( (REG) &= ~( 1 << (PIN_NUM) ) )

#define TOGGLE_BIT( PORT_NUM, PIN_NUM )	( (PORT_NUM) ^= ( 1 << (PIN_NUM) ) )

#define ROR( PORT_NUM, PLACES )	( (PORT_NUM) = ( ( (PORT_NUM) >> (PLACES) ) | ( (PORT_NUM)<<(8-PLACES) ) ) )

#define ROl( PORT_NUM, PLACES )	( (PORT_NUM) = ( ( (PORT_NUM) << (PLACES) ) | ( (PORT_NUM)>>(8-PLACES) ) ) )

#define BIT_IS_SET( PINx, PIN_NUM )	( (PINx) & (1<<PIN_NUM) )

#define BIT_IS_CLEAR( PINx, PIN_NUM )	( !((PINx) & (1<<PIN_NUM)) )

/********************************************************************************************************************/
#endif
