/*
 * game.c
 *
 * Created: 11/15/2017 8:29:40 PM
 *  Author: dinos
 */ 

 #include "settings.h"
 #include <util/delay.h>
 
 #include "drivers/menu.h"
 
 #include "multiboard_data.h"
 #include "drivers/sram.h"
 #include "game.h"



void game_init()
{
	game_state = GAMEIDLE;
	game_settings.lives = 0;
	game_settings.controller = 0;
	game_settings.parameters[0] = 0;
	game_settings.parameters[1] = 0;
	game_settings.parameters[2] = 0;
	game_settings.user_id = 0;
}

void game_updateData()
{
	game_settings.lives = 0;
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

// void game_saveGameData()
// {
// 	sram_write(game_settings.parameters[0], 128 * 8 + 1);
// 	sram_write(game_settings.parameters[1], 128 * 8 + 2);
// 	sram_write(game_settings.parameters[2], 128 * 8 + 3);
// }

void game_play()
{
	if(game_exit() != 1 && game_state == GAMEIDLE)
	{
		if(game_state != GAMEOVER)
		{
			if(game_settings.lives <= -1)
				game_state = GAMEOVER;	
			
			menu_setCurrentMenu(&gameScreenM);	
			game_updateData();	
			
			//send playing state
			//game_updateLives();
			//send inputs
			
			// 			//multiboard_data_updateInputs();
			// 			//game_transmitControllerInput();
			// 			//menu_draw();
		}	
		else
		{
			//update highscore && print
			game_state = GAMEIDLE;	
			//oled_print("Gameover", )	
		}
	}
	else
	{
		game_state = GAMEIDLE;
		menu_setCurrentMenu(&gameM);	
	}
	
// 	if(game_state != GAMEOVER)
// 	{
// 		//menu_setCurrentMenu(playingscreen)
// 		
// 
// 		if (game_exit() != 1/* && game_settings.lives > 0*/)
// 		{
// 			//multiboard_data_updateInputs();
// 			//game_transmitControllerInput();
// 			//menu_draw();
// 			#warning This must be added if we dont use timer interrupts			
// 		}
// 		game_state = GAMEOVER;
// 	}
// 	//menu_showScoreAndPlace(game_insertHighscore());
// 	game_state = GAMEIDLE;
// 	fsm_setCurrentState(IDLE);
}