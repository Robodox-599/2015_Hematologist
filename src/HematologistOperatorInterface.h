#ifndef HEMATOLOGIST_OPERATOR_INTERFACE_H
#define HEMATOLOGIST_OPERATOR_INTERFACE_H

#include "HematologistMacros.h"

class HematologistOperatorInterface
{
public:
	HematologistOperatorInterface();
	~HematologistOperatorInterface();

    //returns a joystick
    //'L' = LeftDriveJoystick
    //'R' = rightDriveJoystick
    //'M' = ManipJoystick
    //returns leftDriveJoystick if you pass in a character that isn't L, R, or M
	Joystick* getJoystick(char whichJosytick);     
	SmartDashboard* getDashboard();
private:
	Joystick* leftDriveJoystick;
	Joystick* rightDriveJoystick;
	Joystick* manipJoystick;
	SmartDashboard* dashboard;

};

#endif