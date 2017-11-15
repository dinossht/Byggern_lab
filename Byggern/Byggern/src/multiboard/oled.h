/*
 * oled.h
 *
 * Created: 25.09.2017 11:53:04
 *  Author: dinossht
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>

typedef enum
{
	OLED_ON,
	OLED_OFF	
}
oled_state_t;

void oled_setOnState(oled_state_t state);
void oled_init(void);

void oled_updateScreen(void);

void oled_clearScreen(void);

void oled_setContrast(uint8_t contrastVal);

void oled_drawPixel(uint8_t x, uint8_t y);

void oled_print(char* string, uint8_t row, uint8_t col);

// should implement graphics functions such as draw line etc.

// scroll menu function can be implemented if needed. Need to check data sheet for the graphic controller

#endif /* OLED_H_ */