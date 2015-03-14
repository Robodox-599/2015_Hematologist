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

	Relay* longArmFlapOpen;
	Relay* longArmFlapClose;

	Joystick* manipJoystick;

	Encoder* liftEncoder;

	Compressor* compressor;

	HematologistAnalogLimitSwitch* topLimitSwitch;
	HematologistAnalogLimitSwitch* bottomLimitSwitch;

	Talon* leftLiftMotor;
	Talon* rightLiftMotor;

	Talon* leftRollerMotor;
	Talon* rightRollerMotor;

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

	int autoRollerStep;

	bool autoButtonPressed;
	bool autoSequenceFinished;

	Timer *timer;
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
  	Relay* getLongArmFlap(bool open);
  	bool flapsIsOpen();

	//Functionality of Manip
	void resetEncoders();
	void moveLift(float speed);
  	void automaticallyActivate(bool activate);

  	void openPiston(bool forklift, bool open);
  	void closePiston(bool forklift, bool close);

  	void turnOnCompressor(bool start);
  	void turnOffCompressor(bool stop);

  	void openBinHugger(bool open);
  	void closeBinHugger(bool close);

  	void toggleRollers(bool toggle, float direction); //direction is if throttle is + move forward if - move backward

  	void longArmMoveOut(bool move, bool confirm);
  	void longArmMoveIn(bool move, bool confirm);

	void automaticallyOpenTier();

	void openFlaps(bool open);
	void closeFlaps(bool close);

	void autoRollers();

	void autoForkLift(bool start);
};
#endif
