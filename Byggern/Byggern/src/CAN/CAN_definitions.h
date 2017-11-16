/*
 * CAN_header.h
 *
 * Created: 11/15/2017 4:03:50 PM
 *  Author: dinos
 */ 


#ifndef CAN_DEFINITIONS_H_
#define CAN_DEFINITIONS_H_

//ID[10..8]
#define CAN_NODE_1_ID					0x100
#define CAN_NODE_2_ID					0x200
#define CAN_NODE_3_ID					0x300

//ID[7..4]
#define CAN_GRP_MULTIBOARD_ID			0x10
#define CAN_GRP_DATA_ID					0x20
#define CAN_GRP_PS3_ID					0x30

//ID[3..0]
	//Multiboard
#define CAN_MODULE_JOYSTICK_ID			0x1
#define CAN_MODULE_SLIDER_ID			0x2
#define CAN_MODULE_BUTTON_ID			0x3
	//Data
#define CAN_MODULE_STATE_ID				0x1
#define CAN_MODULE_SCORE_ID				0x2
#define CAN_MODULE_ACTUATOR_ID			0x3
#define CAN_MODULE_PARAMETERS_ID		0x4
#define CAN_MODULE_LIVES_ID				0x5
#define CAN_MODULE_CONTROLLER_ID		0x6
	//PS3
#define CAN_MODULE_JOYSTICK_ID			0x1
#define CAN_MODULE_DPAD_ID				0x2
#define CAN_MODULE_SHOULDERBUTTON_ID	0x3
#define CAN_MODULE_FACEBUTTONS_ID		0x4


//ID									(	NODE			|	GROUP					|	MODULE						)
#define CAN_MULTIBOARD_JOYSTICK_ID		(	CAN_NODE_1_ID	|	CAN_GRP_MULTIBOARD_ID	|	CAN_MODULE_JOYSTICK_ID		)
#define CAN_MULTIBOARD_SLIDER_ID		(	CAN_NODE_1_ID	|	CAN_GRP_MULTIBOARD_ID	|	CAN_MODULE_SLIDER_ID		)
#define CAN_MULTIBOARD_BUTTON_ID		(	CAN_NODE_1_ID	|	CAN_GRP_MULTIBOARD_ID	|	CAN_MODULE_BUTTON_ID		)
#define CAN_STATE_FROMNODE1_ID			(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_STATE_ID			)
#define CAN_STATE_FROMNODE2_ID			(	CAN_NODE_2_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_STATE_ID			)
#define CAN_SCORE_FROMNODE1_ID			(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_SCORE_ID			)
#define CAN_SCORE_FROMNODE2_ID			(	CAN_NODE_2_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_SCORE_ID			)
#define CAN_ACTUATOR_FROMNODE1_ID		(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_ACTUATOR_ID		)
#define CAN_ACTUATOR_FROMNODE2_ID		(	CAN_NODE_2_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_ACTUATOR_ID		)
#define CAN_PS3_JOYSTICK_ID				(	CAN_NODE_3_ID	|	CAN_GRP_PS3_ID			|	CAN_MODULE_JOYSTICK_ID		)
#define CAN_PS3_DPAD_ID					(	CAN_NODE_3_ID	|	CAN_GRP_PS3_ID			|	CAN_MODULE_DPAD_ID			)
#define CAN_PS3_SHOULDERBUTTONS_ID		(	CAN_NODE_3_ID	|	CAN_GRP_PS3_ID			|	CAN_MODULE_SHOULDERBUTTON_ID)
#define CAN_PS3_FACEBUTTONS_ID			(	CAN_NODE_3_ID	|	CAN_GRP_PS3_ID			|	CAN_MODULE_FACEBUTTONS_ID	)
#define CAN_PID_TUNING_ID				(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_PARAMETERS_ID	)
#define CAN_SET_LIVES_ID				(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_LIVES_ID			)
#define CAN_REMAINING_LIVES_ID			(	CAN_NODE_2_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_LIVES_ID			)
#define CAN_SET_CONTROLLER_ID			(	CAN_NODE_1_ID	|	CAN_GRP_DATA_ID			|	CAN_MODULE_CONTROLLER_ID	)


#endif /* CAN_DEFINITIONS_H_ */