#ifndef HEMATOLOGIST_MANIPULATOR_H
#define HEMATOLOGIST_MANIPULATOR_H

#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"
#include "HematologistLimitSwitch.h"

class HematologistManipulator
{
public:
	//constructor/destructor
	HematologistManipulator();
	~HematologistManipulator();

	//you would send in either a joystick->GetRawButton() or an actual value of true/false. 
	//the latter is used for autonomous
	//the names of the following should be self-explanatory
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

	//takes into account the limit switches/dedzone and moves the lift appropriately
	//put in a positive value to move up. neg to move down
	//either put in joystick->GetY()/GetX() or a value for autonomous
	void moveLift(float input);

	//the input here is joystick->GetY()/GetX(). The reason for this is so that
	//if the joystick moves too far up/down/to the side, the autosequence will 
	//see that and then stop the sequence
	void autoSequence(float input);

	//put in joystick->GetY()/GetX() for input
	//put in joystick->GetRawButton() for startSequence
	//you stop the sequence b moving the joystick
	void controlLift(float input, bool startSequence);

	//will reset the encoder value to zero
	//this should be caleld when the bottom limit switch is hit
	void resetEncoder();

	//returns the enoder value
	//this way, we don't have a function to return the Encoder and then calling encoder->Get()
	float getEncoderValue();

	//this will mvoe the intake rollers
	//put in joystick->GetRawButton(). For this robot, we use joystick->GetTrigger()
	//this way, we're not wasting a joystick axis but instead using a button. 
	//Also, we're not screwing with if it goes the mtoors rotate inward or not
	//keep in mind that the two motors must rotate in opposite direction
	void intakeWithRoller(bool intake);

	//self-explnatory
	//compressor is set to stop at 120 psi anyhow
	//this turning on/off is gen used b/c of the noise
	//send in joystick->GetRawButton()
	void turnOnCompressor(bool turnOn);
	void turnOffCompressor(bool turnOff);

	//returns the limit switches
	//we decided not to return if limitswitch->isPressed() to demonstrate the returning of objects
	HematologistLimitSwitch* getTopLimitSwitch();
	HematologistLimitSwitch* getBottomLimitSwitch();

	//this function was meant to indicate to the driver if he had gone far enough up with the tote
	//to bring the lift down safely
	//however, this function is never used 
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

	//variables that control the sequence. It will become clear hwo they work in the .cpp code
	bool sequenceStarted;
	int sequenceStep;

	bool forkliftOpen;
};

#endif
