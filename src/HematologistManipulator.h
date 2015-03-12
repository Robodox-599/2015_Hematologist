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

	Relay* longArmFlap1;
	Relay* longArmFlap2;

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
	bool flapsOpen;

	bool longArmOpen1;
	bool longArmOpen2;
	bool longArmOpen3;

	bool longArmClose1;
	bool longArmClose2;
	bool longArmClose3;

	bool automaticActivation;
	bool disableEncoders;

public:

	//Constructor
	HematologistManipulator(Joystick* manipJoystick);
	~HematologistManipulator();

	//Get Functions
	bool getSecondTierState();
	bool getForkliftState();
	HematologistAnalogLimitSwitch* getLimitSwitch(bool top);
	bool getCompressorOn();
	Talon* getManipTalon(bool right);
	Encoder* getLiftEncoder();
	DoubleSolenoid* getForkliftPiston();
	DoubleSolenoid* getSecondTierPiston();
	bool compressorIsOn();
	bool binHuggerIsOpen();
  	bool forkliftIsOpen();
  	bool secondTierIsOpen();
  	Relay* getLongArmFlap(int whichOne);
  	bool flapsIsOpen();

	//Functionality of Manip
	void resetEncoders();
	void moveLift(float speed);
	void activateCompressor(bool start);
	void controlCompressor(bool change);
  	void automaticallyActivate(bool activate);

  	void openPiston(bool forklift, bool open);
  	void closePiston(bool forklift, bool close);

  	void turnOnCompressor(bool start);
  	void turnOffCompressor(bool stop);

  	void openBinHugger(bool open);
  	void closeBinHugger(bool close);

  	void longArmOpenStep1(bool step1);
  	void longArmOpenStep2(bool step2);
  	void longArmOpenStep3(bool step3);

  	std::string warningFromLongArm();

  	void longArmMoveOut();

  	void longArmCloseStep1(bool step1);
	void longArmCloseStep2(bool step2);
	void longArmCloseStep3(bool step3);

	void longArmMoveIn();

	void automaticallyOpenTier();


};

#endif
