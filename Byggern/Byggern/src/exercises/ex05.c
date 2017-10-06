/*
 * ex05.c
 *
 * Created: 02.10.2017 11:55:04
 *  Author: hermansu
 */ 

#include <stdio.h>

#include "../drivers/mcp2515.h"
#include "../drivers/spi.h"
#include "ex05.h"


static void mcp2515_printModeStatus(uint8_t status);
static void mcp2515_testReadAndLoadBuffer(void);

void ex05()
{
	mcp2515_init();	
	// loop back mode for testing
	mcp2515_printModeStatus(mcp2515_readStatus());
	
	mcp2515_testReadAndLoadBuffer();
}

static void mcp2515_printModeStatus(uint8_t status)
{
	printf("Current mode: ");
	switch(status)
	{
		case MODE_NORMAL:
			printf("MODE NORMAL");
			break;     
			
		case MODE_SLEEP:
			printf("MODE SLEEP");
			break;      
			
		case MODE_LOOPBACK:
			printf("MODE LOOPBACK");
			break;   
			
		case MODE_LISTENONLY:
			printf("MODE LISTENONLY");
			break;
			
		case MODE_CONFIG:
			printf("MODE CONFIG");
			break;     
	}
	printf("\n");
}

static void mcp2515_testReadAndLoadBuffer()
{
	uint8_t bufferTX[] = {0xCA, 0xFF, 0xEE};  // ABCDEF
	uint8_t bufferRX[3];
	
	mcp2515_loadTX(MCP_TXB1CTRL + 2, bufferTX, 3);
	mcp2515_readRX(MCP_TXB1CTRL + 2, bufferRX, 3);
	
	for(uint8_t i = 0; i < 3; i++)
	{
		printf("%2X", bufferRX[i]);
	}
	printf("?\n\n");
}