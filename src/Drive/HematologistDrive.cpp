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

  //these encoders had to be reversed because when I moved forward, it said it was moving backward
	frontRightEncoder->SetReverseDirection(true);  //reverses the encoder so that when it moves backward, counts up not down
	backRightEncoder->SetReverseDirection(true);   //reverses the encoder so that when it moves backward, counts up not down

	forward = 0;
	turn = 0;
	strafe = 0;
}

HematologistDrive::~HematologistDrive()
{
	delete frontLeftMotor;
	delete frontRightMotor;
	delete backLeftMotor;
	delete backRightMotor;

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

the slope is : 1/(1-DEADZONE) (it's 1 because 1 is the max/min of the joystick values)
x1, y1 = (DEADZONE, 0)
y = the value that we're returning
x = the value of the joystick

therefore:
y = m(x - x1) + 0
y = (1/(1-DEADZONE)) * (input - DEADZONE)

*/
float HematologistDrive::linearizeDrive(float input)
{
	if (input > DEADZONE)
		return (1/(1-DEADZONE)) * (input - DEADZONE);     //the derivation is above
	else
		if (input < -DEADZONE)
			return (1/(1-DEADZONE)) * (input + DEADZONE);   //this must be input + DEADZONE to account for the fact that DEADZONE is a negative number
		else
			return 0;                                       //if inside DEADZONE, motors shouldn't move
}

void HematologistDrive::drive(float forward, float turn, float strafe)
{
	setForward(forward);
	setTurn(turn *.75);	//turning made stack fall. This ensures that the robot moves slower to prevent that
	setStrafe(strafe);

	frontLeftMotor->Set(linearizeDrive(this->forward - this->turn + this->strafe));    //sets motors to adjusted value of sum of forward/turn/strafe
	frontRightMotor->Set(linearizeDrive(-this->forward - this->turn - this->strafe));  //sets motors to adjusted value of sum of forward/turn/strafe  
	backLeftMotor->Set(linearizeDrive(this->forward - this->turn - this->strafe));     //sets motors to adjusted value of sum of forward/turn/strafe
	backRightMotor->Set(linearizeDrive(-this->forward - this->turn + this->strafe));   //sets motors to adjusted value of sum of forward/turn/strafe

  //it's difficult to tell which motors are reversed but it's the one with -this->forward
  //the math behind how you add/subtract turn is simple. 
  //if reversed properly, here's how it should be:
  //frontLeft   = forward + turn + strafe
  //frontRight  = forward - turn - strafe
  //backLeft    = forward + turn - strafe
  //backRight   = forward - turn + strafe
  //to reverse a motor, in front
  //ex: to reverse frontLeft, you get that frontLeft = -(forward + turn + strafe)
}

float HematologistDrive::getForwardAverage()
{
	float average = (frontLeftEncoder->Get() + frontRightEncoder->Get() + backLeftEncoder->Get() + backRightEncoder->Get())/4.0;
	return average;
}

float HematologistDrive::getTurnAverage()
{
  //make the right encoders negative so that when you turn right, the encoders give a positive value
	float average =(frontLeftEncoder->Get() - frontRightEncoder->Get() + backLeftEncoder->Get() - backRightEncoder->Get())/4.0; 
	return average;
}

float HematologistDrive::getStrafeAverage()
{
  //reverse the frontRight and the backLeft so that when you strafe right the encoders give a positive value
	float average = (frontLeftEncoder->Get() - frontRightEncoder->Get() - backLeftEncoder->Get() + backRightEncoder->Get())/4.0;
	return average;
}

void HematologistDrive::resetEncoders()
{
	frontLeftEncoder->Reset();   //resets the encoders
	frontRightEncoder->Reset();  //resets the encoders
	backLeftEncoder->Reset();    //resets the encoders
	backRightEncoder->Reset();   //resets the encoders
}
void HematologistDrive::resetEncoders(bool reset)
{
  //button put in, if buttton pressed, then encoders reset
	if(reset)
	{
		resetEncoders();
	}
  //no else statement because an else would be run every time the button isn't pressed
  //which is most of the time
  //generally for buttons, you don't want elses
}
