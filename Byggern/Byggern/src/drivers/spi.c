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
 
void spi_init()
{
	/* Set SCK, MOSI and _SS output, all others input */
	DDRB = (1 << DD_CLK) | (1 << DD_MOSI) | (1 << PINB4); 

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) |(1 << SPR0); //  
//	SPCR |= (1 << DORD); // to set LSB transmit first
//	SPCR |= (1 << SPIE); // enable SPI interrupt, 
}

void spi_trancieve(uint8_t* tx_buffer, uint8_t* rx_buffer, int length)
{
	for(int i = 0; i < length; i++) 
	{
		SPDR = tx_buffer[i];
		
		// Wait for word transmission to complete
		while (!(SPSR & (1 << SPIF)));
		
		if (rx_buffer != NULL) {
			rx_buffer[i] = SPDR;
		}
	}
}

