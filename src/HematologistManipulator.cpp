#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
{
	solenoid = new DoubleSolenoid();

	ManipJoystick = new joystick();

}

bool HematologistManipulator::openBinHugger(int buttonNum)
{
	if (joystick->GetRawButton(buttonNum))
	{

	}
}



virtual HematologistManipulator::~HematologistManipulator()
{
	delete solenoid;

	solenoid = NULL;
}

