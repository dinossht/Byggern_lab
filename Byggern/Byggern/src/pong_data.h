/*
 * pong_data.h
 *
 * Created: 11/17/2017 8:25:41 PM
 *  Author: dinos
 */ 


#ifndef PONG_DATA_H_
#define PONG_DATA_H_

#include <stdint.h>


struct pong_data_t
{
	uint8_t irTriggered;
	int16_t encoderPosition;
}
pong_data;

void pong_data_init(void);


#endif /* PONG_DATA_H_ */