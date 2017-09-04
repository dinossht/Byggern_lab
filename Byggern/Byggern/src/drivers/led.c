/*
 * led.c
 *
 * Created: 04.09.2017 13:49:05
 */ 

#include "led.h"
#include "pio.h"

void led_init(void)
{
	pio_enable(&DDRC, PINC0);
}

void led_toggle()
{
	pio_toggle(&PORTC, PINC0);
}