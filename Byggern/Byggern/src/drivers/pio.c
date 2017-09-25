/*
 * io.c
 *
 * Created: 04.09.2017 15:12:40
 *  Author: Lars
 */ 

#include "pio.h"

/* DDRX, PINXN */
void pio_enable(volatile uint8_t* dir, uint8_t pin)
{
	*dir |= (1 << pin);
}

/* PORTX, PINXN */
uint8_t pio_read(volatile uint8_t* input_reg, uint8_t pin)
{
	return (*input_reg & (1 << pin)) >> pin;
}

void pio_set(volatile uint8_t* port, uint8_t pin, pin_val_t val)
{
	if (val == PIN_HIGH)
		*port |= (1 << pin);
	else
		*port &= ~(1 << pin);
}

void pio_toggle(volatile uint8_t* port, uint8_t pin)
{
	*port ^= (1 << pin);
}
