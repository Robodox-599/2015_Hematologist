#include "HematologistManipulator.h"
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator()
{
	leftLiftMotor = new Talon(0);
	rightLiftMotor = new Talon(1);
	secondTierSol = new DoubleSolenoid(2, 3);
	leftLiftEncoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	rightLiftEncoder = new Encoder(2, 3, false, Encoder::EncodingType::k4X);
	manipulatorJoystick = new Joystick(2);
	buttonPressed = false;
	presetValue = 0;

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
	delete buttonPressed;
	delete presetValue;

	leftLiftMotor = NULL;
	rightLiftMotor = NULL;
	secondTierSol = NULL;
	leftLiftEncoder = NULL;
	rightLiftEncoder = NULL;
	manipulatorJoystick = NULL;
	buttonPressed = NULL;
	presetValue = 0;
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

void HematologistManipulator::secondTierClawClosed()
{
	secondTierSol->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::secondTierClawOpen()
{
	secondTierSol->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::secondTierSolStop()
{
	secondTierSol->Set(DoubleSolenoid::kOff);
}

void HematologistManipulator::setLiftToPosition()
{
	if(buttonPressed == true)
	{
		if(rightLiftEncoder->Get() < presetValue && leftLiftEncoder->Get() < presetValue)
			{
				leftLiftMotor->Set(0.5);
				rightLiftMotor->Set(0.5);
			}
			else
			{
				if(rightLiftEncoder->Get() < presetValue + LIFTDEADZONE && rightLiftEncoder->Get() < presetValue + LIFTDEADZONE)
				{
					leftLiftMotor->Set(0);
					rightLiftMotor->Set(0);
					buttonPressed = false;
				}
				else
				{
					leftLiftMotor->Set(-0.5);
					rightLiftMotor->Set(-0.5);
				}
			}
	}
}

void HematologistManipulator::buttonIsPressed()
{
	if(manipulatorJoystick->GetRawButton(3))
	{
		buttonPressed = true;
	}

	if(manipulatorJoystick->GetRawButton(4))
	{
		buttonPressed = true;
	}

	if(manipulatorJoystick->GetRawButton(5))
	{
		buttonPressed = true;
	}
}

void HematologistManipulator::preSetHeight()
{
	if(manipulatorJoystick->GetRawButton(3))
	{
		presetValue = 0;
	}
	if(manipulatorJoystick->GetRawButton(4))
	{
		presetValue = 30;
	}
	if(manipulatorJoystick->GetRawButton(5))
	{
		presetValue = 50;
	}
}

void HematologistManipulator::activateSecondTier(int target)
{
	if(leftLiftEncoder->Get() < target && rightLiftEncoder->Get() < target)
	{
		secondTierClawClosed();
	}
	else
	{
		if(leftLiftEncoder->Get() > target && rightLiftEncoder->Get() > target)
			{
				secondTierClawOpen();
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
		solenoid->Set(DoubleSolenoid::kReverse);
	}
	else if (manipJoystick->GetRawButton(CLOSE_BIN_HUGGER_BUTTON))
	{
		solenoid->Set(DoubleSolenoid::kForward);
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

