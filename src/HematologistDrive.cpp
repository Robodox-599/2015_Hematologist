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

	frontRightEncoder->SetReverseDirection(true);
	backRightEncoder->SetReverseDirection(true);

	forward = 0;
	turn = 0;
	strafe = 0;
}

HematologistDrive::~HematologistDrive()
{
	delete frontLeftMotor;
	delete frontRightMotor;
	delete backLeftMotor;
<<<<<<< HEAD
	delete backRightMotor;

=======
	delete frontRightMotor; //was "delete backRightMotor"
>>>>>>> f88f0b8b7432cdb8b1e38f4b3e1649fd618c64ff
	delete frontLeftEncoder;
	delete frontRightEncoder;
	delete backLeftEncoder;
	delete backRightEncoder;

	frontLeftMotor = NULL;
	frontRightMotor = NULL;
	backLeftMotor = NULL;
	backRightMotor = NULL;
	frontLeftEncoder = NULL;
	frontRightEncoder = NULL;
	backLeftEncoder = NULL;
	backRightEncoder = NULL;
}

void HematologistDrive::setForward(float forward)
{
	if (forward > DEADZONE || forward < -DEADZONE)
	{
		this->forward = forward;
	}else
	{
		this->forward = 0;
	}
}

void HematologistDrive::setTurn(float turn)
{
	if (turn > DEADZONE || turn < -DEADZONE)
	{
		this->turn = turn;
	}else
	{
		this->turn = 0;
	}
}

void HematologistDrive::setStrafe(float strafe)
{
	if (strafe > DEADZONE || strafe < -DEADZONE)
	{
		this->strafe = strafe;
	}else
	{
		this->strafe = 0;
	}
}


float HematologistDrive::getForward()
{
	return forward;
}

float HematologistDrive::getTurn()
{
	return turn;
}

float HematologistDrive::getStrafe()
{
	return strafe;
}

/*
The return value is derived from the point-slope equation
y - y1 = m(x-x1)
where y is the value given to the motors
where x is the value of the joysticks
*/
float HematologistDrive::linearizeDrive(float input)
{
	if (input > DEADZONE)
		return (1/(1-DEADZONE)) * (input - DEADZONE);
	else
		if (input < -DEADZONE)
			return (1/(1-DEADZONE)) * (input + DEADZONE);
		else
			return 0;
}

void HematologistDrive::drive(float forward, float turn, float strafe)
{
	setForward(forward);
	setTurn(turn *.75);	//turning made stack fall automatic slowing of it
	setStrafe(strafe);

	frontLeftMotor->Set(linearizeDrive(this->forward - this->turn + this->strafe));
	frontRightMotor->Set(linearizeDrive(-this->forward - this->turn - this->strafe));
	backLeftMotor->Set(linearizeDrive(this->forward - this->turn - this->strafe));
	backRightMotor->Set(linearizeDrive(-this->forward - this->turn + this->strafe));

}

float HematologistDrive::getForwardAverage()
{
	float average = (frontLeftEncoder->Get() + frontRightEncoder->Get() + backLeftEncoder->Get() + backRightEncoder->Get())/4.0;
	return average;
}

float HematologistDrive::getTurnAverage()
{
	float average =(frontLeftEncoder->Get() - frontRightEncoder->Get() + backLeftEncoder->Get() - backRightEncoder->Get())/4.0; 
	return average;
}

float HematologistDrive::getStrafeAverage()
{
	float average = (frontLeftEncoder->Get() - frontRightEncoder->Get() - backLeftEncoder->Get() + backRightEncoder->Get())/4.0;
	return average;
}

void HematologistDrive::resetEncoders()
{
	frontLeftEncoder->Reset();
	frontRightEncoder->Reset();
	backLeftEncoder->Reset();
	backRightEncoder->Reset();
}
void HematologistDrive::resetEncoders(bool reset)
{
	if(reset)
	{
		resetEncoders();
	}
}
