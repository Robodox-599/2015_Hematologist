#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "WPILib.h"
#include "HematologistMacros.h"

class HematologistManipulator
{
private:

	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	DoubleSolenoid* binHuggerSol;
	DoubleSolenoid* secondTierSol;
	DoubleSolenoid* forkliftSol;

	Encoder* liftEncoder;

public:

	HematologistManipulator();
	virtual ~HematologistManipulator();

	void setForkliftSol(int input);
	void setSecondTierSol(int input);
	void setBinHuggerSol(int input);

	void activateSecondTier(int target);
	void activateBinHugger(bool open, bool close);

	void manualLiftControl(bool up, bool down, float power);
	void setLiftToPosition(int target, float power);
	void preSetHeight(bool low, bool mid, bool high, float power);

};


#endif
