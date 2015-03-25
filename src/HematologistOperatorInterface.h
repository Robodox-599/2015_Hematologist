#ifndef HEMATOLOGIST_OPERATOR_INTERFACE_H_
#define HEMATOLOGIST_OPERATOR_INTERFACE_H_

#include "HematologistMacros.h"

class HematologistOperatorInterface
{
public:
	HematologistOperatorInterface();
	~HematologistOperatorInterface();

	float getJoystickValue(char whichJoystick, char whichAxis);

	Joystick* getJoystick(char whichJoystick);

	SmartDashboard* getDashboard();
private:
	Joystick* leftDriveJoystick;
	Joystick* rightDriveJoystick;
	Joystick* manipJoystick;
	SmartDashboard* dashboard;
};
#endif
