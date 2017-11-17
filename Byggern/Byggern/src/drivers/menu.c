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
#include "../FSM.h"
#include "../game.h"


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
	{.label = "Game", .value = 0},
	{.label = "Tune-PID", .value = 0},
	{.label = "Data Logger", .value = 0,},
	{.label = "Animation", .value = 0,},
	{.label = "High Score", .value = 0, .maxValue = 100, .isValueEntry = 1},
};

menu_t mainM =
{
	.title = "Main",
	.id = 0,
	.nrOfEntries = NR_MAIN_ENTRIES,
	.currentEntryIndex = 0,
	.previousMenu = NULL,
	.entrySelected = 0
};

entry_t gameEntries[NR_GAME_ENTRIES] =
{
	{.label = "User", .value = 0, .maxValue = 5, .isModifiableEntry = 1},
	{.label = "Input", .value = 0, .maxValue = 1, .isModifiableEntry = 1},
	{.label = "Start", .value = 0}
};

menu_t gameM = 
{
	.title = "Game",
	.id = 1,
	.nrOfEntries = NR_GAME_ENTRIES,
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

entry_t tuneEntries[NR_TUNE_ENTRIES] =
{
	{.label = "Kp", .value = 0, .maxValue = 100, .isModifiableEntry = 1},
	{.label = "Ki", .value = 0, .maxValue = 100, .isModifiableEntry = 1},
	{.label = "Kd",	.value = 0, .maxValue = 100, .isModifiableEntry = 1}
};

menu_t tunePidM = 
{
	.title = "Tune-PID",
	.id = 2,
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
	.id = 3,
	.nrOfEntries = NR_LOGGING_ENTRIES, 
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

menu_t animationM = 
{
	.title = "Animation",
	.id = 4,
	.nrOfEntries = 0,
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

menu_t gameScreenM = 
{
	.title = "Pong",
	.id = 5,
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
	.id = 6,
	.nrOfEntries = 2,
	.currentEntryIndex = 0,
	.previousMenu = &mainM,
	.entrySelected = 0
};

int8_t joyPos;
uint8_t shoot;

static void menu_setCurrentMenu(menu_t* menu);
static void menu_initEntries(menu_t* menu, entry_t* entries);

static void main_navigateToCurrentEntry(void);
static void game_navigateToCurrentEntry(void);

static void menu_drawRegularMenu(void);
static void animation_draw(void);
static void gameScreen_draw(uint8_t pongPosition, uint8_t gameState, uint8_t lives, uint8_t isBallHit);
static void drawPong(uint8_t pongPosition, uint8_t isBallHit);
static void drawShoot(uint8_t pongPosition);

void menu_init()
{
	currentMenu = &mainM;
	menu_initEntries(&mainM, mainEntries);
	menu_initEntries(&gameM, gameEntries);
	menu_initEntries(&tunePidM, tuneEntries);
	menu_initEntries(&dataLoggingM, loggingEntries);
	menu_initEntries(&animationM, NULL);
	menu_initEntries(&gameScreenM, NULL);
	
	oled_clearScreen();
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
			oled_print(numberToString(currentMenu->entries[i].value), 2 + i, 104);
		}
	}
}

char* numberToString(uint8_t number)
{
	char str[3];
	sprintf(str, "%d", number);
	return str;
}

static void animation_draw()
{
	oled_clearScreen();
	for(uint8_t i = 1; i < 9; i++)
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
			oled_print(numberToString(lives), 1, 104);	
			
			drawPong(pongPosition, isBallHit);
		break;
	}				
}

void menu_draw()
{
	switch(currentMenu->id)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 6:
			menu_drawRegularMenu();
		break;
		
		case 4:
			animation_draw();
		break;
		
		case 5:	
			gameScreen_draw(joyPos, 0, 9, shoot);				
		break;
	}
}

static void menu_setCurrentMenu(menu_t* menu)
{
	if(menu != NULL)
		currentMenu = menu;	
}

void menu_navigateToPreviusMenu()
{
	if(currentMenu->entrySelected == 0)
	{
		menu_setCurrentMenu(currentMenu->previousMenu);		
	}
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
			FSM_setGlobalState(GAME_PLAY);
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
		
		if (currentMenu->id == 1)
		{
			if (currentMenu->currentEntryIndex == 0 && currentMenu->entrySelected == 1)
			{
				//Gi muligheten for å bla opp og ned i brukere
				#warning Should be implemented
			}
			else if (currentMenu->currentEntryIndex == 1 && currentMenu->entrySelected == 1)
			{
				//Gi muligheten for å bla opp og ned mellom inputs
				#warning Should be implemented
			}
		}
		else if(currentMenu->id == 2)
		{
			if(currentMenu->entrySelected == 1)
			{
				FSM_setGlobalState(TUNING);
			}
		}
		
		else if(currentMenu->id == 3){
			if(currentMenu->currentEntryIndex == 0 && currentMenu->entrySelected == 1)
			{
				FSM_setGlobalState(DATA_LOGGING);
			}
			else if(currentMenu->currentEntryIndex == 1 && currentMenu->entrySelected == 1)
			{
				//Gi muligheten for å spille av log
				#warning Should be implemented
			}			
		}
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
	}
}