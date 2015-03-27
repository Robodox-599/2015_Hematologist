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
	delete dashboard;
	
	leftDriveJoystick = NULL;
	rightDriveJoystick = NULL;
	manipJoystick = NULL;
	dashboard = NULL;
}

