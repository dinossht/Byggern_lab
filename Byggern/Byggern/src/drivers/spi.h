/*
 * spi.h
 *
 * Created: 02.10.2017 11:44:50
 *  Author: hermansu
 */ 


#ifndef SPI_H_
#define SPI_H_

void spi_masterInit(void);
void spi_masterTransmit(char cData);

void spi_slaveInit(void);
char spi_slaveReceive(void);

#endif /* SPI_H_ */