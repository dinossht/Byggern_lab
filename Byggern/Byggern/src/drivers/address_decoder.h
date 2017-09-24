/*
 * address_decoder.h
 *
 * Created: 11.09.2017 14:08:07
 *  Author: dinossht
 */ 


#ifndef ADDRESS_DECODER_H_
#define ADDRESS_DECODER_H_

typedef enum{
	DEVICE_OLED, 
	DEVICE_ADC, 
	DEVICE_SRAM	
}device_t;

void address_decoder_enable(device_t device);

#endif /* ADDRESS_DECODER_H_ */