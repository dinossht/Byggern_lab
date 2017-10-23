#include <asf.h>
#include "settings.h"
#include "hardware_init.h"

#include "exercises/ex01.h"
#include "exercises/ex02.h"
#include "exercises/ex03.h"
#include "exercises/ex04.h"
#include "exercises/ex05.h"
#include "exercises/ex07.h"

int main (void)
{
	hardware_init();
	
	//ex01();
	//ex02();
	//ex03();
	//ex04();
	//ex05();
	ex07();
	
	return 0;
}
