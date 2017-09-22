/*
 * joystick.h
 *
 * Created: 22.09.2017 19:10:28
 *  Author: dinossht
 */ 

#include <asf.h>

#include "adc.h"

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NEUTRAL,
	}joystick_direction_t;

struct joystick_postion{
	int16_t X;
	int16_t Y;
	} current_joystick_postion;
	

	
	
void joystick_getPosition(void);
void joystick_getDirection(void);
