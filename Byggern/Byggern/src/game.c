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
 
static settings_t game_settings = {
	.lives = 3,
};


void game_setUser(char* currentUser){
	game_settings.user = currentUser;
}
char* game_getUser(void){
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



 void game_transmitControllerInput(){
	//TODO Add timer interrupts
	joystick_message.data.i8[0] = joystick_getPos(POS_X);
	joystick_message.data.i8[1] = joystick_getPos(POS_Y);
	joystick_message.data.u8[2] = button_getStat(BUTTON_JOYSTICK);
	can_message_send(&joystick_message);
	
	_delay_ms(10);
	
	slider_message.data.u8[0] = slider_getPos(SLIDER_LEFT);
	slider_message.data.u8[1] = slider_getPos(SLIDER_RIGHT);
	can_message_send(&slider_message);
	
	_delay_ms(10);
	
	button_message.data.u8[0] = button_getStat(BUTTON_LEFT);
	button_message.data.u8[1] = button_getStat(BUTTON_RIGHT);
	can_message_send(&button_message);
	
	_delay_ms(10);
 }



void game_transmitParameters(){
		
}