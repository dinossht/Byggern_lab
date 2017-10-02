/*
 * ex04.c
 *
 * Created: 25.09.2017 11:49:09
 *  Author: dinossht
 */ 

#include <util/delay.h>
#include "ex04.h"
#include "../multiboard/joystick.h"
#include "../multiboard/button.h"

#include <stdio.h>

uint8_t current_line = 0;
#define MAX_NR_OF_LINES 4
uint8_t clicked = 0;

void display_total_menu(void);
void display_total_pointer(void);

void ex04(void)
{
	oled_init();
	oled_clear();
	char str[1];
	while(1)
	{
		
		
		
		//oled_print("current line: ", current_line, 0);
		if(clicked){
			oled_print(str, 6, 64);
			clicked = 0;
		}
		if(button_getStat(BUTTON_JOYSTICK))
			clicked = 1;
		
		joystick_dir_t dir = joystick_getDir();
		
		
		_delay_ms(1000);
		
		if(dir == UP)
		{
			current_line--;				
		}
		else if(dir == DOWN)
		{
			current_line++;		
		}
		current_line %= MAX_NR_OF_LINES;
		int someInt = current_line;
		
		sprintf(str, "%d", someInt);
		display_total_menu();
		display_total_pointer();
		
	}

	
}

void display_total_menu(void)
{
	oled_print("Choice 1", 0, 0);
	oled_print("Choice 2", 1, 0);
	oled_print("Choice 3", 2, 0);
	oled_print("Choice 4", 3, 0);
}

void display_total_pointer()
{
	char arrow = '<';
	char blank = ' ';
	for(uint8_t i = 0; i < MAX_NR_OF_LINES; i++)
	{
		char result = current_line == i ? arrow : blank;
		oled_putChar(result, i, 120);	
	}
	
}