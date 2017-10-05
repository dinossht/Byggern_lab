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
#include "../multiboard/slider.h"
#include "../multiboard/oled.h"

#include <stdio.h>

uint8_t current_line = 0;
#define MAX_NR_OF_LINES 4
uint8_t clicked = 0;

void display_total_menu(void);
void display_total_pointer(void);
void printDir(uint8_t dir);

void ex04(void)
{
	joystick_calib();
	oled_init();
	oled_clear();
	char str[6];
	char slider[10];
	while(1)
	{
	
		if(clicked){
			oled_print(str, 4, 64);
			clicked = 0;
		}
		
		if(button_getStat(BUTTON_JOYSTICK) || button_getStat(BUTTON_LEFT) || button_getStat(BUTTON_RIGHT))
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
		
		
		
		
		// Test slider////////////////////////////////////////
		sprintf(slider, "L: %d", slider_getPos(SLIDER_LEFT) % 100);
		oled_print(slider, 7, 0);
		
		sprintf(slider, "R: %d", slider_getPos(SLIDER_RIGHT) % 100);
		oled_print(slider, 7, 120);
		///////////////////////////////////////////////////////////////
		
		printDir(joystick_getDir());
		int someInt = current_line;
		sprintf(str, "Menu: %d", someInt);
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

void printDir(uint8_t dir)
{
	oled_print("DIR: ", 5, 0);
	switch(dir)
	{
		case UP:
			oled_print("UP", 5, 20);
			break;
		case DOWN:
			oled_print("DN", 5, 20);
			break;
		case LEFT:
			oled_print("LT", 5, 20);
			break;
		case RIGHT:
			oled_print("RT", 5, 20);
			break;
		case NEUTRAL:
			oled_print("NL", 5, 20);
			break;
	}	
}