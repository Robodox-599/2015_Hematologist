#ifndef HEMATOLOGIST_OPERATOR_INTERFACE_H
#define HEMATOLOGIST_OPERATOR_INTERFACE_H
#include "HematologistMacros.h"
#include "WPILib.h"

class HematologistOperatorInterface
{
public:
	HematologistOperatorInterface();
	~HematologistOperatorInterface();

	Joystick *leftJoystick;
	Joystick *rightJoystick;
	SmartDashboard* dashboard;

	void printForkliftPower();


private:
};
#endif
