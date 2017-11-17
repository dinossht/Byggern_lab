/*
 * joystick.h
 *
 * Created: 22.09.2017 19:10:28
 *  Author: dinossht
 */ 

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdint.h>

typedef enum
{
	JOY_UP,
	JOY_DOWN,
	JOY_LEFT,
	JOY_RIGHT,
	JOY_NEUTRAL
}
joystick_dir_t;

typedef enum
{
	POS_X,
	POS_Y	
}
pos_t;

void joystick_calib(void);	
int16_t joystick_getPos(pos_t pos);
joystick_dir_t joystick_getDir(void);
				
#endif //JOYSTICK_H_								  