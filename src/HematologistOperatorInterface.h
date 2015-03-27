#ifndef HEMATOLOGIST_OPERATOR_INTERFACE_H
#define HEMATOLOGIST_OPERATOR_INTERFACE_H

#include "HematologistMacros.h"

class HematologistOperatorInterface
{
public:
	HematologistOperatorInterface();
	~HematologistOperatorInterface();

	Joystick* getJoystick(char whichJosytick);
	SmartDashboard* getDashboard();
private:
	Joystick* leftDriveJoystick;
	Joystick* rightDriveJoystick;
	Joystick* manipJoystick;
	SmartDashboard* dashboard;

};

#endif