#include "HematologistManipulator.h"


HematologistManipulator::HematologistManipulator()
{
	leftLiftMotor = new Talon(0);
	rightLiftMotor = new Talon(1);
	secondTierSol = new DoubleSolenoid(2, 3);
	leftLiftEncoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	rightLiftEncoder = new Encoder(2, 3, false, Encoder::EncodingType::k4X);
	manipulatorJoystick = new Joystick(2);
}


HematologistManipulator::~HematologistManipulator()
{
	delete leftLiftMotor;
	delete rightLiftMotor;
	delete secondTierSol;
	delete leftLiftEncoder;
	delete rightLiftEncoder;
	delete manipulatorJoystick;

	leftLiftMotor = NULL;
	rightLiftMotor = NULL;
	secondTierSol = NULL;
	leftLiftEncoder = NULL;
	rightLiftEncoder = NULL;
	manipulatorJoystick = NULL;
}

void HematologistManipulator::moveLiftUp()
{
	//moves lift up
	if(manipulatorJoystick->GetRawButton(4))
	{
		leftLiftMotor->Set(0.5);
		rightLiftMotor->Set(0.5);
	}
	else
	{
		leftLiftMotor->Set(0);
		rightLiftMotor->Set(0);
	}
}

void HematologistManipulator::moveLiftDown()
{
		//moves lift down
	if(manipulatorJoystick-> GetRawButton(5))
	{
		leftLiftMotor->Set(-0.5);
		rightLiftMotor->Set(-0.5);
	}
	else
	{
		leftLiftMotor->Set(0);
		rightLiftMotor->Set(0);
	}
}

void HematologistManipulator::secondTierSolForward()
{
	secondTierSol->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::secondTierSolBackward()
{
	secondTierSol->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::secondTierSolStop()
{
	secondTierSol->Set(DoubleSolenoid::kOff);
}

void HematologistManipulator::encoder()
{
	rightLiftEncoder->Start();
}


