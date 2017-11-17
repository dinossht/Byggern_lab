/*
 * game.c
 *
 * Created: 11/15/2017 8:29:40 PM
 *  Author: dinos
 */ 

 
 #include "settings.h"
 #include <util/delay.h>
 
 #include "drivers/CAN.h"
 
 #include "CAN/CAN_messages.h"
 
 #include "multiboard/oled.h"
 #include "multiboard/slider.h"
 #include "multiboard/button.h"
 #include "multiboard_data.h"
 
 #include "game.h"
 
static settings_t game_settings = { //defaults
	.user = PLAYER1,
	.score = 0,
	.lives = 3,
	.parameters[0] = 1,
	.parameters[1] = 0,
	.parameters[2] = 0,
	.controller = MULTIBOARD,
};

uint8_t highscorePoints[5] = { 0 };
uint8_t highscoreNames[5] = { 0 };



void game_setUser(user_t currentUser){
	game_settings.user = currentUser;
}
user_t game_getUser(void){
	return game_settings.user;
}


void game_setScore(uint8_t currentScore){
	game_settings.score = currentScore;
}
uint8_t game_getScore(void){
	return game_settings.score;
}


void game_setLives(uint8_t currentLives){
	game_settings.lives = currentLives;
}
uint8_t game_getLives(void){
	return game_settings.lives;
}


void game_setParameters(uint8_t* currentParameters){
	for (uint8_t i = 0; i < 3; i++)
	{ 
		game_settings.parameters[i] = currentParameters[i]; 
	}
}
uint8_t* game_getParameters(void){
	return game_settings.parameters;
}

void game_setController(controller_t currentController){
	game_settings.controller = currentController;
}
controller_t game_getController(void){
	return game_settings.controller;
}


uint8_t game_insertHighscore(){ //Returns place of users highscore, returns 0 if not in top 5
	uint8_t i;
	for (i = 4; i >= 0; i--){ //compare
		if (game_settings.score < highscorePoints[i]){
			i++;
			break;
		}
	}
	if (i == 5){
		return 0;
	}
	else{
		for (uint8_t j = 3; j >= i; j--){ //make room for score
			highscorePoints[ j + 1 ] = highscorePoints[ j ];
			highscoreNames [ j + 1 ] = highscoreNames [ j ];
		}
		highscorePoints[ i ] = game_settings.score; //insert score
		highscoreNames [ i ] = game_settings.user; //insert name of user
		return ( i + 1 );
	}
}


void game_updateControllerInput(){
	
	multiboard_data.joystickPositionX = joystick_getPos(POS_X);
	multiboard_data.joystickPositionY = joystick_getPos(POS_Y);
	multiboard_data.joystickPressed = button_getStat(BUTTON_JOYSTICK);
	
	multiboard_data.sliderLeftPosition  = slider_getPos(SLIDER_LEFT);
	multiboard_data.sliderRightPosition = slider_getPos(SLIDER_RIGHT);
	
	multiboard_data.buttonLeftPressed  = button_getStat(BUTTON_LEFT);
	multiboard_data.buttonRightPressed = button_getStat(BUTTON_RIGHT);
	
	multiboard_data.joystickDirection = joystick_getDir();
//	multiboardStates.inUse = !game_settings.controller;
}



 void game_transmitControllerInput(){
	//TODO Add timer interrupts
	joystick_message.data.i8[0] = joystick_getPos(POS_X);
	joystick_message.data.i8[1] = joystick_getPos(POS_Y);
	joystick_message.data.u8[2] = button_getStat(BUTTON_JOYSTICK);
	can_sendMessage(&joystick_message);
	
	_delay_ms(10);
	
	slider_message.data.u8[0] = slider_getPos(SLIDER_LEFT);
	slider_message.data.u8[1] = slider_getPos(SLIDER_RIGHT);
	can_sendMessage(&slider_message);
	
	_delay_ms(10);
	
	button_message.data.u8[0] = button_getStat(BUTTON_LEFT);
	button_message.data.u8[1] = button_getStat(BUTTON_RIGHT);
	can_sendMessage(&button_message);
	
	_delay_ms(10);
 }



void game_transmitParameters(){
	for (uint8_t i = 0; i < 3; i++){
		gamesData_message.data.u8[i] = game_settings.parameters[i];
	}
	can_sendMessage(&gamesData_message);
}




game_state_t game_state = GAMEIDLE;




uint8_t game_exit(){
	return multiboard_data.buttonLeftPressed;
}


static uint8_t menu_entryIsClick();
#warning empty prototypes

void game_play(){
	while(game_state != GAMEOVER)
	{

		//menu_setCurrentMenu(playingscreen)
		game_state = GAMEPLAYING;

		while (game_settings.lives > 0 && game_exit() != 1)
		{
			game_transmitControllerInput();
			//menu_draw();
			#warning This must be added if we dont use timer interrupts			
		}
		game_state = GAMEOVER;
	}
	//menu_showScoreAndPlace(game_insertHighscore());
	game_state = GAMEIDLE;
}