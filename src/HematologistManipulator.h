#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "WPILib.h"
#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"

class HematologistManipulator
{
private:
	Talon* leftLiftMotor;
	Talon* rightLiftMotor;
	DoubleSolenoid* secondTierSol;
	Encoder *encLift;
	Joystick* manipulatorJoystick;
	double liftHeight;
	
	DoubleSolenoid* solenoid;

	Talon* rightForkliftMotor;
	Talon* leftForkliftMotor; 

	OperatorInterface* oi;

public:
	HematologistManipulator();
	HematologistManipulator(OperatorInterface* oi);
	virtual ~HematologistManipulator();

	void moveLiftUp();
	void moveLiftDown();

	void secondTierSolForward();
	void secondTierSolBackward();
	void secondTierSolStop();

	void setLiftToPosition(int target);
	void preSetHeight();
	void activateSecondTier(int target);
	
	void toggleBinHugger();
	void moveForklift(float power);

};
#endif
