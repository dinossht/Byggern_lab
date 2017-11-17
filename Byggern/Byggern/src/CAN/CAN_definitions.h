/*
 * can_definitions.h
 *
 * Created: 11/17/2017 6:10:42 PM
 *  Author: dinos
 */ 


#ifndef CAN_DEFINITIONS_H_
#define CAN_DEFINITIONS_H_


//ID[10..8](bits)
#define CAN_NODE_1_ID			0x100
#define CAN_NODE_2_ID			0x200
#define CAN_NODE_3_ID			0x300


//ID[7..4](bits)
#define CAN_GRP_MULTIBOARD_ID	0x10
#define CAN_GRP_DATA_ID			0x20
#define CAN_GRP_PS3_ID			0x30


//ID[3..0](bits)

//Multiboard
#define CAN_JOYSTICK_ID			0x1
#define CAN_SLIDER_ID			0x2
#define CAN_BUTTONS_ID			0x3

//PS3
#define CAN_JOYSTICK_ID			0x1
#define CAN_DPAD_ID				0x2
#define CAN_BUTTONS_ID			0x3

//Data
#define CAN_GAME_DATA_ID		0x1
#define CAN_PID_PARAM_ID		0x2
#define CAN_MOT_CONTROLL_ID		0x3



//ID									(	NODE			|	GROUP					|	MODULE				)
#define CAN1_MULTIBOARD_JOYSTICK_ID		(	CAN_NODE_1_ID	|	CAN_GRP_MULTIBOARD_ID	|	CAN_JOYSTICK_ID		)
#define CAN1_MULTIBOARD_SLIDER_ID		(	CAN_NODE_1_ID	|	CAN_GRP_MULTIBOARD_ID	|	CAN_SLIDER_ID		)
#define CAN1_MULTIBOARD_BUTTON_ID		(	CAN_NODE_1_ID	|	CAN_GRP_MULTIBOARD_ID	|	CAN_BUTTONS_ID		)
#define CAN1_DATA_PID_PARAM_ID			(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_PID_PARAM_ID	)
#define CAN1_DATA_GAME_DATA_ID			(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_GAME_DATA_ID	)

#define CAN2_DATA_ENCODER_ID			(	CAN_NODE_2_ID	|	CAN_GRP_DATA_ID			|	CAN_MOT_CONTROLL_ID	)

#define CAN3_PS3_JOYSTICK_ID			(	CAN_NODE_3_ID	|	CAN_GRP_PS3_ID			|	CAN_JOYSTICK_ID		)
#define CAN3_PS3_BUTTONS_ID				(	CAN_NODE_3_ID	|	CAN_GRP_PS3_ID			|	CAN_BUTTONS_ID		)
#define CAN3_PS3_DPAD_ID				(	CAN_NODE_3_ID	|	CAN_GRP_PS3_ID			|	CAN_DPAD_ID			)

#endif /* CAN_DEFINITIONS_H_ */