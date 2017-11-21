/*
 * menu.c
 *
 * Created: 15.11.2017 20.10.20
 *  Author: Admin
 */ 

#include <asf.h>
#include <stdio.h>
#include "../multiboard/oled.h"
#include "../multiboard_data.h"
#include "sram.h"
#include "../FSM.h"
#include "../game.h"
#include "sram.h"
#include "menu.h"


entry_t mainEntries[NR_MAIN_ENTRIES] =
{
	{.label = "Game", .value = 0},
	{.label = "Tune-PID", .value = 0},
	{.label = "Data Logger", .value = 0,},
	{.label = "Animation", .value = 0,},
	{.label = "High Score", .value = 0, .maxValue = 100, .isValueEntry = 1},
};

menu_t mainM =
{
	.title = "Main",
	.id = MAIN_ID,
	.nrOfEntries = NR_MAIN_ENTRIES,
	.currentEntryIndex = 0,
	.previousMenu = NULL,
	.entrySelected = 0
};

entry_t gameEntries[NR_GAME_ENTRIES] =
{
	{.label = "User", .value = 0, .maxValue = 5, .isModifiableEntry = 1},
	{.label = "Input", .value = 0, .maxValue = 1, .isModifiableEntry = 1},
	{.label = "Start", .value = 0},
	{.label = "Difficulty", .value = 0, maxValue = 10, .isModifiableEntry = 1}
};

