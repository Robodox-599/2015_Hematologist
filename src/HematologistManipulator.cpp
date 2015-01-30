#include "HematologistManipulator.h"
<<<<<<< HEAD
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator()
{
	leftLiftMotor = new Talon(0);
	rightLiftMotor = new Talon(1);
	secondTierSol = new DoubleSolenoid(2, 3);
	leftLiftEncoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	rightLiftEncoder = new Encoder(2, 3, false, Encoder::EncodingType::k4X);
	manipulatorJoystick = new Joystick(2);

	rightLiftEncoder->Encoder::SetMaxPeriod(1);
	rightLiftEncoder->Encoder::SetMinRate(10);
	rightLiftEncoder->Encoder::SetDistancePerPulse(5);
	rightLiftEncoder->Encoder::SetReverseDirection(true);
	rightLiftEncoder->Encoder::SetSamplesToAverage(7);
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

/*void HematologistManipulator::moveLiftUp()
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
}*/

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

void HematologistManipulator::setLiftToPosition(int target)
{
	if(rightLiftEncoder->Get() < target && leftLiftEncoder->Get() < target)
	{
		leftLiftMotor->Set(0.5);
		rightLiftMotor->Set(0.5);
	}
	else
	{
		if(rightLiftEncoder->Get() < target + LIFTDEADZONE && rightLiftEncoder->Get() < target + LIFTDEADZONE)
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
		else
		{
			leftLiftMotor->Set(-0.5);
			rightLiftMotor->Set(-0.5);
		}
	}
}

void HematologistManipulator::preSetHeight()
{
	if(manipulatorJoystick->GetRawButton(3))
	{
		setLiftToPosition(0);
	}
	if(manipulatorJoystick->GetRawButton(4))
	{
		setLiftToPosition(30);
	}
	if(manipulatorJoystick->GetRawButton(5))
	{
		setLiftToPosition(50);
	}
}

void HematologistManipulator::activateSecondTier(int target)
{
	if(leftLiftEncoder->Get() < target && rightLiftEncoder->Get() < target)
	{
		secondTierSolForward();
	}
	else
	{
		if(leftLiftEncoder->Get() > target && rightLiftEncoder->Get() > target)
			{
				secondTierSolBackward();
			}
	}
}


HematologistManipulator::HematologistManipulator(OperatorInteface* oi)
{
	this->oi = oi;
	HematologistManipulator();
}

void HematologistManipulator::toggleBinHugger()
{
	if (manipJoystick->GetRawButton(OPEN_BIN_HUGGER_BUTTON))
	{ 
		binHuggerSolenoid->Set(DoubleSolenoid::kReverse);
	}
	else if (manipJoystick->GetRawButton(CLOSE_BIN_HUGGER_BUTTON))
	{
		binHuggerSolenoid->Set(DoubleSolenoid::kForward);
	}
}

void HematologistManipulator::moveForklift(float power)
{
	if(manipJoystick->GetRawButton(MOVE_FORKLIFT_BUTTON))
	{
		leftForkliftMotor->Set(power);
		rightForkliftMotor->Set(-power);
	}
	else
	{
		leftForkliftMotor->Set(0);
		rightForkliftMotor->Set(0);
	}
}
