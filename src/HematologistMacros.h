#ifndef HEMATOLOGIST_MACROS_H
#define HEMATOLOGIST_MACROS_H
#include "WPILib.h"

//Joystick
#define MANIP_JOYSTICK						(0)			//TODO: get correct number
#define BIN_HUGGER_OPEN_BUTTON				(1)			//TODO: get correct number
#define BIN_HUGGER_CLOSE_BUTTON				(2)			//TODO: get correct number
#define FORKLIFT_UP_BUTTON					(3)			//TODO: get correct number
#define FORKLIFT_DOWN_BUTTON				(4)			//TODO: get correct number

//Motor Channels
#define FRONT_LEFT_MOTOR_CHANNEL			(2)
#define BACK_LEFT_MOTOR_CHANNEL				(3)
#define FRONT_RIGHT_MOTOR_CHANNEL			(0)
#define BACK_RIGHT_MOTOR_CHANNEL			(1)
#define LEFT_LIFT_MOTOR_CHANNEL				(5)			//TODO: get correct number
#define RIGHT_LIFT_MOTOR_CHANNEL			(6)			//TODO: get correct number
#define LEFT_FORKLIFT_MOTOR_CHANNEL			(7)			//TODO: get correct number
#define RIGHT_FORKLIFT_MOTOR_CHANNEL		(8)			//TODO: get correct number

//Solenoids
#define BIN_HUGGER_SOL_CHANNEL_A			(0)			//TODO: get correct number
#define BIN_HUGGER_SOL_CHANNEL_B			(1)			//TODO: get correct number
#define SECOND_TIER_SOL_CHANNEL_A			(2)			//TODO: get correct number
#define SECOND_TIER_SOL_CHANNEL_B			(3)			//TODO: get correct number

//Encoders
#define LIFT_ENCODER_CHANNEL_A				(0)			//TODO: get correct number
#define LIFT_ENCODER_CHANNEL_B				(1)			//TODO: get correct number
#define FORKLIFT_ENCODER_CHANNEL_A			(2)			//TODO: get correct number
#define FORKLIFT_ENCODER_CHANNEL_B			(3)			//TODO: get correct number

//Misc Constants
#define DEADZONE                   		    (.1)
#define LIFT_DEADZONE           			(10)
#define SLOPE_ADJUSTMENT					(1.1111111111111111111111111111111)
#define PRE_SET_LOW							(0)			//TODO: get correct number
#define PRE_SET_MID							(30)		//TODO: get correct number
#define PRE_SET_HIGH						(50)		//TODO: get correct number

#define PI									(3.1415926535897932384626433832795)

#endif
