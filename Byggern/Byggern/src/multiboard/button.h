/*
 * button.h
 *
 * Created: 25.09.2017 10:26:00
 *  Author: dinossht
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

typedef enum
{
	RELEASED,
	PRESSED,
	UNDEFINED
}
button_stat_t;

typedef enum
{
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_JOYSTICK	
}
button_t;

button_stat_t button_getStat(button_t btn);

#endif /* BUTTON_H_ */