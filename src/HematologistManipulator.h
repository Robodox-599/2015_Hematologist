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

	bool secondTierOpen;
	bool forkliftOpen;

	bool automaticActivation;

public:
	HematologistManipulator(Joystick* manipJoystick);
	~HematologistManipulator();

	void openBinHugger();
	void openForklift();
	void openSecondTier();

	void activateForklift(bool open);
	void activateSecondTier(bool open);

	bool getSecondTierState();
	bool getForkliftState();

	void resetEncoders();
	void toggleCompressor(bool start, bool stop);

	void moveLift(float speed);

	HematologistAnalogLimitSwitch* getLimitSwitch(bool top);

	void activateCompressor(bool start);

	void controlCompressor(bool change);

	bool getCompressorOn();

	Talon* getManipTalon(bool right);
	Encoder* getLiftEncoder();

  	void automaticallyActivate(bool activate);

  	DoubleSolenoid* getForkliftPiston();
  	DoubleSolenoid* getSecondTierPiston();

  	void openPiston(bool forklift, bool open);
  	void closePiston(bool forklift, bool close);

  	void turnOnCompressor(bool start);
  	void turnOffCompressor(bool stop);



};

#endif
