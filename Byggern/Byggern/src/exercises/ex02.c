/*
 * ex02.c
 *
 * Created: 04.09.2017 14:14:22
 *  Author: Lars
 */ 

#include "settings.h"
#include <util/delay.h>
#include "drivers/sram.h"
#include "drivers/address_decoder.h"
#include "ex02.h"


static void ex02_addressDecoderTest(void);

void ex02()
{	
	while(1)
	{
		//address_decoder_test();
		sram_test();	
	}
}

static void ex02_addressDecoderTest()
{
	address_decoder_enable(DEVICE_ADC);
	_delay_ms(1000);
	
	address_decoder_enable(DEVICE_SRAM);
	_delay_ms(1000);	
	
	address_decoder_enable(DEVICE_OLED);
	_delay_ms(1000);
}


