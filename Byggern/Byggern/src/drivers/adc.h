/*
 * adc.h
 *
 * Created: 11.09.2017 08:30:31
 *  Author: dinossht
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <asf.h>
#include <util/delay.h>

typedef enum {
	CH_1 = 0x04,
	CH_2 = 0x05,
	CH_3 = 0x06,
	CH_4 = 0x07,
	}channel_t;

uint8_t adc_read(channel_t ch);


#endif /* ADC_H_ */