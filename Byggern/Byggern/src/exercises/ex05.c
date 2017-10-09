/*
 * ex05.c
 *
 * Created: 02.10.2017 11:55:04
 *  Author: hermansu
 */ 

#include <stdio.h>
#include "settings.h"
#include <util/delay.h>

#include "../drivers/mcp2515.h"
#include "../drivers/spi.h"
#include "../drivers/CAN.h"
#include "ex05.h"


void printMsg(struct can_message msg)
{
	printf("\n\nID: %2X\n", msg.id);	
	printf("length: %d\n", msg.length);
	printf("DATA: \n");
	
	for(uint8_t i = 0; i < msg.length; i++)
	{
		printf("%d", msg.data.u8[i]);		
	}	
	printf("\n");		
}

void ex05()
{
	struct can_message message = 
	{
		.id = 0x4,
		.length = 0x3,
		.data.u32[0] =  0xABC    // 
	};
	printMsg(message);
	while(1);
	can_init();
	while(1)
	{
		can_message_send(&message);
		_delay_ms(500);	
	//	printf("status: %2X\n", mcp2515_readStatus());
		struct can_message recievedMsg = can_message_recieve();
 		

	}
	
	
}
// ISR()
// {
// 	canreceived = True;
// }

void mcp2515_printModeStatus(uint8_t status)
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

void mcp2515_testReadAndLoadBuffer()
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