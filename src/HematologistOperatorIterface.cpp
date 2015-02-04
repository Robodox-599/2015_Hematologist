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
	delete dashboard;

	leftDriveJoystick = NULL;
	rightDriveJoystick = NULL;
	manipJoystick = NULL;
	dashboard = NULL;
}

HematologistOperatorInterface::getJoystickValue(string whichOne, char whichAxis)
{
	Joystick* joystick;
	if (whichOne.compare("Left"))
	{
		joystick = leftDriveJoystick;
	}
	else
	{
		if (whichOne.compare("Right"))
		{
			joystick = rightDriveJoystick;
		}
		else
		{
			joystick = manipJoystick;
		}
	}

	if (whichAxis == X)
	{
		return joystick->GetX();
	}
	else
	{
		return joystick->GetY();
	}
}