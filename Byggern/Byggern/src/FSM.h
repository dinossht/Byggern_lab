/*
 * fsm.h
 *
 * Created: 11/17/2017 3:25:06 PM
 *  Author: dinos
 */ 


#ifndef FSM_H_
#define FSM_H_

typedef enum
{
	IDLE,
	GAME_PLAY,
	DATA_LOGGING,
	DATA_PLAYBACK,
	TUNING
}
fsm_state_t;

typedef struct{
	fsm_state_t FSM_current_state;
} FSM_stateMachine_t;

void fsm_init(void);
void fsm_setCurrentState(fsm_state_t state);
fsm_state_t fsm_getCurrentState(void);

void fsm_updateStates(void);


void FSM_setGlobalState(fsm_state_t new_state);

fsm_state_t FSM_getGlobalState(void);





#endif /* FSM_H_ */