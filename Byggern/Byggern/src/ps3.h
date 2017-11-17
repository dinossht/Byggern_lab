/*
 * ps3.h
 *
 * Created: 11/17/2017 6:55:28 PM
 *  Author: dinos
 */ 


#ifndef PS3_H_
#define PS3_H_

#include <stdint.h>


struct ps3_inputs_t
{
	int8_t joystickLeftPositionX;
	int8_t joystickLeftPositionY;
	
	int8_t joystickRightPositionX;
	int8_t joystickRightPositionY;
}
ps3Inputs;

void ps3_init(void);

#endif /* PS3_H_ */