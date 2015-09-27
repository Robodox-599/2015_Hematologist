#include "Manipulator.h"

Manipulator::Manipulator()
{
	forkliftPiston 		= new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A, FORKLIFT_PISTON_CHANNEL_B);
	secondTierPiston	= new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A, SECOND_TIER_PISTON_CHANNEL_B);
	binHuggerPiston		= new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A, BIN_HUGGER_PISTON_CHANNEL_B);
	longArmPiston		= new DoubleSolenoid(LONG_ARM_PISTON_CHANNEL_A, LONG_ARM_PISTON_CHANNEL_B);

	flapOpenRelay		= new Relay(FLAP_OPEN_RELAY_CHANNEL, Relay::kForwardOnly);
	flapCloseRelay		= new Relay(FLAP_CLOSE_RELAY_CHANNEL, Relay::kForwardOnly);

	liftEncoder 		= new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B);

	leftLiftMotor		= new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor		= new Talon(RIGHT_LIFT_MOTOR_CHANNEL);

	leftRollerMotor		= new Talon(LEFT_ROLLER_MOTOR_CHANNEL);
	rightRollerMotor	= new Talon(RIGHT_ROLLER_MOTOR_CHANNEL);

	compressor 			= new Compressor(COMPRESSOR_CHANNEL);
	compressor->SetClosedLoopControl(true);							//ensures that the compressor stops after 120psi
																	//this is always needed!!!!!!!

	topLimitSwitch 		= new HematologistLimitSwitch(TOP_LIMIT_SWITCH_CHANNEL);
	bottomLimitSwitch 	= new HematologistLimitSwitch(BOTTOM_LIMIT_SWITCH_CHANNEL);

	sequenceStarted	= false;
	sequenceStep	= 0;

	forkliftOpen = false;
}

Manipulator::~Manipulator()
{
	delete forkliftPiston;
	delete secondTierPiston;
	delete binHuggerPiston;
	delete longArmPiston;
	delete flapOpenRelay;
	delete flapCloseRelay;
	delete liftEncoder;
	delete leftLiftMotor;
	delete rightLiftMotor;
	delete leftRollerMotor;
	delete rightRollerMotor;
	delete compressor;
	delete topLimitSwitch;
	delete bottomLimitSwitch;

	forkliftPiston= NULL;
	secondTierPiston= NULL;
	binHuggerPiston= NULL;
	longArmPiston= NULL;
	flapOpenRelay= NULL;
	flapCloseRelay= NULL;
	liftEncoder= NULL;
	leftLiftMotor= NULL;
	rightLiftMotor= NULL;
	leftRollerMotor= NULL;
	rightRollerMotor= NULL;
	compressor= NULL;
	topLimitSwitch= NULL;
	bottomLimitSwitch= NULL;
}

/*
	all of these open/closeSomething are all the same. 
	For teleop, put in joystick->GetRawButton()
	for auto, put in true
	the reason why I don't toggle (use one button to swtich between open/close) is that toggling doens't really work
	If in the future it does, I welcome you to do so. However, there are other problems.
	For one, the driver needs to know that the button will do one thing. If we toggle, he has to keep track of if said thing
	is open or not. this way, one button will open it no matter what and will close it no matter what. 
	It's just generally easier

	Finally, keep in mind that kForward ≠ open. OpenForklift is a perfect example as kReverse means to open
	This is why we have these functions, so you don't have to remember if one is reversed or not. 
	We found out which does what by experimentation
*/

void Manipulator::openForklift(bool open)
{
	if(open){
		forkliftPiston->Set(DoubleSolenoid::kReverse);
		forkliftOpen = true;
	}
}

void Manipulator::closeForklift(bool close)
{
	if (close){
		forkliftPiston->Set(DoubleSolenoid::kForward);
		forkliftOpen = false;
	}
}

void Manipulator::openSecondTier(bool open)
{
	if (open)
		secondTierPiston->Set(DoubleSolenoid::kForward);
}

void Manipulator::closeSecondTier(bool close)
{
	if (close)
		secondTierPiston->Set(DoubleSolenoid::kReverse);
}

void Manipulator::openBinHugger(bool open)
{
	if (open)
		binHuggerPiston->Set(DoubleSolenoid::kForward);
}

void Manipulator::closeBinHugger(bool close)
{
	if (close)
		binHuggerPiston->Set(DoubleSolenoid::kReverse);
}

/*
we ran out of space for solenoids so we had to use relays to activate the DoubleSolenoid
relays are pretty simple to understand so think of them as a switch. when a relay is activated, current flows and so the pison is activated
because each relay goes to activate the solenoid differently (one tells it to DoubleSolenoid::kForward, other DoubleSoleonid::kReverse)
one must be turned off
I'm fairly certain that the relays we used are Normally Open relays but you might want to check back with electronics about that. 
If relays still confuse you, talk to them.
*/
void Manipulator::openFlaps(bool open)
{
	if (open)
	{
		flapOpenRelay->Set(Relay::kOff);			//essentially tells the solenoid to set it to DoubleSolenoid::kForward
		flapCloseRelay->Set(Relay::kForward);				//stops giving a command so the solenoid doesn't bother with it
	}
}

