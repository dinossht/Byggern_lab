/*
 * sram.h
 *
 * Created: 11.09.2017 08:30:31
 *  Author: dinossht
 */ 


#ifndef SRAM_H_
#define SRAM_H_

#include <stdint.h>

void sram_write(uint8_t data, uint16_t memory_index);
uint8_t sram_read(uint16_t memory_index);
void sram_test(void);

#endif /* SRAM_H_ */