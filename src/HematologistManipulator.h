#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "HematologistMacros.h"
#include "HematologistAnalogLimitSwitch.h"

class HematologistManipulator
{
private:
	DoubleSolenoid* secondTierPiston;
	DoubleSolenoid* binHuggerPiston;
	DoubleSolenoid* forkliftPiston;

	Joystick* manipJoystick;

	Encoder* liftEncoder;

	Compressor* compressor;

	bool disableEncoders;

	HematologistAnalogLimitSwitch* limitSwitch;

	bool compressorOn;


public:
	void openBinHugger();
	void openForklift();
	void openSecondTier();

	bool limitSwitchIsPressed();

	void resetEncoders();
	void toggleCompressor(bool start, bool stop);

	HematologistManipulator(Joystick* manipJoystick);
	~HematologistManipulator();

	void moveLift(float speed);
	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	HematologistAnalogLimitSwitch* getLimitSwitch();

	void activateCompressor(bool start);
};

#endif
