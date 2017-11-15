/*
 * menu.c
 *
 * Created: 15.11.2017 20.10.20
 *  Author: Admin
 */ 

#include <asf.h>
#include <stdio.h>
#include "../multiboard/oled.h"
#include "menu.h"


// struct menu_t
// {
// 	char* title;
// 	
// 	entry_t entries[MAX_NR_OF_ENTRIES];
// 	uint8_t currentEntryIndex;		
// 	uint8_t nrOfEntries;
// 	
// 	menu_t* previousMenu;
// 	menu_t* nextMenu;
// };

entry_t mainEntries[NR_MAIN_ENTRIES] =
{
	{.label = "Game", .value = 0, .isValueEntry = 0},
	{.label = "Tune-PID", .value = 0, .isValueEntry = 0},
	{.label = "Data Logger", .value = 0, .isValueEntry = 0},
	{.label = "Animation", .value = 0, .isValueEntry = 0},
	{.label = "High Score", .value = 0, .isValueEntry = 1},
};

menu_t mainM =
{
	.title = "Main",
	.id = 0,
	.nrOfEntries = NR_MAIN_ENTRIES,
	.currentEntryIndex = 0,
	.previousMenu = NULL,
	.entries = mainEntries
};

entry_t gameEntries[NR_GAME_ENTRIES] =
{
	{.label = "User", .value = 0, .isValueEntry = 1},
	{.label = "Input", .value = 0, .isValueEntry = 1},
	{.label = "Start", .value = 0, .isValueEntry = 0}
};

menu_t gameM = 
{
	.title = "Game",
	.id = 1,
	.nrOfEntries = NR_GAME_ENTRIES,
	.currentEntryIndex = 0,
	.previousMenu = &mainM
};

entry_t tuneEntries[NR_TUNE_ENTRIES] =
{
	{.label = "Kp", .value = 0, .isValueEntry = 1},
	{.label = "Ki", .value = 0, .isValueEntry = 1},
	{.label = "Kd",	.value = 0, .isValueEntry = 1}
};

menu_t tunePidM = 
{
	.title = "Tune-PID",
	.id = 2,
	.nrOfEntries = NR_TUNE_ENTRIES, 
	.currentEntryIndex = 0,
	.previousMenu = &mainM
};

entry_t loggingEntries[NR_LOGGING_ENTRIES] =
{
	{.label = "Start Logging", .value = 0},
	{.label = "Start Playback", .value = 0}
};

menu_t dataLoggingM = 
{
	.title = "Data logger",
	.id = 3,
	.nrOfEntries = NR_LOGGING_ENTRIES, 
	.currentEntryIndex = 0,
	.previousMenu = &mainM
};

menu_t animationM = 
{
	.title = "Animation",
	.id = 4,
	.nrOfEntries = 0,
	.currentEntryIndex = 0,
	.previousMenu = &mainM
};

menu_t gameScreenM = 
{
	.title = "GAME SCREEN",
	.id = 5,
	.nrOfEntries = 0,
	.currentEntryIndex = 0,
	.previousMenu = &gameM
};

static void menu_setCurrentMenu(menu_t* menu);
static void menu_initEntries(menu_t* menu, entry_t* entries);

static void main_navigateToCurrentEntry(void);
static void game_navigateToCurrentEntry(void);

void menu_init()
{
	currentMenu = &mainM;
	menu_initEntries(&mainM, mainEntries);
	menu_initEntries(&gameM, gameEntries);
	menu_initEntries(&tunePidM, tuneEntries);
	menu_initEntries(&dataLoggingM, loggingEntries);
	menu_initEntries(&animationM, NULL);
	menu_initEntries(&gameScreenM, NULL);
}

static void menu_initEntries(menu_t* menu, entry_t* entries)
{
	for(uint8_t i = 0; i < menu->nrOfEntries; i++)
	{
		menu->entries[i] = entries[i];
	}
}

void menu_draw()
{
	oled_print(currentMenu->title, 0, 0);
	
	for(uint8_t i = 0; i < currentMenu->nrOfEntries; i++)
	{
		oled_print(currentMenu->entries[i].label, 2 + i, 1);	
		if(i == currentMenu->currentEntryIndex)
			oled_print(">",  2 + i, 0);
		
		if(currentMenu->entries[i].isValueEntry == 1)
		{
			char str[2];
			sprintf(str, "%d", currentMenu->entries[i].value);
			oled_print(str, 2 + i, 14);	
		}
	}
}

static void menu_setCurrentMenu(menu_t* menu)
{
	if(menu != NULL)
		currentMenu = menu;		
}

void menu_navigateToPreviusMenu()
{
	menu_setCurrentMenu(currentMenu->previousMenu);	
}

static void main_navigateToCurrentEntry()
{
	switch(mainM.currentEntryIndex)
	{
		case 0:
			menu_setCurrentMenu(&gameM);
		break;
			
		case 1:
			menu_setCurrentMenu(&tunePidM);
		break;
		
		case 2:
			menu_setCurrentMenu(&dataLoggingM);
		break;
		
		case 3:
			menu_setCurrentMenu(&animationM);
		break;
	}	
		
}

static void game_navigateToCurrentEntry()
{
	switch(gameM.currentEntryIndex)
	{		
		case 2:
			menu_setCurrentMenu(&gameScreenM);
		break;
	}	
}

void menu_navigateToCurrentEntry()
{
	switch(currentMenu->id)
	{
		case 0:
			main_navigateToCurrentEntry();	
		break;
		
		case 1:
			game_navigateToCurrentEntry();	
		break;
	}
			
}

void menu_scrollEntry(scroll_dir_t direction)
{
	if(currentMenu->nrOfEntries > 0)
	{
		switch(direction)
		{
			case SCROLL_DOWN:
				if(currentMenu->currentEntryIndex == currentMenu->nrOfEntries - 1)
				{
					currentMenu->currentEntryIndex = 0;	
				}
				else
				{
					currentMenu->currentEntryIndex++;
				}
			break;
			
			case SCROLL_UP:
				if(currentMenu->currentEntryIndex == 0)
				{
					currentMenu->currentEntryIndex = currentMenu->nrOfEntries - 1;	
				}
				else
				{
					currentMenu->currentEntryIndex--;
				}
				
			break;
		}	
	}	
}