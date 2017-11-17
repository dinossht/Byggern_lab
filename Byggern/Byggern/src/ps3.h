/*
 * ps3.h
 *
 * Created: 11/17/2017 6:55:28 PM
 *  Author: dinos
 */ 


#ifndef PS3_H_
#define PS3_H_

struct ps3_inputs_t
{
	int8_t joystickLeftPositionX;
	int8_t joystickLeftPositionY;
	
	int8_t joystickRightPositionX;
	int8_t joystickRightPositionY;
}
ps3Inputs;

void ps3_init()
{
	ps3Inputs.joystickLeftPositionX = 0;
	ps3Inputs.joystickLeftPositionY = 0;
	ps3Inputs.joystickRightPositionX = 0;	
	ps3Inputs.joystickRightPositionY = 0;
}

#endif /* PS3_H_ */