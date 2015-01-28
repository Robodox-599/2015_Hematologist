#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_
#include "WPILib.h"


class HematologistManipulator
{
private:
	Talon* leftLiftMotor;
	Talon* rightLiftMotor;
	DoubleSolenoid* secondTierSol;
	Encoder* leftLiftEncoder;
	Encoder* rightLiftEncoder;
	Joystick* manipulatorJoystick;

public:
	HematologistManipulator();
	virtual ~HematologistManipulator();

	void moveLiftUp();
	void moveLiftDown();

	void secondTierSolForward();
	void secondTierSolBackward();
	void secondTierSolStop();
};


#endif
