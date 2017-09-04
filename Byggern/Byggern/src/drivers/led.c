/*
 * led.c
 *
 * Created: 04.09.2017 13:49:05
 */ 

#include "led.h"

#include <avr/io.h>

void led_init(void)
{
	DDRC = (1 << PINC0);
}

void led_toggle()
{
	PORTC ^= (1 << PINC0);
}