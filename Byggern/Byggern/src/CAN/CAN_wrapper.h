/*
 * can_wrapper.h
 *
 * Created: 11/17/2017 6:36:45 PM
 *  Author: dinos
 */ 


#ifndef CAN_WRAPPER_H_
#define CAN_WRAPPER_H_

uint8_t sendLog;
uint8_t sendPlayback;

void can_wrapper_recieveMessages(void);
void can_wrapper_sendMessages(void);

#endif /* CAN_WRAPPER_H_ */