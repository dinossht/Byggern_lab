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
	uint8_t mode = MODE_LOOPBACK;
	mcp2515_init(mode);
	mcp2515_printModeStatus(mcp2515_readStatus());
	
	//TODO
	//Interrupts 
	// CANINTE.RXnIE for interrupt when valid message has been received 
}

void can_message_send(struct can_message* message)
{
	// Send message
	
	uint8_t ID = message->id;
	uint8_t Length = message->length;
	uint8_t *data = &message->data;
	
	// Request - to - send 

	
	// Write ID
	mcp2515_write(0x31, ID);
	//mcp2515_write(0x32, );
	
	// Write message length
	
	mcp2515_write(0x35, Length);
	
	// Write to TX buffer
	
	mcp2515_loadTX(0x36, data, Length);
	
	mcp2515_requestToSend(MCP_RTS_TX0);
	
	// At a minimum: TXBnSIDH, TXBnSIDL and TXBnDLC must be loaded
	// For extended identifiers, TXBnEIDm must be loaded
	// If data bytes are present in message, TXBnDm must be loaded and TXBnSIDL.EXIDE must be set
	// TXBnCTRL.TXREQ must be clear
	// Transmit Priority: TXBnCTRL.TXP <1:0>
	// TXBnCTRL-TXREQ must be set for each buffer to request to transmit
}

struct can_message can_message_recieve()
{
	mcp2515_requestToRead(MCP_READ_RX0);
	struct can_message message;
	message.id =  mcp2515_read(MCP_RXB0SIDH);
	message.length = mcp2515_read(0x65);	
	uint8_t *data = &message.data;
	mcp2515_readRX(0x66, data, message.length);	
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

