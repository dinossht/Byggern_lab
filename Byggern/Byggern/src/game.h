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

typedef enum {
	MULTIBOARD,
	PS3,
} controller_t;

typedef enum {
	PLAYER1 = 1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	PLAYER5,
} user_t;

typedef struct{
	user_t user;
	uint8_t score;
	uint8_t lives;
	uint8_t parameters[3];
	controller_t controller;
} settings_t;


struct multiboard_states_t
{
	int8_t joystickPositionX;
	int8_t joystickPositionY;
	uint8_t joystickPressed;
	
	uint8_t	sliderLeftPosition;
	uint8_t sliderRightPosition;

	uint8_t buttonLeftPressed;
	uint8_t buttonRightPressed;

	joystick_dir_t joystickDirection;
//	uint8_t inUse;
} multiboardInputs;
#warning This should probably be moved


void game_init(void);

void game_setUser(user_t currentUser);
user_t game_getUser(void);

void game_setScore(uint8_t currentScore);
uint8_t game_getScore(void);

void game_setLives(uint8_t currentScore);
uint8_t game_getLives(void);

void game_setParameters(uint8_t* currentParameters);
uint8_t* game_getParameters(void);

void game_setController(controller_t currentController);
controller_t game_getController(void);



uint8_t game_insertHighscore(void);



void game_updateControllerInput(void);

//Transmit
void game_transmitControllerInput(void);

void game_transmitParameters(void);




#endif /* GAME_H_ */