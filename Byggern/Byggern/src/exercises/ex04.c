/*
 * ex04.c
 *
 * Created: 25.09.2017 11:49:09
 *  Author: dinossht
 */ 
 
#include <stdio.h>
#include <stdint.h>
#include "settings.h"
#include <util/delay.h>

#include "../multiboard/joystick.h"
#include "../multiboard/button.h"
#include "../multiboard/slider.h"
#include "../multiboard/oled.h"

#include "ex04.h"


#define MAX_NR_OF_MENUS 4

static void ex04_updateCurrentMenu(joystick_dir_t currentDir, uint8_t* currentMenuIndex);
static void ex04_printJoystickDir(joystick_dir_t dir, uint8_t lineNr, uint8_t colNr);
static void ex04_displayMenus(uint8_t currentMenuIndex);
static void ex04_displayCurrentMenuCursor(uint8_t currentMenuIndex);
static void ex04_displaySlidersPos(uint8_t sliderLeftPos,  uint8_t sliderRightPos);
static void ex04_printCurrentMenuIndex(uint8_t currentMenuIndex, uint8_t lineNr, uint8_t colNr);

void ex04(void)
{
	oled_init();
	oled_clear();
	
	joystick_calib();
	joystick_dir_t currentDir = NEUTRAL;
	
	uint8_t sliderLeftPos = 0;
	uint8_t sliderRightPos = 0;
	
	uint8_t currentMenuIndex = 0;

	while(1)
	{
		sliderLeftPos = slider_getPos(SLIDER_LEFT);
		sliderRightPos = slider_getPos(SLIDER_RIGHT);
		ex04_displaySlidersPos(sliderLeftPos, sliderRightPos);
		
		currentDir = joystick_getDir();
		ex04_updateCurrentMenu(currentDir, &currentMenuIndex);

		ex04_printJoystickDir(currentDir, 5, 0);
		
		ex04_displayMenus(currentMenuIndex); // display menus with cursor on current menu

		if(
			button_getStat(BUTTON_JOYSTICK) ||
			button_getStat(BUTTON_LEFT) ||
			button_getStat(BUTTON_RIGHT))
		{
			ex04_printCurrentMenuIndex(currentMenuIndex, 4, 64);	
		}
		else
		{
			oled_print("       ", 4, 64);	
		}

		_delay_ms(200);		
	}
}

static void ex04_printJoystickDir(joystick_dir_t dir, uint8_t lineNr, uint8_t colNr)
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

static void ex04_displayMenus(uint8_t currentMenuIndex)
{
	oled_print("Menu 0", 0, 0);
	oled_print("Menu 1", 1, 0);
	oled_print("Menu 2", 2, 0);
	oled_print("Menu 3", 3, 0);
	
	ex04_displayCurrentMenuCursor(currentMenuIndex);
}

static void ex04_displayCurrentMenuCursor(uint8_t currentIndex)
{
	char arrow = '<';
	char blank = ' ';
	for(uint8_t i = 0; i < MAX_NR_OF_MENUS; i++)
	{
		char result = currentIndex == i ? arrow : blank;
		oled_putChar(result, i, 120);
	}
}

static void ex04_displaySlidersPos(uint8_t sliderLeftPos,  uint8_t sliderRightPos)
{
	static char slider_pos[10];
	
	sprintf(slider_pos, "L: %d", sliderLeftPos % 100);
	oled_print(slider_pos, 7, 0);	
	
	sprintf(slider_pos, "R: %d", sliderRightPos % 100);
	oled_print(slider_pos, 7, 120);
}

static void ex04_updateCurrentMenu(joystick_dir_t currentDir, uint8_t* currentMenuIndex)
{
	if(currentDir == UP)
	{
		*currentMenuIndex--;
	}
	else if(currentDir == DOWN)
	{
		*currentMenuIndex++;
	}
	*currentMenuIndex %= MAX_NR_OF_MENUS;		
}

static void ex04_printCurrentMenuIndex(uint8_t currentMenuIndex, uint8_t lineNr, uint8_t colNr)
{
	char num[8];
	
	sprintf(num, "Menu: %d", currentMenuIndex);
	oled_print(num, lineNr, colNr);
}