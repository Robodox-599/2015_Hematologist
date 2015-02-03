#include "HematologistDrive.h"

HematologistDrive::HematologistDrive()
{
	frontLeftMotor 	= new Talon(FRONT_LEFT_MOTOR_CHANNEL);
	backLeftMotor 	= new Talon(BACK_LEFT_MOTOR_CHANNEL);
	frontRightMotor	= new Talon(FRONT_RIGHT_MOTOR_CHANNEL);
	backRightMotor	= new Talon(BACK_RIGHT_MOTOR_CHANNEL);

	gyro = new Gyro(1);
	gyro_ref = 0;

	forward = turn = strafe = 0;
}

HematologistDrive::~HematologistDrive()
{
	delete frontLeftMotor;
	delete backRightMotor;
	delete backLeftMotor;
	delete backRightMotor;
	delete gyro;

	frontLeftMotor 	= NULL;
	backRightMotor 	= NULL;
	backLeftMotor 	= NULL;
	frontRightMotor = NULL;
}

float HematologistDrive::setForward(float forward)
{
	this->forward = forward;
	return forward;
}

float HematologistDrive::setTurn(float turn)
{
	this->turn = turn;
	return turn;
}


float HematologistDrive::setStrafe(float strafe)
{
	this->strafe = strafe;
	return strafe;
}

void  HematologistDrive::drive(float forward, float turn, float strafe);