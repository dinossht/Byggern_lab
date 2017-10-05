/*
 * ex04.c
 *
 * Created: 25.09.2017 11:49:09
 *  Author: dinossht
 */ 

#include "settings.h"
#include <util/delay.h>	  
#include <stdio.h>
#include <stdint.h>

#include "../multiboard/joystick.h"
#include "../multiboard/button.h"
#include "../multiboard/slider.h"
#include "../multiboard/oled.h"

#include "ex04.h"


#define MAX_NR_OF_LINES 4



static void joystick_printDir(joystick_dir_t dir, uint8_t lineNr, uint8_t colNr);
void display_total_menu(void);
void display_total_pointer(void);


void ex04(void)
{
	oled_init();
	oled_clear();
	joystick_calib();
	joystick_dir_t current_dir = NEUTRAL;
	uint8_t _current_line = 0;
	uint8_t clicked = 0;

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
		
		// print current joystick direction
		current_dir = joystick_getDir();
		joystick_printDir(current_dir, 5, 0);
		
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

static void joystick_printDir(joystick_dir_t dir, uint8_t lineNr, uint8_t colNr)
{
	oled_print("DIR: ", lineNr, colNr);

	switch(dir)
	{
		case UP:
			oled_print("UP", 5, colNr + 20);
			break;
		case DOWN:
			oled_print("DN", 5, colNr + 20);
			break;
		case LEFT:
			oled_print("LT", 5, colNr + 20);
			break;
		case RIGHT:
			oled_print("RT", 5, colNr + 20);
			break;
		case NEUTRAL:
			oled_print("NL", 5, colNr + 20);
			break;
	}	
}