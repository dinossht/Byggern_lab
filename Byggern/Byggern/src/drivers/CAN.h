/*
 * CAN.h
 *
 * Created: 02.10.2017 18:12:47
 *  Author: hermansu
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>
#include <stdbool.h>


union can_data_t
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

struct can_message_t
{
	unsigned int id;
	uint8_t length;
	union can_data_t data;
};
	
void can_init(void);
void can_sendMessage(struct can_message_t* message);
bool can_recieveMessage(struct can_message_t* message);

#endif /* CAN_H_ */