/*
 * multiboard_data.c
 *
 * Created: 11/17/2017 8:30:11 PM
 *  Author: dinos
 */ 

#include "multiboard/joystick.h"
#include "multiboard/slider.h"
#include "multiboard/button.h"
#include "multiboard_data.h"

void multiboard_data_init()
{
	joystick_calib();

	multiboard_dataInputs.joystickDirection = JOY_NEUTRAL;
	multiboard_dataInputs.joystickPositionX = 0;
	multiboard_dataInputs.joystickPositionY = 0;
	multiboard_dataInputs.joystickPressed = 0;
	multiboard_dataInputs.sliderLeftPosition = 0;
	multiboard_dataInputs.sliderRightPosition = 0;
	multiboard_dataInputs.buttonLeftPressed = 0;
	multiboard_dataInputs.buttonRightPressed = 0;
}

void multiboard_data_updateInputs()
{
	multiboard_dataInputs.joystickDirection = joystick_getDir();
	multiboard_dataInputs.joystickPositionX = joystick_getPos(POS_X);
	multiboard_dataInputs.joystickPositionY = joystick_getPos(POS_Y);
	multiboard_dataInputs.buttonLeftPressed = button_getStat(BUTTON_LEFT);
	multiboard_dataInputs.buttonRightPressed = button_getStat(BUTTON_RIGHT);
	multiboard_dataInputs.joystickPressed = button_getStat(BUTTON_JOYSTICK);
	multiboard_dataInputs.sliderLeftPosition = slider_getPos(SLIDER_LEFT);
	multiboard_dataInputs.sliderRightPosition = slider_getPos(SLIDER_RIGHT);
}
