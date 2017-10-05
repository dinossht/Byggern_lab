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

static void joystick_updateCurrentMenu(joystick_dir_t currentDir, uint8_t* currentLineNr);
static void joystick_printDir(joystick_dir_t dir, uint8_t lineNr, uint8_t colNr);

static void oled_displayMenus(void);
static void oled_displayMenuArrow(uint8_t currentMenuIndex);

static void slider_displaySlidersPos(void);

static void button_printCurrentMenuIndex(uint8_t currentMenuIndex);

void ex04(void)
{
	oled_init();
	oled_clear();
	
	joystick_calib();
	
	joystick_dir_t currentDir = NEUTRAL;
	uint8_t currentMenuIndex = 0;
	uint8_t numberOfMenus = 4;

	while(1)
	{
		currentDir = joystick_getDir();
		joystick_updateCurrentMenu(currentDir, currentMenuIndex);

		joystick_printDir(currentDir, 5, 0);
		
		oled_displayMenus(); // display menus with cursor on current menu

		slider_displaySlidersPos();
	
		_delay_ms(1000);		
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

static void oled_displayMenus()
{
	oled_print("Menu 0", 0, 0);
	oled_print("Menu 1", 1, 0);
	oled_print("Menu 2", 2, 0);
	oled_print("Menu 3", 3, 0);
	
	oled_displayMenuArrow();
}

static void oled_displayMenuArrow(uint8_t currentIndex)
{
	char arrow = '<';
	char blank = ' ';
	for(uint8_t i = 0; i < MAX_NR_OF_LINES; i++)
	{
		char result = currentIndex == i ? arrow : blank;
		oled_putChar(result, i, 120);
	}
}

static void slider_displaySlidersPos()
{
	static char slider_pos[10];
	
	sprintf(slider_pos, "L: %d", slider_getPos(SLIDER_LEFT) % 100);
	oled_print(slider_pos, 7, 0);	
	
	sprintf(slider_pos, "R: %d", slider_getPos(SLIDER_RIGHT) % 100);
	oled_print(slider_pos, 7, 120);
}

static void joystick_updateCurrentMenu(joystick_dir_t current_dir, uint8_t* index)
{
	if(current_dir == UP)
	{
		*index--;
	}
	else if(current_dir == DOWN)
	{
		*index++;
	}
	*index %= MAX_NR_OF_LINES;		
}

static void button_printCurrentMenuIndex(uint8_t currentIndex)
{
	char num[6];
	
	if(
	button_getStat(BUTTON_JOYSTICK) || 
	button_getStat(BUTTON_LEFT) || 
	button_getStat(BUTTON_RIGHT))
	{
		sprintf(num, "Menu: %d", currentIndex);
		oled_print(num, 4, 64);	
	}
	else
	{
		oled_print("      ", 4, 64);	
	}
}