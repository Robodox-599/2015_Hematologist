#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
{
	//Motor-based manipulators
	leftLiftMotor = new Talon(0);
	rightLiftMotor = new Talon(1);
	leftForkliftMotor = new Talon(2);
	rightForkliftMotor = new Talon (3);

	//Solenoids
	binHuggerSol = new DoubleSolenoid(5, 6);
	secondTierSol = new DoubleSolenoid(2, 3);

	//Encoders
	encLift = new Encoder(0,1,false, Encoder::EncodingType::k4X);
	count = 0;
}


HematologistManipulator::~HematologistManipulator()
{
	delete leftLiftMotor;
	delete rightLiftMotor;
	delete leftForkliftMotor;
	delete rightForkliftMotor;
	delete binHuggerSol;
	delete secondTierSol;
	delete encLift;

	leftLiftMotor = NULL;
	rightLiftMotor = NULL;
	leftForkliftMotor = NULL;
	rightForkliftMotor = NULL;
	binHuggerSol = NULL;
	secondTierSol = NULL;
	encLift = NULL;
}

void HematologistManipulator::moveForklift(bool up, bool down, float power)
{
	if(up)
	{
		leftForkliftMotor->Set(power);
		rightForkliftMotor->Set(-power);
	}
	else
	{
		if(down)
		{
			leftForkliftMotor->Set(-power);
			rightForkliftMotor->Set(power);
		}
		else
		{
			leftForkliftMotor->Set(0);
			rightForkliftMotor->Set(0);
		}
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

void HematologistManipulator::activateSecondTier(int target)
{
	if(encLift->Get() < target)
	{
		secondTierSolForward();
	}
	else
	{
		if(encLift->Get() > target)
		{
			secondTierSolBackward();
		}
	}
}

void HematologistManipulator::manualLiftControl(bool up, bool down, float power)
{
	//moves lift up
	if(up)
	{
		leftLiftMotor->Set(power);
		rightLiftMotor->Set(power);
	}
	else
	{
		if(down)
		{
			leftLiftMotor->Set(-power);
			rightLiftMotor->Set(-power);
		}
		else
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
	}
}

void HematologistManipulator::setLiftToPosition(int target, float power)
{
	if(encLift->Get() < target)
	{
		leftLiftMotor->Set(power);
		rightLiftMotor->Set(power);
	}
	else
	{
		if(encLift->Get() < target + LIFTDEADZONE)
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
		else
		{
			leftLiftMotor->Set(-power);
			rightLiftMotor->Set(-power);
		}
	}
}

void HematologistManipulator::preSetHeight(bool low, bool mid, bool high)
{
	if(low)
	{
		setLiftToPosition(0, 0.5);
	}
	if(mid)
	{
		setLiftToPosition(30, 0.5);
	}
	if(high)
	{
		setLiftToPosition(50, 0.5);
	}
}

void HematologistManipulator::toggleBinHugger(bool on, bool off)
{
	if (on)
	{ 
		binHuggerSol->Set(DoubleSolenoid::kReverse);
	}
	else if (off)
	{
		binHuggerSol->Set(DoubleSolenoid::kForward);
	}
}

