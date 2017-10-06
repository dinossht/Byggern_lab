/*
 * spi.c
 *
 * Created: 02.10.2017 11:44:37
 *  Author: hermansu
 */ 


#include "asf.h"
#include "spi.h"

/* NOTE: In PORTB, all the unused pins are set to input during initialization */

// spi pin definitions
#define DD_CLK DDB7
#define DD_MOSI DDB5
#define DD_MISO DDB6

// SS active low (on atmega162 is pulled up), 
// input on slave and output on master, needs to be user defined before transmission
 
void spi_masterInit()
{
	/* Set SCK, MOSI and _SS output, all others input */
	DDRB = (1 << DD_CLK) | (1 << DD_MOSI) | (1 << PINB4); 

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) |(1 << SPR0);
	
}


void spi_masterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)));
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
	spi_masterTransmit(0xFF);
	/* Wait for reception complete */
	while(!(SPSR & (1 << SPIF)));
	/* Return data register */
	return SPDR;
}

