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

	kP = GYRO_KP;
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
	if (forward > DEADZONE || forward < -DEADZONE)
	{
		this->forward = forward;
	}else
	{
		forward = 0;
	}
	return forward;
}

float HematologistDrive::setTurn(float turn)
{
	if (turn > DEADZONE || turn < -DEADZONE)
	{
		this->turn = turn;
		gyro_ref = gyro->GetAngle();
	}else
	{
		turn = kP * (gyro_ref - (gyro->GetAngle()));
	}
	return turn;
}


float HematologistDrive::setStrafe(float strafe)
{
	if (strafe > DEADZONE || strafe < -DEADZONE)
	{
		this->strafe = strafe;
	}else
	{
		strafe = 0;
	}
	return strafe;
}

void  HematologistDrive::drive(float forward, float turn, float strafe)
{

}