#include <asf.h>

#include "hardware_init.h"

#include "exercises/ex02.h"
#include "exercises/ex03.h"

int main (void)
{
	hardware_init();
	
	ex03();
	
	return 0;
}
