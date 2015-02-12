#include "HematologistOperatorInterface.h"

HematologistOperatorInterface::HematologistOperatorInterface()
{
	leftDriveJoystick = new Joystick(LEFT_DRIVE_JOYSTICK);
	rightDriveJoystick = new Joystick(RIGHT_DRIVE_JOYSTICK);
	manipJoystick = new Joystick(MANIP_JOYSTICK);
	dashboard->init();
}

HematologistOperatorInterface::~HematologistOperatorInterface()
{
	delete leftDriveJoystick;
	delete rightDriveJoystick;
	delete manipJoystick;

	leftDriveJoystick = NULL;
	rightDriveJoystick = NULL;
	manipJoystick = NULL;
	dashboard = NULL;
}

float HematologistOperatorInterface::getJoystickValue(char whichOne, char whichAxis)
{
	Joystick* joystick;
	(whichOne == 'L') ? (joystick = leftDriveJoystick) : ();
	else
	{
		if (whichOne == 'R')
		{
			joystick = rightDriveJoystick;
		}
		else
		{
			joystick = manipJoystick;
		}
	}

	(whichAxis == 'X') ? (return joystick->GetX()) : (return joystick->GetY());
}

Joystick* HematologistOperatorInterface::getJoystick(char whichJoystick)
{
	if (whichJoystick == 'L')
	{
		return leftDriveJoystick;
	}
	else
	{
		(whichJoystick == 'R') ? (return rightDriveJoystick) : (return manipJoystick);
	}
}

SmartDashboard* HematologistOperatorInterface::getDashboard()
{
	return dashboard;
}
