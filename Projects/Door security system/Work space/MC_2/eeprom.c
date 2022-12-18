/*****************************************************************************************************************************************************
 *	Module: EEPROM
 *
 *	File name: my_eeprom.h
 *
 *	Description: Header file of the EEPROM
 *
 *	Author: FARID
 *
 ****************************************************************************************************************************************************/

#include "eeprom.h"
#include "my_i2c.h"

/****************************************************************************************************************************************************
 *
 * 																	 	  FUNCTIONS
 *
****************************************************************************************************************************************************/

uint8 EEPROM_writeByte( uint16 u16addr, uint8 u8data )
{
	/* Send the start bit */
	TWI_start();
	/* Check if the operation is completed successfully */
    if ( TWI_getStatus() != TWI_START )
        return ERROR;
    /* Send the device address */
    TWI_writeByte( (uint8) ( 0xA0 | ( ( u16addr & 0x0700 ) >> 7 ) ) );
    if ( TWI_getStatus() != TWI_MT_SLA_W_ACK )
        return ERROR;
    /* Send the required memory location address */
    TWI_writeByte( ( uint8 ) u16addr );
    if ( TWI_getStatus() != TWI_MT_DATA_ACK )
        return ERROR;
    /* Send the required data */
    TWI_writeByte( u8data );
    if ( TWI_getStatus() != TWI_MT_DATA_ACK )
        return ERROR;
    /* Send the Stop Bit */
    TWI_stop();
	return SUCCESS;
}

uint8 EEPROM_readByte( uint16 u16addr, uint8 *u8data )
{
	/* Send the start bit */
	TWI_start();
    if ( TWI_getStatus() != TWI_START )
        return ERROR;
    /* Send the device address */
    TWI_writeByte( (uint8) ( 0xA0 | ( ( u16addr & 0x0700 ) >> 7 ) ) );
    if ( TWI_getStatus() != TWI_MT_SLA_W_ACK )
        return ERROR;
    /* Send the required memory location address */
    TWI_writeByte( ( uint8 ) u16addr );
    if ( TWI_getStatus() != TWI_MT_DATA_ACK )
        return ERROR;
	/* Send a repeated start bit */
	TWI_start();
    if ( TWI_getStatus() != TWI_REP_START )
        return ERROR;
    /* Send the device address and the read signal */
    TWI_writeByte( (uint8) ( 0xA0 | ( ( u16addr & 0x0700 ) >> 7 )  | READ_SIGNAL ) );
    if ( TWI_getStatus() != TWI_MT_SLA_R_ACK )
        return ERROR;
    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readByteWithNACK();
    if ( TWI_getStatus() != TWI_MR_DATA_NACK )
        return ERROR;
    /* Send the Stop Bit */
    TWI_stop();
	return SUCCESS;
}

/***************************************************************************************************************************************************/
