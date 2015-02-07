#ifndef HEMATOLOGIST_MACROS_H_
#define HEMATOLOGIST_MACROS_H_
#include "WPILib.h"

//Joystick
#define MANIP_JOYSTICK						(0)		//TODO: FIND CORRECT VALUE
#define BIN_HUGGER_OPEN_BUTTON				(1)		//TODO: FIND CORRECT VALUE
#define BIN_HUGGER_CLOSE_BUTTON				(2)		//TODO: FIND CORRECT VALUE
#define FORKLIFT_UP_BUTTON					(3)		//TODO: FIND CORRECT VALUE
#define FORKLIFT_DOWN_BUTTON				(4)		//TODO: FIND CORRECT VALUE
#define LEFT_DRIVE_JOYSTICK					(1)		//TODO: FIND CORRECT VALUE
#define RIGHT_DRIVE_JOYSTICK				(2)		//TODO: FIND CORRECT VALUE
#define FORKLIFT_OPEN_BUTTON				(3)		//you know hwat
#define SECOND_TIER_OPEN_BUTTON				(0)		//BYE
#define IGNORE_ENCODERS_BUTTON				(1)		//TODO: get #####digits;)
#define GYRO_TOGGLE_BUTTON          		(3)   	//TODO: get correct number
#define SECOND_TIER_CLOSE_BUTTON			(3)		//TODO: get correct number
#define FORKLIFT_CLOSE_BUTTON				(4)		//TODO: get correct number


//Motor Channels
#define FRONT_LEFT_MOTOR_CHANNEL			(2)
#define BACK_LEFT_MOTOR_CHANNEL				(3)
#define FRONT_RIGHT_MOTOR_CHANNEL			(0)
#define BACK_RIGHT_MOTOR_CHANNEL			(1)
#define LEFT_LIFT_MOTOR_CHANNEL				(5)		//TODO: get correct number
#define RIGHT_LIFT_MOTOR_CHANNEL			(6)		//TODO: get correct number
#define LEFT_FORKLIFT_MOTOR_CHANNEL			(7)		//TODO: get correct number
#define RIGHT_FORKLIFT_MOTOR_CHANNEL		(8)		//TODO: get correct number

//Solenoids
#define SECOND_TIER_PISTON_CHANNEL_A		(1)		// /? ? numBer?
#define SECOND_TIER_PISTON_CHANNEL_B 		(2)		//TODO: get correct number
#define BIN_HUGGER_PISTON_CHANNEL_A			(2)		//TODO: get correct number
#define BIN_HUGGER_PISTON_CHANNEL_B			(3)		//TODO: get correct number
#define FORKLIFT_PISTON_CHANNEL_A			(3)		//TODO: get correct number
#define FORKLIFT_PISTON_CHANNEL_B			(4)		//TODO: get correct number

//Encoders
#define LIFT_ENCODER_CHANNEL_A				(0)		//TODO: get correct number
#define LIFT_ENCODER_CHANNEL_B				(1)		//TODO: get correct number

//Misc Constants
#define DEADZONE                   		    (.1)
#define PRE_SET_LOW							(0)		//TODO: get correct number
#define PRE_SET_MID							(30)	//TODO: get correct number
#define PRE_SET_HIGH						(50)	//TODO: get correct number
#define LIFT_DEADZONE						(10.0)	//TODO: get correct number


//Gyro
#define GYRO_KP								(.1)

#endif

