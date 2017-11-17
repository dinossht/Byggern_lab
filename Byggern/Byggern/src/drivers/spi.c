/*
 * spi.c
 *
 * Created: 02.10.2017 11:44:37
 *  Author: hermansu
 */ 


#include "asf.h"
#include "spi.h"

/* NOTE: In PORTB, all the unused pins are set to input during initialization */

// spi port and pin definitions
#define SPI_DD_PORT DDRB 

#define SPI_CLK_PIN DDB7
#define SPI_MOSI_PIN DDB5
#define SPI_MISO_PIN DDB6
 
void spi_init()
{
	/* Set SCK, MOSI and _SS output, all others input */
	SPI_DD_PORT = (1 << SPI_CLK_PIN) | (1 << SPI_MOSI_PIN); 

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) |(1 << SPR0); 
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

