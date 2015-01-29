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
	Encoder* leftLiftEncoder;
	Encoder* rightLiftEncoder;
	Joystick* manipulatorJoystick;
	double liftHeight;
	
	DoubleSolenoid* solenoid;

	Talon* rightForkliftMotor;
	Talon* leftForkliftMotor; 

	OperatorInterface* oi;
public:
	HematologistManipulator();
	virtual ~HematologistManipulator();

	void moveLiftUp();
	void moveLiftDown();

	void secondTierSolForward();
	void secondTierSolBackward();
	void secondTierSolStop();

	void setLiftToPosition(int target);
	void preSetHeight();
	void activateSecondTier(int target);
	
	HematologistManipulator(OperatorInterface* oi);
	void toggleBinHugger();
	void moveForklift(float power);

};


#endif
