/*
 * mcp2515.c
 *
 * Created: 06.10.2017 13:06:24
 *  Author: dinossht
 */ 

#include <asf.h>
#include <stdbool.h>
#include "settings.h"
#include <util/delay.h>
#include <stdio.h>
#include "spi.h"
#include "mcp2515.h"


#define CAN_PORT PORTB
#define CAN_DD_PORT DDRB
#define CAN_CS PINB7

static void mcp2515_enableCS(bool selectChip);

uint8_t mcp2515_init(uint8_t mode)
{
	/* set CS pin as output */
	CAN_DD_PORT |= (1 << CAN_CS);
	
	spi_init();

	/* Set to configuration mode */
	mcp2515_reset();
	
	/* Enable receive interrupt */
	mcp2515_bitModify(MCP_CANINTE, MCP_RX0IF, 1);
	
	/* Set mode of operations */
	mcp2515_bitModify(MCP_CANCTRL, MODE_MASK, mode);
	
	return 0;
}

void mcp2515_reset()
{
	mcp2515_enableCS(true);
	
	uint8_t buffer[] =
	{
		MCP_RESET
	};
	spi_trancieve(buffer, NULL, 1);
	
	mcp2515_enableCS(false);
	_delay_us(50); // delay time to stabilize the clock
}

void mcp2515_bitModify(uint8_t address, uint8_t bitMask, uint8_t data)
{
	mcp2515_enableCS(true);
	
	uint8_t buffer[] =
	{
		MCP_BITMOD,
		address,
		bitMask,
		data
	};
	spi_trancieve(buffer, buffer, 4);
	
	mcp2515_enableCS(false);
}

void mcp2515_loadTX(uint8_t address, uint8_t* bufferTX, uint8_t length)
{
	mcp2515_enableCS(true);

	uint8_t buffer[] =
	{
		MCP_WRITE,
		address
	};
	
	spi_trancieve(buffer, NULL, 2);
	spi_trancieve(bufferTX, NULL, length);
	
	mcp2515_enableCS(false);
}

void mcp2515_readRX(uint8_t address, uint8_t* bufferRX, uint8_t length)
{
	mcp2515_enableCS(true);
	
	uint8_t buffer[length + 2];
	buffer[0] = MCP_READ;
	buffer[1] = address;

	spi_trancieve(buffer, NULL, 2);
	spi_trancieve(NULL, bufferRX, length);
	
	mcp2515_enableCS(false);
}

// Used to initiate message transmission for one or more of the transmit buffers
void mcp2515_requestToSend(uint8_t bufferNAddress)
{
	mcp2515_enableCS(true);
	
	uint8_t buffer[] =
	{
		bufferNAddress
	};
	spi_trancieve(buffer, NULL, 1);
	
	mcp2515_enableCS(false);
}

void mcp2515_requestToRead(uint8_t bufferNAddress)
{
	mcp2515_enableCS(true);
	
	uint8_t buffer[] =
	{
		bufferNAddress
	};
	spi_trancieve(buffer, NULL, 1);
	
	mcp2515_enableCS(false);
}

static void mcp2515_enableCS(bool selectChip)
{
	// CS is active low
	if(selectChip)
	{
		CAN_PORT &= ~(1 << CAN_CS);
	}
	
	else
	{
		CAN_PORT |= (1 << CAN_CS);
	}
}
