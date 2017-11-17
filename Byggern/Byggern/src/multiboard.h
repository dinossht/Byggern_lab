/*
 * multiboard.h
 *
 * Created: 11/17/2017 6:46:16 PM
 *  Author: dinos
 */ 


#ifndef MULTIBOARD_H_
#define MULTIBOARD_H_

#include <stdint.h>
#include "multiboard/joystick.h"


struct multiboard_inputs_t
{
	int8_t joystickPositionX;
	int8_t joystickPositionY;
	uint8_t joystickPressed;
	
	uint8_t	sliderLeftPosition;
	uint8_t sliderRightPosition;

	uint8_t buttonLeftPressed;
	uint8_t buttonRightPressed;

	joystick_dir_t joystickDirection;
} 
multiboardInputs;

void multiboard_init(void);
void multiboard_updateInputs(void);


#endif /* MULTIBOARD_H_ */