/*
 * latch.c
 *
 * Created: 04.09.2017 15:46:16
 *  Author: Lars
 */ 

#include "latch.h"

static void latch_enable(void);

void latch_init()
{
	/* Enable output */
	DDRE |= (1 << PINE1);
	DDRA |= 0xFF;
	
	latch_enable();
}

/* Write 8-bit data to the latch */
void latch_write(uint8_t val)
{
	PORTA = val;
}

static void latch_enable()
{
	PORTE |= (1 << PINE1);
}
