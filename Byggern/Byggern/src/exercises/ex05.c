/*
 * ex05.c
 *
 * Created: 02.10.2017 11:55:04
 *  Author: hermansu
 */ 

#include <asf.h>
#include "ex05.h"
#include "../drivers/spi.h"


void ex05()
{
	spi_masterInit();	
	
	PORTB |= (1 << 4); // set as high !SS, this enables atmega162 to be the master, !SS low leads to it act as a slave
	
	while(1)
	{
		spi_masterTransmit('i');	
		spi_masterTransmit('0');	
		spi_masterTransmit('k');	
		//spi_masterTransmit('s');
		//spi_masterTransmit('s');		
	}
}