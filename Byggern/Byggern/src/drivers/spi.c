/*
 * spi.c
 *
 * Created: 02.10.2017 11:44:37
 *  Author: hermansu
 */ 


#include "asf.h"
#include "spi.h"

#define DD_CLK PB7
#define DD_MOSI PB5
#define DD_MISO PB6


void spi_masterInit()
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1 << DD_CLK) | (1 << DD_MOSI);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) |(1 << SPR0);
}

void spi_masterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)))
	;
}

void spi_slaveInit()
{
	/* Set MISO output, all others input */
	DDRB = (1 << DD_MISO);
	/* Enable SPI */
	SPCR = (1 << SPE);
}

char spi_slaveReceive()
{
	/* Wait for reception complete */
	while(!(SPSR & (1 << SPIF)));
	/* Return data register */
	return SPDR;
}

