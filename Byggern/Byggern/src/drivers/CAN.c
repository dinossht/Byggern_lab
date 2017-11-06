/*
 * CAN.c
 *
 * Created: 02.10.2017 18:12:35
 *  Author: hermansu
 */ 

#include "CAN.h"
#include "mcp2515.h"
#include "exercises/ex05.h"


void  can_init(void)
{
	//Send config commands to MCP2515
	// Write to MCP_CANCTRL	
	mcp2515_init(MODE_NORMAL);
	
	//TODO
	//Interrupts 
	// CANINTE.RXnIE for interrupt when valid message has been received 

	
}

void can_message_send(struct can_message* message)
{
	// Send message
	while(mcp2515_read(MCP_TXB0CTRL) & 0x03); // wait until buffer is pending transmission
	
	// Setup TX buffer 0


	mcp2515_write(0x31, (message->id >> 3) & 0xFF); // high
	mcp2515_write(0x32, (message->id << 5) & 0xE0); //low
	
	mcp2515_write(0x35, message->length);
	
	mcp2515_loadTX(0x36, &(message->data), message->length);
	
	mcp2515_requestToSend(MCP_RTS_TX0);
	
	//mcp2515_write(MCP_TXB0CTRL, 0x03); // /////////fuck

	
	// At a minimum: TXBnSIDH, TXBnSIDL and TXBnDLC must be loaded
	// For extended identifiers, TXBnEIDm must be loaded
	// If data bytes are present in message, TXBnDm must be loaded and TXBnSIDL.EXIDE must be set
	// TXBnCTRL.TXREQ must be clear
	// Transmit Priority: TXBnCTRL.TXP <1:0>
	// TXBnCTRL-TXREQ must be set for each buffer to request to transmit
}

struct can_message can_message_recieve()
{
	struct can_message message;
	
	uint8_t bufferN;
	mcp2515_readRX(MCP_CANINTF, &bufferN, 1);
	
	if(bufferN & MCP_RX0IF)
	{
		mcp2515_requestToRead(MCP_READ_RX0);
		message.id = mcp2515_read(0x62) >> 5;
		message.id |= ((uint16_t)mcp2515_read(MCP_RXB0SIDH)) << 3;
		message.length = mcp2515_read(0x65);
		uint8_t *data = &(message.data);
		mcp2515_readRX(0x66, data, message.length);	
	}
	
	
	// 	if(bufferN & MCP_RX0IF)
	// 	{
	// 		mcp2515_requestToRead(MCP_READ_RX0);
	// 		message.id = mcp2515_read(0x62) >> 5;
	// 		message.id |= ((uint16_t)mcp2515_read(MCP_RXB0SIDH)) << 3;
	// 		message.length = mcp2515_read(0x65);
	// 		uint8_t *data = &message.data;
	// 		mcp2515_readRX(0x66, data, message.length);
	//
	// 	}
	// 	else if(bufferN & MCP_RX1IF)
	// 	{
	// 		mcp2515_requestToRead(MCP_READ_RX1);
	// 		message.id = mcp2515_read(0x62) >> 5;
	// 		message.id |= ((uint16_t)mcp2515_read(MCP_RXB0SIDH)) << 3;
	// 		message.length = mcp2515_read(0x75);
	// 		uint8_t *data = &message.data;
	// 		mcp2515_readRX(0x76, data, message.length);
	// 	}
	return message;
}

uint8_t can_error()
{

//	uint8_t error_msg = mcp2515_read_status; 
	
	//return error_msg;
	
}

uint8_t can_transmit_complete()
{
// 	Once the transmission has completed successfully, the
// 	TXBnCTRL.TXREQ bit will be cleared, the
// 	CANINTF.TXnIF bit will be set and an interrupt will be
// 	generated if the CANINTE.TXnIE bit is set.




}


void can_data_receive(struct can_message* message)
{
	
	//Need which buffer to read
	// Read CANINTF- bit 0 = buffer 0, bit 1 = buffer 1
	// ID: RXBnSIDH & RXBnSIDL
	// Data length: RXBnDLC
	// Data RXBnDM
	
	//Read ID buffer
	
	//Read Length buffer
	
	// Read Data buffer
	
	
	
	
	

}

// interrupt_flag can_int_vect()
// {
// 	// Called in case of interrupt from MCP2515
// 	// Read CANINTF.RXnIF
// 	//
// 	
// 	uint8_t flag = mcp2515_read(); // Read CANINT
// 	
// 		
// }
// 
// 

