/*
 * game.h
 *
 * Created: 11/15/2017 8:29:27 PM
 *  Author: dinos
 */ 


#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>
#include "multiboard/joystick.h"
#include "multiboard_data.h"

typedef enum 
{
	GAMEIDLE,
	GAMEPLAYING,
	GAMEOVER
} 
game_state_t;

typedef enum 
{
	MULTIBOARD,
	PS3
} 
controller_t;

struct
{
	uint8_t user_id;
	uint8_t lives;
	uint8_t parameters[3];
	controller_t controller;
} 
game_settings;

game_state_t game_state;

void game_play(void);

void game_init(void);

#endif /* GAME_H_ */