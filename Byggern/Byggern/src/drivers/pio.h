/*
 * pio.h
 *
 * Created: 04.09.2017 15:12:52
 *  Author: dinossht
 */ 


#ifndef PIO_H_
#define PIO_H_

#include <asf.h>

void pio_enable(volatile uint8_t* dir, uint8_t pin);
uint8_t pio_read(volatile uint8_t* port, uint8_t pin);
void pio_set(volatile uint8_t* port, uint8_t pin, uint8_t val);
void pio_toggle(volatile uint8_t* port, uint8_t pin);


#endif /* IO_H_ */