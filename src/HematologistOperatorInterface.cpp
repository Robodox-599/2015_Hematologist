#include "HematologistOperatorInterface.h"

HematologistOperatorInterface::HematologistOperatorInterface()
{
	leftJoystick = new Joystick(1);
	rightJoystick = new Joystick(2);
}

HematologistOperatorInterface::~HematologistOperatorInterface()
{
	delete leftJoystick;
	delete rightJoystick;

	leftJoystick = NULL;
	rightJoystick = NULL;
}


