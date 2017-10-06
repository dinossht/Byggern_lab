/*
 * mcp2515.c
 *
 * Created: 06.10.2017 13:06:24
 *  Author: dinossht
 */ 


#include "settings.h"
#include "asf.h"
#include <stdio.h>
#include "spi.h"
#include "mcp2515.h"
#include <util/delay.h>

#define CAN_PORT PORTB
#define CAN_CS PINB4


uint8_t mcp2515_init()
{
	uint8_t val;
	
	spi_masterInit(); // Initialize SPI
	
	mcp2515_reset(); // Send reset-command
	
	// Self-test
	val = mcp2515_read(MCP_CANSTAT);
	
	
	if((val & MODE_MASK) != MODE_CONFIG) // 1110 0000 & val ==  1000 0000
	{
		printf("Recieved value: %02X\n", val);
		printf("MCP2515 is NOT in configuration mode after reset!\n");
		return 1;
	}
	// More initialization
	printf("MCP2515 is in configuration mode after reset!\n");
	return 0;	
}

void mcp2515_reset()
{	
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	spi_masterTransmit(MCP_RESET); // Send read command	

	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
	_delay_us(15);
}

uint8_t mcp2515_read(uint8_t address)
{
	uint8_t result;
	
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	spi_masterTransmit(MCP_READ); // Send read command
	spi_masterTransmit(address); // Send address
	result = (uint8_t)spi_slaveReceive(); // Read result
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
	
	return result;
}
