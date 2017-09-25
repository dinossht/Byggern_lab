/*
 * slider.h
 *
 * Created: 25.09.2017 10:25:32
 *  Author: dinossht
 */ 

#include <stdint.h>

#ifndef SLIDER_H_
#define SLIDER_H_

typedef enum
{
	SLIDER_LEFT,
	SLIDER_RIGHT	
}
slider_t;

int16_t slider_getPos(slider_t pos);

#endif /* SLIDER_H_ */