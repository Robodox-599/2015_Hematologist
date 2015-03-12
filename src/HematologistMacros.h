#ifndef HEMATOLOGIST_MACROS_H_
#define HEMATOLOGIST_MACROS_H_
#include "WPILib.h"

/*Joystick button mapping (for reference)
Left Drive Joystick:
	1 - activate
	2 -	retract long arm
	3 -	extend long arm
	4 -	retract flaps
	5 -	extend flaps
	6 -
	7 -	 	
	8 -		
	9 -		
	10 -	
	11 -	

Manip Joystick:
	1 -		turn rollers on
	2 - 	bihugger close
	3 - 	binhugger opem
	4 - 	second tier open
	5 - 	second tier close
	6 -		forklift open
	7 -		forklift close
	8 -		start compressor
	9 -		stop compressor
	10 - 	flaps close
	11 -	flaps open
	throttle -  roller speed
*/

//Joystick
#define MANIP_JOYSTICK						(0)		
#define LEFT_DRIVE_JOYSTICK					(1)		
#define RIGHT_DRIVE_JOYSTICK				(2)

//manip
#define TURN_ROLLERS_ON_BUTTON				(1)
#define BIN_HUGGER_CLOSE_BUTTON				(2)
#define BIN_HUGGER_OPEN_BUTTON				(3)
#define SECOND_TIER_OPEN_BUTTON				(4)
#define SECOND_TIER_CLOSE_BUTTON			(5)
#define FORKLIFT_OPEN_BUTTON				(6)
#define FORKLIFT_CLOSE_BUTTON				(7)	
#define START_COMPRESSOR_BUTTON				(8)
#define STOP_COMPRESSOR_BUTTON				(9)

//drive

//left (but in code the right joystick)
#define ACTIVATE_LONG_ARM					(1)
#define LONG_ARM_OPEN_BUTTON				(3)
#define LONG_ARM_CLOSE_BUTTON				(2)
#define FLAPS_CLOSE_BUTTON					(4)
#define FLAPS_OPEN_BUTTON					(5)


//Motor Channels
#define FRONT_LEFT_MOTOR_CHANNEL			(0)
#define BACK_LEFT_MOTOR_CHANNEL				(1)
#define FRONT_RIGHT_MOTOR_CHANNEL			(3)
#define BACK_RIGHT_MOTOR_CHANNEL			(2)
#define LEFT_LIFT_MOTOR_CHANNEL				(5)		
#define RIGHT_LIFT_MOTOR_CHANNEL			(6)		
#define LEFT_ROLLER_MOTOR_CHANNEL           (7)
#define RIGHT_ROLLER_MOTOR_CHANNEL          (8)

//Solenoids
#define FORKLIFT_PISTON_CHANNEL_A			(0)		
#define FORKLIFT_PISTON_CHANNEL_B			(1)		
#define LONG_ARM_PISTON_CHANNEL_A			(3)
#define LONG_ARM_PISTON_CHANNEL_B			(2)
#define BIN_HUGGER_PISTON_CHANNEL_A			(5)	
#define BIN_HUGGER_PISTON_CHANNEL_B			(4)	
#define SECOND_TIER_PISTON_CHANNEL_A		(7)
#define SECOND_TIER_PISTON_CHANNEL_B 		(6)

//Relays
#define LONG_ARM_RELAY_OPEN_CHANNEL			(0)
#define LONG_ARM_RELAY_CLOSE_CHANNEL		(1)

//Encoders
#define BACK_RIGHT_ENCODER_CHANNEL_A  (0)   
#define BACK_RIGHT_ENCODER_CHANNEL_B  (1)   
#define FRONT_RIGHT_ENCODER_CHANNEL_A (2)   
#define FRONT_RIGHT_ENCODER_CHANNEL_B (3)   
#define FRONT_LEFT_ENCODER_CHANNEL_A  (4)   
#define FRONT_LEFT_ENCODER_CHANNEL_B  (5)   
#define BACK_LEFT_ENCODER_CHANNEL_A   (6)   
#define BACK_LEFT_ENCODER_CHANNEL_B   (7)   
#define LIFT_ENCODER_CHANNEL_A        (8)   
#define LIFT_ENCODER_CHANNEL_B        (9)   


//Misc
#define DEADZONE                   		    (.05)
#define LIFT_DEADZONE           			(30)
#define PI									(3.141592653589793238462643383279502884197)
#define PRE_SET_LOW							(0)		//TODO: get correct number
#define PRE_SET_MID							(30)	//TODO: get correct number
#define PRE_SET_HIGH						(50)	//TODO: get correct number
#define TOP_LIMIT_SWITCH_CHANNEL			(0)
#define BOTTOM_LIMIT_SWITCH_CHANNEL			(2)

//Gyro
#define GYRO_CHANNEL						(1)
#define GYRO_KP								(.1)

#endif
