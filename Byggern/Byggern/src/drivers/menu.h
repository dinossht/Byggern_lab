/*
 * menu.h
 *
 * Created: 15.11.2017 14.21.25
 *  Author: Admin
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>


void menu_updateScreen(void);
void menu_putPixel(uint8_t x, uint8_t y);
void menu_clearScreen(void);

void menu_placePixel(uint8_t x, uint8_t y);

#endif /* MENU_H_ */