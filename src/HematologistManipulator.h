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

	HematologistAnalogLimitSwitch* topLimitSwitch;
	HematologistAnalogLimitSwitch* bottomLimitSwitch;

	bool compressorOn;

	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

public:
	HematologistManipulator(Joystick* manipJoystick);
	~HematologistManipulator();

	void openBinHugger();
	void openForklift();
	void openSecondTier();

	void resetEncoders();
	void toggleCompressor(bool start, bool stop);

	void moveLift(float speed);

	HematologistAnalogLimitSwitch* getLimitSwitch(bool top);

	HematologistAnalogLimitSwitch* topLimitSwitch;
	HematologistAnalogLimitSwitch* bottomLimitSwitch;
	
	void activateCompressor(bool start);

	void controlCompressor(bool change);

	bool getCompressorOn();

  Talon* getManipTalon(bool right);
  Encoder* getLiftEncoder();

};

#endif
