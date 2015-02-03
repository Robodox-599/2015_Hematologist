#include "HematologistOperatorInterface.h"

HematologistOperatorInterface::HematologistOperatorInterface()
{
	leftDriveJoystick = new Josytick(LEFT_DRIVE_JOYSTICK);
	rightDriveJoystick = new Josytick(RIGHT_DRIVE_JOYSTICK);
	manipJoystick = new Joystick(MANIP_JOYSTICK);
	dashboard->init();
}