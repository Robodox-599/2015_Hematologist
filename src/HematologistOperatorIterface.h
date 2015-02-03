#ifndef HEMATOLOGIST_OPERATOR_INTERFACE_H_
#define HEMATOLOGIST_OPERATOR_INTERFACE_H_

class HematologistOperatorInterface
{
public:
	HematologistOperatorInterface();
	~HematologistOperatorInterface();
private:
	Joystick* leftJoystick;
	Joystick* rightJoystick;
	SmartDashboard* dashboard;
};

#endif