/*
 * game.h
 *
 * Created: 11/15/2017 8:29:27 PM
 *  Author: dinos
 */ 


#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>

/*
typedef enum{
	MENU,
	PLAYING,
	GAMEOVER,
	LOGGING,
	TUNING,
}FSM_states;
*/


typedef struct{
	//uint8_t gameState;
	char* user;
	uint8_t score;
	uint8_t parameters[2];
} settings_t;


void game_setUser(char* currentUser);
char* game_getUser(void);

void game_setScore(uint8_t currentScore);
uint8_t game_getScore(void);

void game_setParameters(uint8_t* currentParameters);
uint8_t* game_getParameters(void);

void game_transmitControllerInput(void);



#endif /* GAME_H_ */