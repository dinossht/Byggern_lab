/*
 * CAN.c
 *
 * Created: 02.10.2017 18:12:35
 *  Author: hermansu
 */ 

#include "CAN.h"
#include "mcp2515.h"


void  can_init(void)
{
	mcp2515_init(MODE_NORMAL);
}

void can_sendMessage(struct can_message_t* message)
{
	uint8_t txBuffer = 0x00;
	
	/* Wait until buffer is pending transmission */
	while(txBuffer &  MCP_TXREQ)
	{
		mcp2515_readRX(MCP_TXB0CTRL, &(txBuffer), 1);
	}
	
	// Setup TX buffer 0
	uint8_t messageId[] =
	{
		(message->id >> 0x03) & MSG_ID_HIGHER_BITS_MASK,
		(message->id << 0x05) & MSG_ID_LOWER_BITS_MASK
	};
	
	uint8_t dataBuffer[sizeof(union can_data_t)];
	for(uint8_t i = 0; i < message->length; i++)
	{
		dataBuffer[i] = message->data.u8[i];
	}
	
	mcp2515_loadTX(MCP_TXB0SIDH, &(messageId[0]), 1);
	mcp2515_loadTX(MCP_TXB0SIDL, &(messageId[1]), 1);
	
	mcp2515_loadTX(MCP_TXB0DLC, &(message->length), 1);
	
	mcp2515_loadTX(MCP_TXB0DM, dataBuffer, message->length);
	
	mcp2515_requestToSend(MCP_RTS_TX0);
}

bool can_recieveMessage(struct can_message_t* message)
{
	uint8_t recieveBufferN;
	mcp2515_readRX(MCP_CANINTF, &(recieveBufferN), 1);
	
	if(recieveBufferN & MCP_RX0IF)
	{
		mcp2515_requestToRead(MCP_READ_RX0);
		
		uint8_t messageIdHigherNibble;
		uint8_t messageIdLowerNibble;
		uint8_t messageLength;
		uint8_t data[sizeof(union can_data_t)];
		
		mcp2515_readRX(MCP_RXB0SIDL, &(messageIdLowerNibble), 1);
		mcp2515_readRX(MCP_RXB0SIDH, &(messageIdHigherNibble), 1);
		
		mcp2515_readRX(MCP_RXB0DLC, &(messageLength), 1);
		
		mcp2515_readRX(MCP_RXB0DM, data, messageLength);
		
		message->id = (messageIdLowerNibble >> 0x05);
		message->id |= (((uint16_t)messageIdHigherNibble) << 0x03);
		
		message->length = messageLength;
		
		for(uint8_t i = 0; i < message->length; i++)
		{
			message->data.u8[i] = data[i];
		}
		return true;
	}
	return false;
}