/*
 * timer.c
 *
 * Created: 16.11.2017 14.21.06
 *  Author: Admin
 */ 


#include <asf.h>
#include "settings.h"
#include <interrupt.h>
#include "timer.h"


uint8_t one_kHz_flag;
uint8_t sixty_Hz_flag;
uint8_t sixty1_Hz_flag;


ISR(TIMER1_COMPA_vect)
{
	sixty_Hz_flag = 1;
	TCNT1 = 0;
}

ISR(TIMER3_COMPA_vect)
{
	one_kHz_flag = 1;

	TCNT3 = 0;

}

void timer_init()
{
	cli();
	
	TCCR1B = (1 << WGM12); // CTC
	TCCR1B |= (1 << CS11); // prescaler 2	
	
	OCR1A = 40959; // 60 Hz
	TIMSK = (1 << OCIE1A);
	
	TCCR3B = (1 << WGM32); // CTC
	TCCR3B |= (1 << CS30); // prescaler 1
	
	OCR3A = 4914; // 1KHz
 	
// 	TCCR3B |= (1 << CS30 ) | (1 << CS31); // prescaler 64
// 	OCR3A = 38399;
	ETIMSK = (1 << OCIE3A);
	
	sei();
}

void timer_reset(timer_n_t timer)
{
	switch(timer)
	{		
		case ONE_KHZ_TIMER:
			one_kHz_flag = 0;
		break;
		
		case SIXTY_HZ_TIMER:
			sixty_Hz_flag = 0;
		break;
	}
}

uint8_t timer_isAFlagSet(timer_n_t timer)
{
	switch(timer)
	{		
		case ONE_KHZ_TIMER:
			return one_kHz_flag;
		
		case SIXTY_HZ_TIMER:
			return sixty_Hz_flag;
	}
	return 0;
}