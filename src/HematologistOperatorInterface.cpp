#include "HematologistOperatorInterface.h"

HematologistOperatorInterface::HematologistOperatorInterface()
{
	leftJoystick = new Joystick(0);
	rightJoystick = new Joystick(1);
	dashboard->init();
}

HematologistOperatorInterface::~HematologistOperatorInterface()
{
	delete leftJoystick;
	delete rightJoystick;
	delete dashboard;

	leftJoystick = NULL;
	rightJoystick = NULL;
	dashboard = NULL;
}




