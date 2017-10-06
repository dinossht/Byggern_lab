/*
 * spi.h
 *
 * Created: 02.10.2017 11:44:50
 *  Author: hermansu
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "asf.h"


void spi_masterInit(void);
void spi_trancieve(uint8_t* tx_buffer, uint8_t* rx_buffer, int length);

#endif /* SPI_H_ */