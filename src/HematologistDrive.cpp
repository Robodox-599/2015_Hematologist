#include "HematologistDrive.h"

HematologistDrive::HematologistDrive(HematologistOperatorInterface* oi)
{
	frontLeftMotor 	= new Talon(FRONT_LEFT_MOTOR_CHANNEL);
	backLeftMotor 	= new Talon(BACK_LEFT_MOTOR_CHANNEL);
	frontRightMotor	= new Talon(FRONT_RIGHT_MOTOR_CHANNEL);
	backRightMotor	= new Talon(BACK_RIGHT_MOTOR_CHANNEL);

	gyro = new Gyro(1);
	gyro_ref = 0;
	gyroButton = true;

	forward = turn = strafe = 0;

	this->oi = oi;

	kP = GYRO_KP;
}

HematologistDrive::~HematologistDrive()
{
	delete frontLeftMotor;
	delete backRightMotor;
	delete backLeftMotor;
	delete backRightMotor;
	delete gyro;
	delete gyroButton;

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

	if (oi->getJoystick('L')->GetRawButton(GYRO_TOGGLE_BUTTON) == true)
	{
		gyroButton = !gyroButton;
	}
	if(gyroButton){
		if (turn > DEADZONE || turn < -DEADZONE)
		{
			this->turn = turn;
			gyro_ref = gyro->GetAngle();
		}
		else
		{
			turn = kP * (gyro_ref - (gyro->GetAngle()));
		}
	}
	else
	{
		if(turn > DEADZONE || turn < -DEADZONE)
			this->turn = turn;
		else
			turn = 0;
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
	setForward(forward);
	setTurn(turn);
	setStrafe(strafe);
	frontLeftMotor->Set(forward + strafe + turn);
	frontRightMotor->Set(-forward + strafe + turn);
	backLeftMotor->Set(forward - strafe + turn);
	backRightMotor->Set(-forward - strafe + turn);
}

