#include "HematologistDrive.h"

HematologistDrive::HematologistDrive()
{
	frontLeftMotor = new Talon(FRONT_LEFT_MOTOR_CHANNEL);
	frontRightMotor = new Talon(FRONT_RIGHT_MOTOR_CHANNEL);
	backLeftMotor = new Talon(BACK_LEFT_MOTOR_CHANNEL);
	backRightMotor = new Talon(BACK_RIGHT_MOTOR_CHANNEL)
}
