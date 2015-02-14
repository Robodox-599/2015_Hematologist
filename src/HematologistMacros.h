#ifndef HEMATOLOGIST_MACROS_H_
#define HEMATOLOGIST_MACROS_H_
#include "WPILib.h"

/*Joystick button mapping (for reference)
Drive Joystick:
	1 -
	2 -
	3 -
	4 -
	5 -
	6 - start compressor
	7 - stop compressor
	8 -
	9 -
	10 -
	11 -

Manip Joystick:
	1 - Forklift toggle
	2 - Lower Lift
	3 - Raise Lift
	4 - Open Second Tier
	5 - Close Second Tier
	6 -
	7 -
	8 -
	9 -
	10 -
	11 -
	throttle -  roller speed
*/

//Joystick
#define MANIP_JOYSTICK						(0)		//TODO: FIND CORRECT VALUE
#define BIN_HUGGER_OPEN_BUTTON				(1)		//TODO: FIND CORRECT VALUE
#define BIN_HUGGER_CLOSE_BUTTON				(2)		//TODO: FIND CORRECT VALUE
#define FORKLIFT_UP_BUTTON					(3)
#define FORKLIFT_DOWN_BUTTON				(2)
#define LEFT_DRIVE_JOYSTICK					(1)		//TODO: FIND CORRECT VALUE
#define RIGHT_DRIVE_JOYSTICK				(2)		//TODO: FIND CORRECT VALUE
#define FORKLIFT_OPEN_BUTTON				(1)
#define FORKLIFT_CLOSE_BUTTON				(4)		//TODO: get correct number
#define FORKLIFT_TOGGLE_BUTTON				(1)
#define SECOND_TIER_OPEN_BUTTON				(4)
#define IGNORE_ENCODERS_BUTTON				(1)		//TODO: get
#define GYRO_TOGGLE_BUTTON          		(3)   	//TODO: get correct number
#define SECOND_TIER_CLOSE_BUTTON			(5)
#define START_COMPRESSOR_BUTTON				(6)
#define STOP_COMPRESSOR_BUTTON				(7)	


//Motor Channels
#define FRONT_LEFT_MOTOR_CHANNEL			(0)
#define BACK_LEFT_MOTOR_CHANNEL				(1)
#define FRONT_RIGHT_MOTOR_CHANNEL			(3)
#define BACK_RIGHT_MOTOR_CHANNEL			(2)
#define LEFT_LIFT_MOTOR_CHANNEL				(5)		
#define RIGHT_LIFT_MOTOR_CHANNEL			(6)		
#define LEFT_FORKLIFT_MOTOR_CHANNEL			(7)		//TODO: get correct number
#define RIGHT_FORKLIFT_MOTOR_CHANNEL		(8)		//TODO: get correct number

//Solenoids
#define SECOND_TIER_PISTON_CHANNEL_A		(1)		//TODO:? ? numBer?
#define SECOND_TIER_PISTON_CHANNEL_B 		(2)		//TODO: get correct number
#define BIN_HUGGER_PISTON_CHANNEL_A			(2)		//TODO: get correct number
#define BIN_HUGGER_PISTON_CHANNEL_B			(3)		//TODO: get correct number
#define FORKLIFT_PISTON_CHANNEL_A			(3)		//TODO: get correct number
#define FORKLIFT_PISTON_CHANNEL_B			(4)		//TODO: get correct number

//Encoders
#define LIFT_ENCODER_CHANNEL_A				(0)		//TODO: get correct number
#define LIFT_ENCODER_CHANNEL_B				(1)		//TODO: get correct number
#define FRONT_RIGHT_ENCODER_CHANNEL_A (0)   //TODO: get correct number  
#define FRONT_RIGHT_ENCODER_CHANNEL_B (1)   //TODO: get correct number 
#define FRONT_LEFT_ENCODER_CHANNEL_A  (2)   //TODO: get correct number 
#define FRONT_LEFT_ENCODER_CHANNEL_B  (3)   //TODO: get correct number 
#define BACK_RIGHT_ENCODER_CHANNEL_A  (4)   //TODO: get correct number 
#define BACK_RIGHT_ENCODER_CHANNEL_B  (5)   //TODO: get correct number 
#define BACK_LEFT_ENCODER_CHANNEL_A   (6)   //TODO: get correct number 
#define BACK_LEFT_ENCODER_CHANNEL_B   (7)   //TODO: get correct number 




//Misc
#define DEADZONE                   		    (.1)
#define LIFT_DEADZONE           			(10)
#define PI									(3.141592653589793238462643383279502884197)
#define SLOPE_ADJUSTMENT					(1.1)   //TODO: get correct number
#define PRE_SET_LOW							(0)		//TODO: get correct number
#define PRE_SET_MID							(30)	//TODO: get correct number
#define PRE_SET_HIGH						(50)	//TODO: get correct number
#define LIFT_DEADZONE						(10.0)	//TODO: get correct number
#define LIMIT_SWITCH_CHANNEL				(1)	

//Gyro
#define GYRO_KP								(.1)

#endif
