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
	6 -	 	
	7 -	 	
	8 -		
	9 -		
	10 -	
	11 -	

Manip Joystick:
	1 - 
	2 - 
	3 - 
	4 - 	open bin hugger
	5 - 	close bin hugger
	6 -		open forklift
	7 -		close forklift
	8 -		start compressor
	9 -		stop compressor
	10 -	close second tier
	11 -	open second tier
	throttle -  roller speed
*/

//Joystick
#define MANIP_JOYSTICK						(0)		
#define LEFT_DRIVE_JOYSTICK					(1)		
#define RIGHT_DRIVE_JOYSTICK				(2)		
#define BIN_HUGGER_OPEN_BUTTON				(4)
#define BIN_HUGGER_CLOSE_BUTTON				(5)
#define FORKLIFT_OPEN_BUTTON				(6)
#define FORKLIFT_CLOSE_BUTTON				(7)	
#define START_COMPRESSOR_BUTTON				(8)
#define STOP_COMPRESSOR_BUTTON				(9)	
#define SECOND_TIER_OPEN_BUTTON				(11)
#define SECOND_TIER_CLOSE_BUTTON			(10)
#define AUTOMATIC_LIFT_BUTTON				(1)
#define GYRO_TOGGLE_BUTTON					(3)		//TODO: get correct number
#define LONG_ARM_OPEN_ENABLE_BUTTON			(5)		//TODO: get correct number
#define LONG_ARM_CLOSE_ENABLE_BUTTON		(4)		//TODO: get correct number
#define LONG_ARM_TRIGGER_BUTTON				(1)		


//Motor Channels
#define FRONT_LEFT_MOTOR_CHANNEL			(0)
#define BACK_LEFT_MOTOR_CHANNEL				(1)
#define FRONT_RIGHT_MOTOR_CHANNEL			(3)
#define BACK_RIGHT_MOTOR_CHANNEL			(2)
#define LEFT_LIFT_MOTOR_CHANNEL				(5)		
#define RIGHT_LIFT_MOTOR_CHANNEL			(6)		

//Solenoids
#define FORKLIFT_PISTON_CHANNEL_A			(0)		
#define FORKLIFT_PISTON_CHANNEL_B			(1)		
#define LONG_ARM_PISTON_CHANNEL_A			(3)
#define LONG_ARM_PISTON_CHANNEL_B			(2)
#define BIN_HUGGER_PISTON_CHANNEL_A			(5)	
#define BIN_HUGGER_PISTON_CHANNEL_B			(4)	
#define SECOND_TIER_PISTON_CHANNEL_A		(7)
#define SECOND_TIER_PISTON_CHANNEL_B 		(6)

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
#define LIFT_DEADZONE           			(10)
#define PI									(3.141592653589793238462643383279502884197)
#define PRE_SET_LOW							(0)		//TODO: get correct number
#define PRE_SET_MID							(30)	//TODO: get correct number
#define PRE_SET_HIGH						(50)	//TODO: get correct number
#define TOP_LIMIT_SWITCH_CHANNEL			(0)
#define BOTTOM_LIMIT_SWITCH_CHANNEL			(1)

//Gyro
#define GYRO_KP								(.1)

#endif
