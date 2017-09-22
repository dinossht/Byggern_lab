/*
 * sram.c
 *
 * Created: 11.09.2017 08:30:18
 *  Author: dinossht
 */ 

#include <stdlib.h>
#include "stdio.h"
#include "uart.h"
#include "sram.h"
#include <asf.h>

#define SRAM_TIMEOUT_COUNTER 10

/* memory_loc is sram memory address index, [0, 2048] == 0x000->0x800, size: 2kB */
void sram_write(uint8_t data, uint16_t memory_index)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM	
	
	uint16_t write_errors = 0;
	
	printf("Starting SRAM writing...\n");
	ext_ram[memory_index] = data;
	uint8_t retrieved_data = ext_ram[memory_index];
	
	while(data != retrieved_data)
	{
		ext_ram[memory_index] = data;
		retrieved_data = ext_ram[memory_index];
		
		printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", memory_index, retrieved_data, data);
		
		write_errors++;
		if(write_errors > SRAM_TIMEOUT_COUNTER)
			printf("Transfer timed out...")
			break;
	}
	printf("Data [%02X] is written", retrieved_data);
}

/* memory_loc is sram memory address index, [0, 2048] == 0x000->0x800 */
uint8_t sram_read(uint16_t memory_index)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	
	printf("Starting SRAM reading...\n");
	
	uint8_t retrieved_data = ext_ram[memory_index];
	printf("Data [%02X] is read", retrieved_data);
	
	return retrieved_data;
}

void sram_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = SRAM_MEM_SIZE;
	
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	
	printf("Starting SRAM test...\n");
	
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	
	uint16_t seed = rand();
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++)
	{
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		
		if (retreived_value != some_value)
		{
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed); // reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++)
	{
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		
		if (retreived_value != some_value)
		{
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

 



