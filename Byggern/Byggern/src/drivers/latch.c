/*
 * latch.c
 *
 * Created: 04.09.2017 15:46:16
 *  Author: Lars
 */ 

#include "latch.h"

void latch_enable(void);

void latch_init()
{
	/* Enable output */
	DDRE |= (1 << PINE1);
	DDRA |= 0xFF;
	
	latch_enable();
}

void latch_write(uint16_t val)
{
	PORTA = val;
}

void latch_enable()
{
	PORTE |= (1 << PINE1);
}
