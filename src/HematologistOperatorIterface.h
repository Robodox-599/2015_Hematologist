#ifndef HEMATOLOGIST_OPERATOR_INTERFACE_H_
#define HEMATOLOGIST_OPERATOR_INTERFACE_H_

class HematologistOperatorInterface
{
public:
	HematologistOperatorInterface();
	~HematologistOperatorInterface();
private:
	Joystick* leftDriveJoystick;
	Joystick* rightDriveJoystick;
	Joystick* manipJoystick;
	SmartDashboard* dashboard;
};

#endif