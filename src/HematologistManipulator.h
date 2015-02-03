#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "WPILib.h"
#include "HematologistMacros.h"

class HematologistManipulator
{
private:

	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	DoubleSolenoid* secondTierSol;
	DoubleSolenoid* binHuggerSol;
	DoubleSolenoid* forkLiftSol;

	Encoder* leftLiftEncoder;
	Encoder* rightLiftEncoder;

public:

	HematologistManipulator();
	virtual ~HematologistManipulator();

	void manualLiftControl(bool up, bool down, float power);
	void setLiftToPosition(int target, float power);
	void preSetHeight(bool low, bool mid, bool high, float power);

	void moveForklift(bool up, bool down, float power);

	void secondTierClosed();
	void secondTierOpen();
	void secondTierStop();
	void activateSecondTier(int target);

	void toggleBinHugger(bool on, bool off);
	void toggleForkLift(bool open, bool closed); 
};


#endif