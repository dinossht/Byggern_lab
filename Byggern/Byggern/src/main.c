#include <asf.h>
#include "settings.h"
#include "hardware_init.h"

// #include "exercises/ex01.h"
// #include "exercises/ex02.h"
#include "exercises/ex03.h"

int main (void)
{
	hardware_init();
	
	//ex01();
	//ex02();
	ex03();
	
	return 0;
}
