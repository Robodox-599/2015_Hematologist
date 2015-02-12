#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

#include "HematologistMacros.h"

class HematologistManipulator
{
private:
	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	DoubleSolenoid* secondTierPiston;
	DoubleSolenoid* binHuggerPiston;
	DoubleSolenoid* forkliftPiston;

	Joystick* manipJoystick;

	Encoder* liftEncoder;

	Compressor* compressor;

	bool disableEncoders;


public:
	void openBinHugger();
	void openForklift();
	void openSecondTier();

	void resetEncoders();
	void toggleCompressor(bool start, bool stop);

	HematologistManipulator(Joystick* manipJoystick);
	~HematologistManipulator();

};

#endif
