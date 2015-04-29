#ifndef HEMATOLOGIST_MANIPULATOR_H
#define HEMATOLOGIST_MANIPULATOR_H

#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"
#include "HematologistLimitSwitch.h"

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

<<<<<<< HEAD
	void moveLift(float input);
	void autoSequence(float input);
	void controlLift(float input, bool startSequence);
=======

	bool longArmOpen1;
	bool longArmOpen2;
	bool longArmOpen3;
>>>>>>> f88f0b8b7432cdb8b1e38f4b3e1649fd618c64ff

	void resetEncoder();
	float getEncoderValue();

	void intakeWithRoller(bool intake);

	void turnOnCompressor(bool turnOn);
	void turnOffCompressor(bool turnOff);

	HematologistLimitSwitch* getTopLimitSwitch();
	HematologistLimitSwitch* getBottomLimitSwitch();

	bool highEnough();


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

	bool forkliftOpen;
};

#endif
