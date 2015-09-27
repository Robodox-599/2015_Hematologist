#include "WPILib.h"

/*
	Manipulator Joystick
		1. 	intake roller
		2.	close bin hugger
		3.	open bin hugger
		4.	open second tier
		5.	close second tier
		6.	open forklift
		7.	close forklift
		8.	open flaps					(commented out) start sequence
		9.	close flaps
		10.	compressor off
		11.	compressor on
		12.
	Drive Joystick
		1.	confirm
		2.	retract long arm
		3.	extend long arm
		4.	
		5.	
		6.
		7.
		8.
		9.
		10.
		11.
		12.

*/

//Joysticks
#define MANIP_JOYSTICK_PORT							(0)
#define LEFT_DRIVE_JOYSTICK_PORT					(1)
#define RIGHT_DRIVE_JOYSTICK_PORT					(2)

//manip
#define INTAKE_ROLLER_BUTTON						(1)
#define CLOSE_BIN_HUGGER_BUTTON						(2)
#define OPEN_BIN_HUGGER_BUTTON						(3)
#define OPEN_SECOND_TIER_BUTTON						(4)
#define CLOSE_SECOND_TIER_BUTTON					(5)
#define OPEN_FORKLIFT_BUTTON						(6)
#define CLOSE_FORKLIFT_BUTTON						(7)
//#define START_SEQUENCE_BUTTON						(8)
#define TURN_COMPRESSOR_OFF_BUTTON					(10)
#define TURN_COMPRESSOR_ON_BUTTON					(11)
#define OPEN_FLAPS_BUTTON							(8)
#define CLOSE_FLAPS_BUTTON							(9)

//drive
#define CONFIRM_BUTTON								(1)
#define RETRACT_LONG_ARM_BUTTON						(2)
#define EXTEND_LONG_ARM_BUTTON						(3)
#define ENCODER_RESET_BUTTON 						(6)

//Motors
#define FRONT_LEFT_MOTOR_CHANNEL					(0)
#define BACK_LEFT_MOTOR_CHANNEL						(1)
#define BACK_RIGHT_MOTOR_CHANNEL					(2)
#define FRONT_RIGHT_MOTOR_CHANNEL					(3)
#define LEFT_LIFT_MOTOR_CHANNEL						(5)
#define RIGHT_LIFT_MOTOR_CHANNEL					(6)
#define LEFT_ROLLER_MOTOR_CHANNEL					(7)
#define RIGHT_ROLLER_MOTOR_CHANNEL					(8)

//Encoders
#define BACK_RIGHT_ENCODER_CHANNEL_A				(0)
#define BACK_RIGHT_ENCODER_CHANNEL_B				(1)
#define FRONT_RIGHT_ENCODER_CHANNEL_A				(2)
#define FRONT_RIGHT_ENCODER_CHANNEL_B				(3)
#define FRONT_LEFT_ENCODER_CHANNEL_A				(4)
#define FRONT_LEFT_ENCODER_CHANNEL_B				(5)
#define BACK_LEFT_ENCODER_CHANNEL_A					(6)
#define BACK_LEFT_ENCODER_CHANNEL_B					(7)
#define LIFT_ENCODER_CHANNEL_A						(8)				
#define LIFT_ENCODER_CHANNEL_B						(9)

//Pneumatics
#define FORKLIFT_PISTON_CHANNEL_A					(0)				
#define FORKLIFT_PISTON_CHANNEL_B					(1)
#define LONG_ARM_PISTON_CHANNEL_B					(2)
#define LONG_ARM_PISTON_CHANNEL_A					(3)
#define BIN_HUGGER_PISTON_CHANNEL_B					(4)
#define BIN_HUGGER_PISTON_CHANNEL_A					(5)
#define SECOND_TIER_PISTON_CHANNEL_B				(6)
#define SECOND_TIER_PISTON_CHANNEL_A				(7)

#define FLAP_OPEN_RELAY_CHANNEL						(0)
#define FLAP_CLOSE_RELAY_CHANNEL					(1)	

//misc
#define COMPRESSOR_CHANNEL							(0)	
#define TOP_LIMIT_SWITCH_CHANNEL					(0)
#define BOTTOM_LIMIT_SWITCH_CHANNEL					(3)
#define DEADZONE									(.5)
#define LIFT_DEADZONE								(.1)
#define ENCODER_DEADZONE							(20)




