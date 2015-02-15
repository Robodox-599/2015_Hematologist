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
	DoubleSolenoid* longArmPiston;

	Joystick* manipJoystick;

	Encoder* liftEncoder;

	Compressor* compressor;

	HematologistAnalogLimitSwitch* topLimitSwitch;
	HematologistAnalogLimitSwitch* bottomLimitSwitch;

	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	bool compressorOn;
	bool secondTierOpen;
	bool forkliftOpen;
	bool binHuggerOpen;

	bool longArmOpen1;
	bool longArmOpen2;
	bool longArmOpen3;

	bool longArmClose1;
	bool longArmClose2;
	bool longArmClose3;

	bool automaticActivation;
	bool disableEncoders;

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

  	bool compressorIsOn();

  	void openBinHugger(bool open);
  	void closeBinHugger(bool close);

  	bool binHuggerIsOpen();
  	bool forkliftIsOpen();
  	bool secondTierIsOpen();

  	void longArmOpenStep1(bool step1);
  	void longArmOpenStep2(bool step2);
  	void longArmOpenStep3(bool step3);

  	std::string warningFromLongArm();

  	void longArmMoveOut();

};

#endif
