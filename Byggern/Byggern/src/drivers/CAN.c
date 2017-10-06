/*
 * CAN.c
 *
 * Created: 02.10.2017 18:12:35
 *  Author: hermansu
 */ 

#include "CAN.h"

void  can_init(void)
{
	//Send config commands to MCP2515
	// Write to MCP_CANCTRL	
	
	uint8_t config_msg = 0x00 | (1 << MODE_LOOPBACK) | (1 << CLKOUT_DISABLE) | (1 << CLKOUT_PS1) 
	// write to MCP2515
	
	mcp2515_write(); // Write command
	mcp2515_write(); // Address
	mcp2515_write(); // send config msg
	
	//Interrupts
	// CANINTE.RXnIE for interrupt when valid message has been received 
	
	
	
	
	
	
}

void can_message_send(struct can_message* message)
{
	// Send message
	// At a minimum: TXBnSIDH, TXBnSIDL and TXBnDLC must be loaded
	// For extended identifiers, TXBnEIDm must be loaded
	// If data bytes are present in message, TXBnDm must be loaded and TXBnSIDL.EXIDE must be set
	// TXBnCTRL.TXREQ must be clear
	// Transmit Priority: TXBnCTRL.TXP <1:0>
	// TXBnCTRL-TXREQ must be set for each buffer to request to transmit
	
	
	
	mcp2515_write(MCP_WRITE); 
	mcp2515_write(); // ID buffer IDH
	mcp2515_write(message->id); // High side of ID
	
	mcp2515_write(MCP_WRITE);
	mcp2515_write(); // ID buffer IDL
	mcp2515_write(message->id); // Low side of ID
	
	
	mcp2515_write(message->length);
	
	for (uint8_t i =0; i<message->length; i++)
	{
		mcp2515_write(message->data[i]);
	}
	
	// Use request to send
	
	
}

uint8_t can_error()
{

	uint8_t error_msg = mcp2515_read_status; 
	
	return error_msg;
	
}

uint8_t can_transmit_complete()
{
// 	Once the transmission has completed successfully, the
// 	TXBnCTRL.TXREQ bit will be cleared, the
// 	CANINTF.TXnIF bit will be set and an interrupt will be
// 	generated if the CANINTE.TXnIE bit is set.




}


can_message can_data_receive(can_message* message)
{
	
	//Need which buffer to read
	// Read CANINTF- bit 0 = buffer 0, bit 1 = buffer 1
	// ID: RXBnSIDH & RXBnSIDL
	// Data length: RXBnDLC
	// Data RXBnDM
	
	
	
	
	

}

interrupt_flag can_int_vect()
{
	// Called in case of interrupt from MCP2515
	// Read CANINTF.RXnIF
	//
	
	uint8_t flag = mcp2515_read(); // Read CANINT
	
		
}



S