#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
{
	solenoid = new DoubleSolenoid();

	ManipJoystick = new joystick();

}

void HematologistManipulator::openBinHugger()
{
	if (joystick->GetRawButton(OPEN_BIN_HUGGER_BUTTON))
	{
		solenoid->Set(DoubleSolenoid::kReverse);
	}
	else
	{
		if (joystick->GetRawButton(CLOSE_BIN_HUGGER_BUTTON))
		{
			solenoid->Set(DoubleSolenoid::kForward);
		}
	}
}



virtual HematologistManipulator::~HematologistManipulator()
{
	delete solenoid;

	solenoid = NULL;
}

