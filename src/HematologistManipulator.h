#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "WPILib.h"
#include "HematologistMacros.h"

class HematologistManipulator
{
private:

	Talon* leftLiftMotor;
	Talon* rightLiftMotor;
	Talon* rightForkliftMotor;
	Talon* leftForkliftMotor;

	DoubleSolenoid* secondTierSol;
	DoubleSolenoid* binHuggerSol;

	Encoder* leftLiftEncoder;
	Encoder* rightLiftEncoder;

	Joystick* manipulatorJoystick;

public:

	HematologistManipulator();
	virtual ~HematologistManipulator();

//	void moveLiftUp();
//	void moveLiftDown();
	void setLiftToPosition(int target, float power);
	void preSetHeight(bool low, bool mid, bool high);

	void moveForklift(bool up, bool down, float power);

	void secondTierSolForward();
	void secondTierSolBackward();
	void secondTierSolStop();
	void activateSecondTier(int target);

	void toggleBinHugger(bool on, bool off);
};


#endif
