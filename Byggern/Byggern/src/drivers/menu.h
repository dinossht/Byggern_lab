/*
 * menu.h
 *
 * Created: 15.11.2017 20.10.28
 *  Author: Admin
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>


#define MAX_NR_OF_ENTRIES 5

typedef struct menu_t menu_t;

typedef struct  
{
	char* label;
	uint8_t value;
	uint8_t isValueEntry;
}entry_t;

struct menu_t
{
	char* title;
	uint8_t id;
	
	entry_t entries[MAX_NR_OF_ENTRIES];
	uint8_t currentEntryIndex;		
	uint8_t nrOfEntries;
	
	menu_t* previousMenu;
};

typedef enum 
{
	SCROLL_UP,
	SCROLL_DOWN	
}scroll_dir_t;

#define NR_MAIN_ENTRIES 5
entry_t mainEntries[NR_MAIN_ENTRIES];
menu_t mainM;

#define NR_GAME_ENTRIES 3
entry_t gameEntries[NR_GAME_ENTRIES];
menu_t gameM;

#define NR_TUNE_ENTRIES 3
entry_t tuneEntries[NR_TUNE_ENTRIES];
menu_t tunePidM;

#define NR_LOGGING_ENTRIES 2
entry_t loggingEntries[NR_LOGGING_ENTRIES];
menu_t dataLoggingM;

menu_t animationM;

menu_t gameScreenM;

menu_t* currentMenu;

void menu_init(void);

void menu_draw(void);

void menu_navigateToPreviusMenu(void);
void menu_navigateToCurrentEntry(void);

void menu_scrollEntry(scroll_dir_t direction);

#endif /* MENU_H_ */