#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
{
	solenoid = new DoubleSolenoid(1);

	leftForkliftMotor = new Talon(1);
	rightForkliftMotor = new Talon(1);
}

virtual HematologistManipulator::~HematologistManipulator()
{
	delete solenoid;
	delete leftForkliftMotor;
	delete rightForkliftMotor;

	leftForkliftMotor = NULL;
	rightForkliftMotor = NULL;
	solenoid = NULL;
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