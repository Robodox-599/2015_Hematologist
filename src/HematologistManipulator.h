#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "WPILib.h"
#include "HematologistOperatorInterface.h"
#include "HematologistMacros.h"

class HematologistManipulator
{
private:
	Talon* leftLiftMotor;
	Talon* rightLiftMotor;
	DoubleSolenoid* secondTierSol;
	Encoder* leftLiftEncoder;
	Encoder* rightLiftEncoder;
	Joystick* manipulatorJoystick;
	bool buttonPressed; //true = button is pressed
	int presetValue;
	
	DoubleSolenoid* forkLiftSol;

	Talon* rightForkliftMotor;
	Talon* leftForkliftMotor; 

	OperatorInterface* oi;

public:
	HematologistManipulator();
	virtual ~HematologistManipulator();

	void moveLiftUp();
	void moveLiftDown();

	void secondTierClawClosed();
	void secondTierClawOpen();
	void secondTierSolStop();

	void setLiftToPosition();
	void preSetHeight();
	void activateSecondTier(int target);
	void buttonIsPressed();
	
	HematologistManipulator(OperatorInterface* oi);
	void toggleBinHugger();
	void moveForklift(float power);

};


#endif
