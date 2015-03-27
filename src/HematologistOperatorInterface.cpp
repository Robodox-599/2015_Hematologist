#include "HematologistOperatorInterface.h"

HematologistOperatorInterface::HematologistOperatorInterface()
{
	leftDriveJoystick 	= new Joystick(LEFT_DRIVE_JOYSTICK_PORT);
	rightDriveJoystick	= new Joystick(RIGHT_DRIVE_JOYSTICK_PORT);
	manipJoystick		= new Joystick(MANIP_JOYSTICK_PORT);
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

Joystick* HematologistOperatorInterface::getJoystick(char whichJoystick)
{
	if (whichJoystick == 'L')
		return leftDriveJoystick;
	if (whichJoystick == 'R')
		return rightDriveJoystick;
	if (whichJoystick == 'M')
		return manipJoystick;
	return leftDriveJoystick;	//arbitrary set as the default
}

SmartDashboard* HematologistOperatorInterface::getDashboard()
{
	return dashboard;
}
