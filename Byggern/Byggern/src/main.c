#include <asf.h>

#include "hardware_init.h"

#include "exercises/ex02.h"

int main (void)
{
	hardware_init();
	
	ex02();
	
	return 0;
}
