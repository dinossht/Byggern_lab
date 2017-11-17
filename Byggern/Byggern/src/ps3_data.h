/*
 * ps3_data.h
 *
 * Created: 11/17/2017 8:34:08 PM
 *  Author: dinos
 */ 


#ifndef PS3_DATA_H_
#define PS3_DATA_H_

#include <stdint.h>


struct ps3_inputs_t
{
	int8_t joystickLeftPositionX;
	int8_t joystickLeftPositionY;
	
	int8_t joystickRightPositionX;
	int8_t joystickRightPositionY;
}
ps3_data;

void ps3_data_init(void);




#endif /* PS3_DATA_H_ */