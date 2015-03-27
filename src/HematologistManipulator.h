#ifndef HEMATOLOGIST_MANIPULATOR_H
#define HEMATOLOGIST_MANIPULATOR_H

#include "HematologistMacros.h"

class HematologistManipulator
{
public:
	HematologistManipulator();
	~HematologistManipulator();

	void openForklift(bool open);
	void closeForklift(bool close);

	void openSecondTier(bool open);
	void closeSecondTier(bool close);

	void openBinHugger(bool open);
	void closeBinHugger(bool close);

	void openFlaps(bool open);
	void closeFlaps(bool close);

	void extendLongArm(bool extend);
	void retractLongArm(bool retract);

	void moveLift(float input);
	void autoSequence(bool start);
	void controlLift(float input, bool startSequence);

	void resetEncoder();
	float getEncoderValue();

	void intakeWithRoller(bool intake);

	void turnOnCompressor(bool turnOn);
	void turnOffCompressor(bool turnOff);


private:
	DoubleSolenoid* forkliftPiston;	
	DoubleSolenoid* secondTierPiston;
	DoubleSolenoid* binHuggerPiston;
	DoubleSolenoid* longArmPiston;

	Relay* flapOpenRelay;
	Relay* flapCloseRelay;

	Encoder* liftEncoder;

	Compressor* compressor;

	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	Talon* leftRollerMotor;
	Talon* rightRollerMotor;

	HematologistLimitSwitch* topLimitSwitch;
	HematologistLimitSwitch* bottomLimitSwitch;

	bool sequenceStarted;
	int sequenceStep;

};

#endif