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

	leftJoystick = NULL;
	rightJoystick = NULL;
}

void HematologistOperatorInterface::printForkliftPower()
{
	//dashboard->PutNumber("Forklift Power: ", leftForkliftMotor->Get());
}



