#include "HematologistDrive.h"

HematologistDrive::HematologistDrive()
{
	frontLeftMotor = new Talon(FRONT_LEFT_MOTOR_CHANNEL);
	frontRightMotor = new Talon(FRONT_RIGHT_MOTOR_CHANNEL);
	backLeftMotor = new Talon(BACK_LEFT_MOTOR_CHANNEL);
	backRightMotor = new Talon(BACK_RIGHT_MOTOR_CHANNEL);

	frontLeftEncoder = new Encoder(FRONT_LEFT_ENCODER_CHANNEL_A, FRONT_LEFT_ENCODER_CHANNEL_B);
	frontRightEncoder = new Encoder(FRONT_RIGHT_ENCODER_CHANNEL_A, FRONT_RIGHT_ENCODER_CHANNEL_B);
	backLeftEncoder = new Encoder(BACK_LEFT_ENCODER_CHANNEL_A, BACK_LEFT_ENCODER_CHANNEL_B);
	backRightEncoder = new Encoder(BACK_RIGHT_ENCODER_CHANNEL_A, BACK_RIGHT_ENCODER_CHANNEL_B);

	forward = 0;
	turn = 0;
	strafe = 0;
}
