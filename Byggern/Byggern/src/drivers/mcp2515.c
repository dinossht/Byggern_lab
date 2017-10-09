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

uint8_t mcp2515_init(uint8_t mode)
{
	uint8_t val;
	
	spi_masterInit(); // Initialize SPI
	
	mcp2515_reset(); // Send reset-command

	// Self-test
	val = mcp2515_read(MCP_CANSTAT);
	
	if((val & MODE_MASK) != MODE_CONFIG)
	{
		printf("MCP2515 is NOT in configuration mode after reset:  value: %02X\n", val);
		return 1;
	}
	// More initialization
	printf("MCP2515 is in configuration mode after reset!\n");
	
		
	// Enable recieve interrupt
	mcp2515_bitModify(MCP_CANINTE, MCP_RX0IF, 1);
	
	// Set mode
	mcp2515_bitModify(MCP_CANCTRL, MODE_MASK, mode);
	// set up filters, masks and transceiver bit timings
	
	return 0;	
}

void mcp2515_reset()
{	
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	uint8_t buffer[] = 
	{
		MCP_RESET	
	};
	spi_trancieve(buffer, NULL, 1);
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
	_delay_us(15); // delay time to stabilize the clock
}

uint8_t mcp2515_read(uint8_t address)
{
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	uint8_t buffer[] = 
	{
		MCP_READ, // command
		address,  // address
		0x00      // dummy data
	};
	spi_trancieve(buffer, buffer, 3);

	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
	
	return buffer[2];
}

void mcp2515_write(uint8_t address, uint8_t data)
{
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	uint8_t buffer[] = 
	{
		MCP_WRITE, 
		address, 
		data
	};
	spi_trancieve(buffer, NULL, 3);
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
}

// used to initiate message transmission for one or more of the transmit buffers 
void mcp2515_requestToSend(uint8_t bufferNAddress)
{
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	uint8_t buffer[] =
	{
		bufferNAddress	
	};
	spi_trancieve(buffer, NULL, 1); 
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
}

void mcp2515_requestToRead(uint8_t bufferNAddress)
{
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	uint8_t buffer[] =
	{
		bufferNAddress
	};
	spi_trancieve(buffer, NULL, 1);
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
}

void mcp2515_bitModify(uint8_t address, uint8_t bitMask, uint8_t data)
{
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	uint8_t buffer[] = 
	{
		MCP_BITMOD, 
		address, 
		bitMask, 
		data
	};
	spi_trancieve(buffer, buffer, 4);
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller	
}

uint8_t mcp2515_readStatus()
{
	uint8_t status;
	mcp2515_readRX(MCP_READ_STATUS, &status, 1);	
	return status;//*/mcp2515_read(MCP_READ_STATUS);	
}

void mcp2515_loadTX(uint8_t address, uint8_t* bufferTX, uint8_t length)
{
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller

	uint8_t buffer[] =
	{
		MCP_WRITE,
		address
	};
	
	spi_trancieve(buffer, NULL, 2);
	spi_trancieve(bufferTX, NULL, length);
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller	
} 

void mcp2515_readRX(uint8_t address, uint8_t* bufferRX, uint8_t length)
{
	CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
	
	uint8_t buffer[length + 2];
	buffer[0] = MCP_READ;
	buffer[1] = address;

	spi_trancieve(buffer, NULL, 2);
	spi_trancieve(NULL, bufferRX, length);
	
	CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
}