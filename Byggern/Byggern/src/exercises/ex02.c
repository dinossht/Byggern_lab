/*
 * ex02.c
 *
 * Created: 04.09.2017 14:14:22
 *  Author: Lars
 */ 

#include "ex02.h"

#include "settings.h"
#include "drivers/led.h"
#include "drivers/latch.h"
#include "drivers/sram.h"
#include "drivers/pio.h"
#include "drivers/address_solver.h"

#include <asf.h>
#include <stdio.h>
#include <util/delay.h>


void ex02(void)
{
	// Enable external memory
	MCUCR |= (1 << SRE);
	
	while(1)
	{
		address_solver_test();
		//SRAM_test();	
	}
}

