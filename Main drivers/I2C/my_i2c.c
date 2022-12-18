/*****************************************************************************************************************************************************
 *	Module: I2C
 *
 *	File name: my_i2c.c
 *
 *	Description: Source file of the I2C
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include "my_i2c.h"
#include "avr/io.h"
#include "my_macros.h"

/*****************************************************************************************************************************************************
 *
 * 																	 	  FUNCTIONS
 *
*****************************************************************************************************************************************************/

void TWI_init( const TWI_CongigType *Config_Ptr )
{
	/* Configure the bit rate -> SCL_freq = ( F_CPU / ( 16 + 2*TWBR*( 4^TWPS ) ) ). */
	TWBR = ( Config_Ptr -> twbr_prescaler );
	TWSR = TWSR | ( Config_Ptr -> twps_prescaler );
	/* Enable the TWI. */
	TWCR = ( 1 << TWEN );
	/* Set the address if the master is gonna act like a slave (receives). */
	TWAR = ( Config_Ptr -> mc_address );
	//TWIE = 1;
}

void TWI_start( void )
{
	/*
	 * (1) Clear the TWINT flag before sending the start bit.
	 * (2) Send the start bit.
	 * (3) Enable the TWI.
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	/* Check for start condition successful. */
	while( BIT_IS_CLEAR( TWCR, TWINT ) );
}

/* NB: TWI_stop can be neglected. */
void TWI_stop( void )
{
	/*
	 * (1) Clear the TWINT flag before sending the stop bit.
	 * (2) Send the stop bit.
	 * (3) Enable the TWI.
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	/* Check for stop condition successful. */
	//while( BIT_IS_CLEAR( TWCR, TWINT ) );
}

void TWI_writeByte( uint8 data )
{
	/* Put the data in TWDR register */
	TWDR = data;
	/*
	 * (1) Clear the TWINT flag before sending the data.
	 * (2) Enable the TWI module.
	 */
	TWCR = (1 << TWINT) | (1 << TWEN); //TWWC??
	/* Check for write condition successful. */
	while( BIT_IS_CLEAR( TWCR, TWINT ) );
}

uint8 TWI_readByteWithACK( void )
{
	/*
	 * (1) Clear the TWINT flag before sending the data.
	 * (2) Enable the TWI module.
	 * (3) Enable the ack bit.
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Check for read condition successful. */
	while( BIT_IS_CLEAR( TWCR, TWINT ) );
	/* Read the data from TWDR register */
	return TWDR;
}

uint8 TWI_readByteWithNACK( void )
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while( BIT_IS_CLEAR( TWCR, TWINT ) );
	return TWDR;
}

uint8 TWI_getStatus( void )
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}

/****************************************************************************************************************************************************/
