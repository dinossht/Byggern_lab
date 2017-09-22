/*
 * address_decoder.h
 *
 * Created: 11.09.2017 14:08:07
 *  Author: dinossht
 */ 


#ifndef ADDRESS_DECODER_H_
#define ADDRESS_DECODER_H_

#include <stdint.h>

typedef enum{
	DEVICE_OLED, 
	DEVICE_ADC, 
	DEVICE_SRAM	
}device_t;

void address_decoder_send(device_t device, uint8_t data, uint16_t memory_index);

#endif /* ADDRESS_DECODER_H_ */