menu_t gameM = 
{
	.title = "Game",
	.id = GAME_ID,
	.nrOfEntries = NR_GAME_ENTRIES,
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

entry_t tuneEntries[NR_TUNE_ENTRIES] =
{
	{.label = "Kp", .value = 0, .maxValue = 255, .isModifiableEntry = 1},
	{.label = "Ki", .value = 0, .maxValue = 255, .isModifiableEntry = 1},
	{.label = "Kd",	.value = 0, .maxValue = 255, .isModifiableEntry = 1}
};

menu_t tunePidM = 
{
	.title = "Tune-PID",
	.id = TUNE_ID,
	.nrOfEntries = NR_TUNE_ENTRIES, 
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

entry_t loggingEntries[NR_LOGGING_ENTRIES] =
{
	{.label = "Log", .value = 0, .maxValue = 1, .isModifiableEntry = 1},
	{.label = "Playback", .value = 0, .maxValue = 1, .isModifiableEntry = 1}
};

menu_t dataLoggingM = 
{
	.title = "Data logger",
	.id = DATALOG_ID,
	.nrOfEntries = NR_LOGGING_ENTRIES, 
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

menu_t animationM = 
{
	.title = "Animation",
	.id = ANIM_ID,
	.nrOfEntries = 0,
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

menu_t gameScreenM = 
{
	.title = "Pong",
	.id = GAME_SCR_ID,
	.nrOfEntries = 0,
	.currentEntryIndex = 0,
	.previousMenu = &gameM,
	.entrySelected = 0
};

entry_t highScoreEntries[NR_HIGHSCORE_ENTRIES] =
{
	{.label = "Player:", .value = 0, .maxValue = 10, .isValueEntry = 1},
	{.label = "High Score:", .value = 0, .maxValue = 100, .isValueEntry = 1}
};

menu_t highScoreM =
{
	.title = "High Score",
	.id = HIGHSCORE_ID,
	.nrOfEntries = 2,
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

uint8_t shoot;

static void menu_initEntries(menu_t* menu, entry_t* entries);

static void main_navigateToCurrentEntry(void);
static void game_navigateToCurrentEntry(void);

static void menu_drawRegularMenu(void);

static void menu_playLoadScreen(void);

static void gameScreen_draw(uint8_t pongPosition, uint8_t gameState, uint8_t lives, uint8_t isBallHit);
static void drawPong(uint8_t pongPosition, uint8_t isBallHit);
static void drawShoot(uint8_t pongPosition);

void menu_init()
{
	menu_initEntries(&mainM, mainEntries);
	menu_initEntries(&gameM, gameEntries);
	menu_initEntries(&tunePidM, tuneEntries);
	menu_initEntries(&dataLoggingM, loggingEntries);
	menu_initEntries(&animationM, NULL);
	menu_initEntries(&gameScreenM, NULL);
	
	menu_setCurrentMenu(&mainM);
}

menu_t menu_returnCurrentMenu()
{
	return *currentMenu;	
}

static void menu_initEntries(menu_t* menu, entry_t* entries)
{
	for(uint8_t i = 0; i < menu->nrOfEntries; i++)
	{
		menu->entries[i] = entries[i];
	}
}

static void menu_drawRegularMenu()
{
	oled_print(currentMenu->title, 0, 0);
			
	for(uint8_t i = 0; i < currentMenu->nrOfEntries; i++)
	{
		oled_print(currentMenu->entries[i].label, 2 + i, 9);
		if(i == currentMenu->currentEntryIndex)
		{
			oled_print(">",  2 + i, 0);
			if(currentMenu->entrySelected == 1)
			{
				oled_print(currentMenu->entries[i].label, 2 + i, 10);
			}
		}
				
		if(currentMenu->entries[i].isModifiableEntry == 1 || currentMenu->entries[i].isValueEntry == 1)
		{
			char numberString[3];
			numberToString(currentMenu->entries[i].value, numberString);
			oled_print(numberString, 2 + i, 104);
		}
	}
}

void numberToString(uint8_t number, char* string)
{
	sprintf(string, "%d", number);
}

#define NR_OF_GIF_FRAMES 9
static void menu_playLoadScreen()
{
	oled_clearScreen();
	for(uint8_t i = 1; i < NR_OF_GIF_FRAMES; i++)
	{
		oled_displayLoading(i, 56, 3);
		oled_updateScreen();	
	}
}

static void drawPongBoard(uint8_t pongPosition)
{
	uint8_t pongSize = 16;
	for(uint8_t i = 0; i < pongSize; i++)
	{
		oled_drawPixel(pongPosition + i, 62);
		oled_drawPixel(pongPosition + i, 63);
	}
}

static void drawShoot(uint8_t pongPosition)
{
	uint8_t pongSize = 16;
	uint8_t shootHeight = 14;
	
	uint8_t x = pongPosition;
	uint8_t y = 54;
	for(uint8_t i = 0; i < shootHeight; i++)
	{
		
		for (uint8_t j = 0; j < pongSize - 2 * i; j++)
		{
			oled_drawPixel(x, y);		
			x++;
		}
		y++;	
		x = pongPosition + i;
	}		
}

static void drawPong(uint8_t pongPosition, uint8_t isBallHit)
{
	drawPongBoard(pongPosition);
	
	if(isBallHit == 1)
	{
		drawShoot(pongPosition);	
	}
}			

static void gameScreen_draw(uint8_t pongPosition, uint8_t gameState, uint8_t lives, uint8_t isBallHit)
{
	oled_print(currentMenu->title, 0, 0);
	switch(gameState)
	{
		case 0: // playing
			oled_print("Lives:", 0, 80);
			
			char numberString[3];
			numberToString(lives, numberString);
			oled_print(numberString, 1, 104);	
			
			drawPong(pongPosition, isBallHit);
		break;
	}	
	oled_print("LB [EX]", 7, 0);			
}

void menu_draw()
{
	switch(currentMenu->id)
	{
		case MAIN_ID:
		case GAME_ID:
		case TUNE_ID:
		case DATALOG_ID:
		case HIGHSCORE_ID:
			menu_drawRegularMenu();
		break;
		
		case ANIM_ID:
			menu_playLoadScreen();
		break;
		
		case GAME_SCR_ID:	
			gameScreen_draw(0, 0, 9, shoot);	
		break;
	}
}

void menu_setCurrentMenu(menu_t* menu)
{
	if(menu != NULL)
		currentMenu = menu;	
}

void menu_navigateToPreviusMenu()
{
	if(currentMenu->entrySelected == 0)
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
	if(currentMenu->entrySelected == 0)
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
}

void menu_scrollEntry(scroll_dir_t direction)
{
	if(currentMenu->nrOfEntries > 0 && currentMenu->entrySelected == 0)
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

void menu_modEntry(uint8_t value)
{
	uint8_t index = currentMenu->currentEntryIndex;
	if(currentMenu->entries[index].isModifiableEntry == 1)
	{
		currentMenu->entries[index].value = value;				
	}
}

void menu_selectCurrentEntry()
{
	uint8_t index = currentMenu->currentEntryIndex;
	if(currentMenu->entries[index].isModifiableEntry == 1)
	{
		currentMenu->entrySelected = currentMenu->entrySelected == 1 ? 0 : 1;
	}	
}

void menu_incrementEntryValue(uint8_t increment)
{
	uint8_t index = currentMenu->currentEntryIndex;
	if(currentMenu->entries[index].isModifiableEntry == 1 && currentMenu->entrySelected == 1)
	{
		if(increment == 0 && currentMenu->entries[index].value > 0)
			currentMenu->entries[index].value--;
		
		if(increment == 1 && currentMenu->entries[index].value < currentMenu->entries[index].maxValue)
			currentMenu->entries[index].value++;	
	
		menu_writeEntryValueToSram();	
	}
}

void menu_loadEntryValueFromSram()
{
	tunePidM.entries[0].value = sram_read(128 * 8 + 1);
	tunePidM.entries[1].value = sram_read(128 * 8 + 2);
	tunePidM.entries[2].value = sram_read(128 * 8 + 3);
	mainM.entries[4].value = 100 - 10 * game_settings.lives;	
}

void menu_writeEntryValueToSram()
{
	sram_write(tunePidM.entries[0].value, 128 * 8 + 1);
	sram_write(tunePidM.entries[1].value, 128 * 8 + 2);
	sram_write(tunePidM.entries[2].value, 128 * 8 + 3);
}



