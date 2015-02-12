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
	if (whichOne == 'L')
	{
		joystick = leftDriveJoystick;
	}
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

	if (whichAxis == 'X')
	{
		return joystick->GetX();
	}else
	{
		return joystick->GetY();
	}
}

Joystick* HematologistOperatorInterface::getJoystick(char whichJoystick)
{
	if (whichJoystick == 'L')
	{
		return leftDriveJoystick;
	}
	else
	{
		if (whichJoystick == 'R')
		{
			return rightDriveJoystick;
		}else
		{
			return manipJoystick;
		}
	}
}

SmartDashboard* HematologistOperatorInterface::getDashboard()
{
	return dashboard;
}
