/*
 * game.c
 *
 * Created: 11/15/2017 8:29:40 PM
 *  Author: dinos
 */ 

 #include "settings.h"
 #include <util/delay.h>
 
 #include "drivers/menu.h"
 
 #include "pong_data.h"
 #include "multiboard_data.h"
 #include "drivers/sram.h"

 #include "game.h"
 

static void game_updateData(void);

static uint8_t game_exit(void);


void game_init()
{
	game_state = GAMEIDLE;
	game_settings.lives = 3;
	game_settings.controller = 0;
	game_settings.parameters[0] = 0;
	game_settings.parameters[1] = 0;
	game_settings.parameters[2] = 0;
	game_settings.user_id = 0;
	
}


void game_play()
{
	if (game_state == GAMEIDLE){
		game_settings.lives = gameM.entries[2].value;
		game_state = GAMEPLAYING;
	}
	if(game_exit() != 1 && game_state != GAMEOVER)
	{
		if(game_settings.lives <= 0 )
		{
			game_state = GAMEOVER;
			return;	
		}
		
		menu_setCurrentMenu(&gameScreenM);	
		game_updateData();	
	}
	else
	{
		game_state = GAMEIDLE;
		menu_setCurrentMenu(&gameM);

	}
}


static void game_updateData()
{
	if(pong_data.irTriggered == 1)
	{
		gameM.entries[2].value--;
		game_settings.lives = gameM.entries[2].value;
		pong_data.irTriggered = 0;
	}
	
	game_settings.controller = gameM.entries[1].value; // Input
	game_settings.parameters[0] = tunePidM.entries[0].value;
	game_settings.parameters[1] = tunePidM.entries[1].value;
	game_settings.parameters[2] = tunePidM.entries[2].value;
	game_settings.user_id = gameM.entries[0].value; // Input

}


static uint8_t game_exit()
{
	return multiboard_data.buttonLeftPressed == 1;
}