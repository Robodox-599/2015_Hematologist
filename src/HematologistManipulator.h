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



public:
	void openBinHugger();
	void openForklift();
	void openSecondTier();

	void openBinHuggerButton();
	void openForkliftButton();
	void openSecondTierButton();

};

#endif