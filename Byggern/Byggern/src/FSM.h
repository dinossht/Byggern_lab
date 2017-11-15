/*
 * game.h
 *
 * Created: 11/15/2017 2:43:27 PM
 *  Author: dinos
 */ 


#ifndef GAME_H_
#define GAME_H_

typedef enum{
	PLAYING,
	GAMEOVER,
	LOGGING,
	TUNING,
}FSM_states;



typedef struct{
	FSM_states FSM_current_state;
} FSM_stateMachine_t;

void FSM_game_setGlobalState(FSM_states new_state);

FSM_states FSM_getGlobalState(void);



// main:
// If CAN_message ID == gameID
// switch
// message == game over: set state(GAMEOVER);
// Switch(inputFromScreen)  
// case playback: set state(PLAYBACK);
// case play game: set state(playing);
// case tuning: set state(tuning); //kanskje flett inn i playback

#endif /* GAME_H_ */