#include "HematologistDrive.h"

HematologistDrive::HematologistDrive(HematologistOperatorInterface* oi)
{
	frontLeftMotor 	= new Talon(FRONT_LEFT_MOTOR_CHANNEL);
	backLeftMotor 	= new Talon(BACK_LEFT_MOTOR_CHANNEL);
	frontRightMotor	= new Talon(FRONT_RIGHT_MOTOR_CHANNEL);
	backRightMotor	= new Talon(BACK_RIGHT_MOTOR_CHANNEL);

	frontLeftEncoder = new Encoder(FRONT_LEFT_ENCODER_CHANNEL_A, FRONT_LEFT_ENCODER_CHANNEL_B);
	backLeftEncoder = new Encoder(BACK_LEFT_ENCODER_CHANNEL_A, BACK_LEFT_ENCODER_CHANNEL_B);
	frontRightEncoder = new Encoder(FRONT_RIGHT_ENCODER_CHANNEL_A, FRONT_RIGHT_ENCODER_CHANNEL_B);
	backRightEncoder = new Encoder(BACK_RIGHT_ENCODER_CHANNEL_A, BACK_RIGHT_ENCODER_CHANNEL_B);

	frontRightEncoder->SetReverseDirection(true);
	backRightEncoder->SetReverseDirection(true);

	gyro = new Gyro(1);
	gyro_ref = 0;
	gyroButton = false;

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
		this->forward = 0;
	}
	return this->forward;
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
			this->turn = 0;
	}
	return this->turn;
}


float HematologistDrive::setStrafe(float strafe)
{
	if (strafe > DEADZONE || strafe < -DEADZONE)
	{
		this->strafe = strafe;
	}else
	{
		this->strafe = 0;
	}
	return this->strafe;
}

float HematologistDrive::linearizeDrive(float driveInput)
{
	if (driveInput > DEADZONE)
		return (1/.9)*(driveInput - .1);
	else
		if (driveInput < -DEADZONE)
			return (1/.9)*(driveInput + .1);
		else
			return 0;
}

void  HematologistDrive::drive(float forward, float turn, float strafe)
{
	setForward(forward);
	setTurn(turn);
	setStrafe(strafe);
	frontLeftMotor->Set(linearizeDrive(forward - strafe + turn));
	frontRightMotor->Set(linearizeDrive(-forward + strafe + turn));
	backLeftMotor->Set(linearizeDrive(forward + strafe + turn));
	backRightMotor->Set(linearizeDrive(-forward - strafe + turn));
}

Encoder* HematologistDrive::getEncoder(bool front, bool right)
{
  if (front)
  {
    if (right)
      return frontRightEncoder;
    else
      return frontLeftEncoder;
  }
  else
  {
    if (right)
      return backRightEncoder;
    else
      return backLeftEncoder;
  }
}

Talon* HematologistDrive::getDriveTalon(bool front, bool right)
{
  if (front)
  {
    if (right)
      return frontRightMotor;
    else
      return frontLeftMotor;
  }
  else
  {
    if (right)
      return backRightMotor;
    else
      return backLeftMotor;
  }
}
