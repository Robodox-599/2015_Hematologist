#include "HematologistManipulator.h"
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator()
{
	leftLiftMotor = new Talon(0);
	rightLiftMotor = new Talon(1);
	leftForkliftMotor = new Talon(2);
	rightForkliftMotor = new Talon(3);
	secondTierSol = new DoubleSolenoid(2, 3);
	forkLiftSol = new DoubleSolenoid(1,4);
	liftEncoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	manipulatorJoystick = new Joystick(2);
	buttonPressed = false;
	presetValue = 0;
	oi = new HematologistOperatorInterface();

	liftEncoder->SetMaxPeriod(1);
	liftEncoder->SetMinRate(10);
	liftEncoder->SetDistancePerPulse(5);
	liftEncoder->SetReverseDirection(true);
	liftEncoder->SetSamplesToAverage(7);
}


HematologistManipulator::~HematologistManipulator()
{
	delete leftLiftMotor;
	delete rightLiftMotor;
	delete secondTierSol;
	delete liftEncoder;
	delete manipulatorJoystick;
	delete buttonPressed;
	delete presetValue;

	leftLiftMotor = NULL;
	rightLiftMotor = NULL;
	secondTierSol = NULL;
	liftEncoder = NULL;
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
		if(liftEncoder->Get() < presetValue)
			{
				leftLiftMotor->Set(0.5);
				rightLiftMotor->Set(0.5);
			}
			else
			{
				if(liftEncoder->Get() < presetValue + LIFTDEADZONE)
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
	if(liftEncoder->Get() < target)
	{
		secondTierClawClosed();
	}
	else
	{
		if(liftEncoder->Get() > target)
			{
				secondTierClawOpen();
			}
	}
}


HematologistManipulator::HematologistManipulator(HematologistOperatorInterface* oi)
{
	this->oi = oi;
	HematologistManipulator();
}

void HematologistManipulator::toggleBinHugger()
{
	if (manipulatorJoystick->GetRawButton(1)) /*OPEN_BIN_HUGGER_BUTTON*/
	{ 
		forkLiftSol->Set(DoubleSolenoid::kReverse);
	}
	else if (manipulatorJoystick->GetRawButton(2)) /*CLOSE_BIN_HUGGER_BUTTON*/
	{
		forkLiftSol->Set(DoubleSolenoid::kForward);
	}
}

void HematologistManipulator::moveForklift(float power)
{
	if(manipulatorJoystick->GetRawButton(3)) /*MOVE_FORKLIFT_BUTTON*/
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

