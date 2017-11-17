/*
 * timer.h
 *
 * Created: 16.11.2017 14.20.43
 *  Author: Admin
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>


typedef enum
{
	SIXTY_HZ_TIMER,
	SIXTEEN_KHZ_TIMER
}
timer_n_t;

void timer_init(void);
void timer_reset(timer_n_t timer);
uint8_t timer_isAFlagSet(timer_n_t timer);

#endif /* TIMER_H_ */