void Manipulator::closeFlaps(bool close)
{
	if (close)
	{
		flapOpenRelay->Set(Relay::kForward);
		flapCloseRelay->Set(Relay::kOff);
	}
}

void Manipulator::extendLongArm(bool extend)
{
	if (extend)
		longArmPiston->Set(DoubleSolenoid::kForward);
}

void Manipulator::retractLongArm(bool retract)
{
	if (retract)
		longArmPiston->Set(DoubleSolenoid::kReverse);
}

void Manipulator::moveLift(float input)
{
	//different deadzone used here b/c drivers want different deadzone values
	if (topLimitSwitch->isPressed())
	{
		if (input < -LIFT_DEADZONE)			//lift only moves if I tell it to go down
		{
			leftLiftMotor->Set(input);
			rightLiftMotor->Set(input);
		}else
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
	}
	else
	{
		if (bottomLimitSwitch->isPressed())
		{
			resetEncoder();
			if (input > LIFT_DEADZONE)		//lift only moves if I tell it to go up
			{
				leftLiftMotor->Set(input);
				rightLiftMotor->Set(input);
			}else
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}
		}else
		{
			//neither button pressed, act as if they don't exist
			if (input > LIFT_DEADZONE || input < -LIFT_DEADZONE)
			{
				leftLiftMotor->Set(input);
				rightLiftMotor->Set(input);
			}else
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}
		}
	}
}

/*
The assumption here is that the lift is all the way down and that the lift is hitting the limit switch
If the driver screws that up, that's his fault. 
This sequence is a good example of even though your program should be user friendly (and idiot proof for the drivers)
you can still give them instructions on what they can and cannot do
just make sure the instructions are easy to follow
*/
//the input should be the value of the liftJoystick
void Manipulator::autoSequence(float input)
{
	if(sequenceStep == 0)
	{
		moveLift(1);
		if(getEncoderValue() > 3275 - ENCODER_DEADZONE)
		{
			sequenceStep++;
		}
	}
	if(sequenceStep == 1)
	{
	 	moveLift(-.6);
	 	if (getEncoderValue() < 2500)
	 	{
	 		openForklift(true);
	 	}
	 	if(getEncoderValue() >= 0 && getEncoderValue() < 20)
	 	{
	 		sequenceStep++;
	 		moveLift(0);
	 	}
	}
	if (input > LIFT_DEADZONE || input < -LIFT_DEADZONE)
	{
		moveLift(0);
		sequenceStarted = false;					//you have to make this false so that we don't keep looping		
	}
}

//because the sequence didn't work on the field (it actually worked well in the pit)
//we just took it out of code
//However, the code with the sequence is put in between the #if 0 and #end if. 
//If you want to use that code, comment out the moveLift(input) and turn the 0 into a 1
/*
	the input should be the joystick->GetY() and the startSequence a ->GetRawButton()
*/
void Manipulator::controlLift(float input, bool startSequence)
{
	moveLift(input);
#if 0
	if (startSequence)
	{
		sequenceStarted = true;
		sequenceStep = 0;			//sequenceStep increases during the sequence so if we didn't do this, sequenceStep wouldn't equal 0 at the beginning
									//so the sequence would never start
	}
	if (sequenceStarted)
	{
		autoSequence(input);
	}else
	{
		moveLift(input);
	}
#endif
}

void Manipulator::resetEncoder()
{
	liftEncoder->Reset();
}

float Manipulator::getEncoderValue()
{
	return liftEncoder->Get();
}

/*
	the intake should be ->GetRawButton()
*/
void Manipulator::intakeWithRoller(bool intake)
{
	if (intake)
	{
		leftRollerMotor->Set(1);
		rightRollerMotor->Set(1);
	}else
	{
		leftRollerMotor->Set(0);
		rightRollerMotor->Set(0);
	}
}

/*
another ->GetRawButton()
these functions do not affect the fact that the compressor will turn off whenever psi = 120
if psi = 120 and you turn on the compressor, nothing will happen
however, if you turn it off and the psi < 120, the compressor will not automatically turn on as it would if it was on
*/
void Manipulator::turnOnCompressor(bool turnOn)
{
	if (turnOn)
		compressor->Start();
}

void Manipulator::turnOffCompressor(bool turnOff)
{
	if (turnOff)
		compressor->Stop();
}

HematologistLimitSwitch* Manipulator::getTopLimitSwitch()
{
	return topLimitSwitch;
}

HematologistLimitSwitch* Manipulator::getBottomLimitSwitch()
{
	return bottomLimitSwitch;
}

/*
intended to help the driver know when he had moved high enough with the tote to have passed the second tier
but it was never put in and was never used so...
*/
bool Manipulator::highEnough()
{
	if (getEncoderValue() > 3000 - LIFT_DEADZONE && getEncoderValue() < 3100 + LIFT_DEADZONE)
	{
		return true;
	}
	return false;
}

















































