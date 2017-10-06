/*
 * ex05.c
 *
 * Created: 02.10.2017 11:55:04
 *  Author: hermansu
 */ 

#include <asf.h>
#include "../settings.h"
#include <util/delay.h>

#include "ex05.h"
#include "../drivers/mcp2515.h"
#include "../drivers/spi.h"
#include <stdio.h>


#define CAN_PORT PORTB
#define CAN_CS PINB4

void ex05()
{

	
	mcp2515_init();	
	

	while(1)
	{
		CAN_PORT &= ~(1 << CAN_CS); // Select CAN-controller
		_delay_us(500);
		spi_masterTransmit(4);	
		CAN_PORT |= (1 << CAN_CS); // Deselect CAN-controller
 		_delay_us(500);	
	}	
}