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

	Encoder* liftEncoder;
	Encoder* forkliftEncoder;

public:

	HematologistManipulator();
	virtual ~HematologistManipulator();

	void manualLiftControl(bool up, bool down, float power);
	void setLiftToPosition(int target, float power);
	void preSetHeight(bool low, bool mid, bool high, float power);

	void moveForklift(bool up, bool down, float power);

	void openSecondTierSol();
	void closeSecondTierSol();
	void stopSecondTierSol();
	void activateSecondTier(int target);

	void toggleBinHugger(bool on, bool off);
};


#endif
