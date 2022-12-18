/*****************************************************************************************************************************************************
 *	Module: I2C
 *
 *	File name: my_i2c.h
 *
 *	Description: Header file of the I2C
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/*****************************************************************************************************************************************************
 *
 * 																	 TWSR REGISTER MACROS
 *
 ****************************************************************************************************************************************************/

#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*****************************************************************************************************************************************************
 *
 * 																		 TYPES DEFINISIONS
 *
 ****************************************************************************************************************************************************/

typedef enum
{
	ONE, FOUR, EIGHT, SIXTEEN, SIXTY_FOUR
}TWI_PreScaler;

typedef struct
{
	TWI_PreScaler	twps_prescaler;
	uint8	twbr_prescaler;
	uint8	mc_address;
}TWI_CongigType;

/*****************************************************************************************************************************************************
 *
 * 																	 FUNCTIONS PROTOTYPES
 *
*****************************************************************************************************************************************************/

void TWI_init( const TWI_CongigType *Config_Ptr );

void TWI_start( void );

void TWI_stop( void );

void TWI_writeByte( uint8 data );

uint8 TWI_readByteWithACK( void );

uint8 TWI_readByteWithNACK( void );

uint8 TWI_getStatus( void );

/****************************************************************************************************************************************************/
#endif
