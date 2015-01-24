#include "HematologistOperatorInterface.h"

HematologistOperatorInterface::HematologistOperatorInterface()
{
	leftJoystick = new Joystick(0);
	rightJoystick = new Joystick(1);
}

HematologistOperatorInterface::~HematologistOperatorInterface()
{
	delete leftJoystick;
	delete rightJoystick;

	leftJoystick = NULL;
	rightJoystick = NULL;
}




