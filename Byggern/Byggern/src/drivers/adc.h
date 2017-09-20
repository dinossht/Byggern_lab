/*
 * adc.h
 *
 * Created: 11.09.2017 08:30:31
 *  Author: dinossht
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
uint8_t adc_read(uint16_t memory_index);
void adc_write(uint8_t data, uint16_t memory_index);


#endif /* ADC_H_ */