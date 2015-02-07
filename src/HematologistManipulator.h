#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "HematologistMacros.h"

class HematologistManipulator
{
private:
	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	DoubleSolenoid* secondTierPiston;
	DoubleSolenoid* binHuggerPiston;
	DoubleSolenoid* forkliftPiston;
	Joystick* manipJoystick;



	bool disableEncoders;


public:
	void openBinHugger();
	void openForklift();
	void openSecondTier();

	void resetEncoders();

	HematologistManipulator(Joystick* manipJoystick);
	~HematologistManipulator();

};

#endif
