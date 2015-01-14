#ifndef HEMATOLOGIST_OPERATOR_INTERFACE_H
#define HEMATOLOGIST_OPERATOR_INTERFACE_H
#include "HematologistMacros.h"

class HematologistOperatorInterface
{
public:
	HematologistOperatorInterface();
	~HematologistOperatorInterface();

private:
	Joystick *leftJoystick;
	Joystick *rightJoystick;

};
#endif
