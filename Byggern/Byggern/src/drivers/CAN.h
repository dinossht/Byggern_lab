/*
 * CAN.h
 *
 * Created: 02.10.2017 18:12:47
 *  Author: hermansu
 */ 


#ifndef CAN_H_
#define CAN_H_


struct can_message{
		unsigned int id;
		uint8_t length;
		uint8_t data[8]	
	};
	
enum interrupt_flag{
	RXOIF,//Receive Buffer 0 interrupt flag
	RX1IF,//Receive Buffer 1 interrupt flag
	TX0IF,//Transmit Buffer 0 interrupt flag
	TX1IF,//Transmit Buffer 1 interrupt flag
	TX2IF,//Transmit Buffer 2 interrupt flag
	ERRIF,//Error interrupt Flag
	WAKIF,//Wake-up interrupt Flag
	MERRF,//Message Error Interrupt Flag
	}; 


#endif /* CAN_H_ */