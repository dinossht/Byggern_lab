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


uint8_t eight_kHz_flag;
uint8_t sixteen_kHz_flag;
uint8_t one_kHz_flag;

ISR(TIMER1_COMPA_vect)
{
	eight_kHz_flag = 1;
	TCNT1 = 0;
}

// ISR(TIMER3_COMPA_vect)
// {
// 	sixteen_kHz_flag = 1;
// 	TCNT3 = 0;
// }


void timer_init()
{
	cli();

	
 	OCR1A = 49140; 
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10);
	
	TIMSK |= (1 << OCIE1A);
	TCNT1 = 0;
// 	
// 	TCCR1B = (1 << CS10) |(1 << WGM12); //CTC with prescaler 1
// 	
// 	TIMSK = (1 << OCIE1A); //enable interrupts
/*	
	// should be less than 65536
	// OCR3A = f_clk / N / f_out - 1
	// OCR3A = 4.9MHz / 1 / f_out - 1
	// 4915200
	OCR1A = 614; // 8kHz
	OCR3A = 306; // 16kHz
//	OCRA = 15999; // 1kHz

	TCCR1A |= (1 << WGM12); // CTC mode
	TCCR3A |= (1 << WGM32); // CTC mode
	

	TCCR1B |= (1 << CS10); // No prescaling
	TCCR3B |= (1 << CS30); // No prescaling
	
	TIMSK |= (1 << OCIE1A); // enable timer compare interrupt
	ETIMSK |= (1 << OCIE3A); // enable timer compare interrupt
	
	TCNT1 = 0; // Reset counter
	TCNT3 = 0; // Reset counter
*/
}

void timer_reset(timer_n_t timer)
{
	switch(timer)
	{		
		case EIGHT_KHZ_TIMER:
		eight_kHz_flag = 0;
		break;
		
		case SIXTEEN_KHZ_TIMER:
		sixteen_kHz_flag = 0;
		break;
	}
}

uint8_t timer_isAFlagSet(timer_n_t timer)
{
	switch(timer)
	{		
		case EIGHT_KHZ_TIMER:
		return eight_kHz_flag;
		
		case SIXTEEN_KHZ_TIMER:
		return sixteen_kHz_flag;
	}
	return 0;
}