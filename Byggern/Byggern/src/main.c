#include <asf.h>

#include "hardware_init.h"

#include "exercises/ex01.h"

int main (void)
{
	hardware_init();
	
	ex01();
		
	return 0;
}
