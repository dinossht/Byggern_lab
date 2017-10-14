/*
 * CAN.h
 *
 * Created: 02.10.2017 18:12:47
 *  Author: hermansu
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "asf.h"


union Can_data_t
{
	uint64_t	u64;
	int64_t		i64;
	uint32_t	u32[2];
	int32_t		i32[2];
	uint16_t	u16[4];
	int16_t		i16[4];
	uint8_t		u8[8];
	int8_t		i8[8];
};

struct can_message
{
	uint16_t id;
	uint8_t length;
	union Can_data_t data;	
};
	
enum interrupt_flag
{
	RXOIF,//Receive Buffer 0 interrupt flag
	RX1IF,//Receive Buffer 1 interrupt flag
	TX0IF,//Transmit Buffer 0 interrupt flag
	TX1IF,//Transmit Buffer 1 interrupt flag
	TX2IF,//Transmit Buffer 2 interrupt flag
	ERRIF,//Error interrupt Flag
	WAKIF,//Wake-up interrupt Flag
	MERRF,//Message Error Interrupt Flag
}; 
		
void  can_init(void);
void can_message_send(struct can_message* message);
struct can_message can_message_recieve();
uint8_t can_error();
uint8_t can_transmit_complete(void);

#endif /* CAN_H_ */