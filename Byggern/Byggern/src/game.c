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
 #include "multiboard/joystick.h"
 #include "multiboard/slider.h"
 #include "multiboard/button.h"
 
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


void game_init(){
	game_transmitParameters();
	
	game_setLives_message.data.u8[0] = game_settings.lives;
	can_message_send(&game_setLives_message);
	
	game_setController_message.data.u8[0] = game_settings.controller;
	can_message_send(&game_setController_message);
}

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


void game_insertHighscore(){
	uint8_t i;
	for (i = 4; i >= 0; i--){ //compare
		if (game_settings.score > highscorePoints[i]){
			break;
		}
	}
	for (uint8_t j = 3; j >= i; j--){ //make room for score
		highscorePoints[ j + 1 ] = highscorePoints[ j ];
		highscoreNames [ j + 1 ] = highscoreNames [ j ];
	}
	highscorePoints[ i ] = game_settings.score; //insert score
	highscoreNames [ i ] = game_settings.user; //insert name of user
}


 void game_transmitControllerInput(){
	//TODO Add timer interrupts
	multiboard_joystick_message.data.i8[0] = joystick_getPos(POS_X);
	multiboard_joystick_message.data.i8[1] = joystick_getPos(POS_Y);
	multiboard_joystick_message.data.u8[2] = button_getStat(BUTTON_JOYSTICK);
	can_message_send(&multiboard_joystick_message);
	
	_delay_ms(10);
	
	multiboard_slider_message.data.u8[0] = slider_getPos(SLIDER_LEFT);
	multiboard_slider_message.data.u8[1] = slider_getPos(SLIDER_RIGHT);
	can_message_send(&multiboard_slider_message);
	
	_delay_ms(10);
	
	multiboard_button_message.data.u8[0] = button_getStat(BUTTON_LEFT);
	multiboard_button_message.data.u8[1] = button_getStat(BUTTON_RIGHT);
	can_message_send(&multiboard_button_message);
	
	_delay_ms(10);
 }



void game_transmitParameters(){
	return; 
	#warning Not implemented
}