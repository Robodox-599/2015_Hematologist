#include "HematologistManipulator.h"
#include "HematologistMacros.h"
#include "HematologistManiuplator.h"

HematologistManipulator::HematologistManipulator()
{
	//Motor-based manipulators
	leftLiftMotor = new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor = new Talon(RIGHT_LIFT_MOTOR_CHANNEL);
	leftForkliftMotor = new Talon(LEFT_FORKLIFT_MOTOR_CHANNEL);
	rightForkliftMotor = new Talon (RIGHT_FORKLIFT_MOTOR_CHANNEL);

	//Solenoids
	binHuggerSol = new DoubleSolenoid(BIN_HUGGER_SOL_CHANNEL_A, BIN_HUGGER_SOL_CHANNEL_B);
	secondTierSol = new DoubleSolenoid(SECOND_TIER_SOL_CHANNEL_A, SECOND_TIER_SOL_CHANNEL_B);

	//Encoders
	leftLiftEncoder = new Encoder(LEFT_LIFT_ENCODER_CHANNEL_A, LEFT_LIFT_ENCODER_CHANNEL_B, false, Encoder::EncodingType::k4X);
	rightLiftEncoder = new Encoder(RIGHT_LIFT_ENCODER_CHANNEL_A, RIGHT_LIFT_ENCODER_CHANNEL_B, false, Encoder::EncodingType::k4X);
	rightLiftEncoder->Encoder::SetMaxPeriod(1);
	rightLiftEncoder->Encoder::SetMinRate(10);
	rightLiftEncoder->Encoder::SetDistancePerPulse(5);
	rightLiftEncoder->Encoder::SetReverseDirection(true);
	rightLiftEncoder->Encoder::SetSamplesToAverage(7);
}


HematologistManipulator::~HematologistManipulator()
{
	delete leftLiftMotor;
	delete rightLiftMotor;
	delete leftForkliftMotor;
	delete rightForkliftMotor;
	delete binHuggerSol;
	delete secondTierSol;
	delete leftLiftEncoder;
	delete rightLiftEncoder;

	leftLiftMotor = NULL;
	rightLiftMotor = NULL;
	leftForkliftMotor = NULL;
	rightForkliftMotor = NULL;
	binHuggerSol = NULL;
	secondTierSol = NULL;
	leftLiftEncoder = NULL;
	rightLiftEncoder = NULL;
}

void HematologistManipulator::moveForklift(bool up, bool down, float power)
{
	if(up)
	{
		leftForkliftMotor->Set(power);
		rightForkliftMotor->Set(-power);
	}
	else
	{
		if(down)
		{
			leftForkliftMotor->Set(-power);
			rightForkliftMotor->Set(power);
		}
		else
		{
			leftForkliftMotor->Set(0);
			rightForkliftMotor->Set(0);
		}
	}
}

void HematologistManipulator::secondTierSolForward()
{
	secondTierSol->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::secondTierSolBackward()
{
	secondTierSol->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::secondTierSolStop()
{
	secondTierSol->Set(DoubleSolenoid::kOff);
}

void HematologistManipulator::activateSecondTier(int target)
{
	if(leftLiftEncoder->Get() < target && rightLiftEncoder->Get() < target)
	{
		secondTierSolForward();
	}
	else
	{
		if(leftLiftEncoder->Get() > target && rightLiftEncoder->Get() > target)
		{
			secondTierSolBackward();
		}
	}
}

void HematologistManipulator::manualLiftControl(bool up, bool down, float power)
{
	//moves lift up
	if(up)
	{
		leftLiftMotor->Set(power);
		rightLiftMotor->Set(power);
	}
	else
	{
		if(down)
		{
			leftLiftMotor->Set(-power);
			rightLiftMotor->Set(-power);
		}
		else
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
	}
}

void HematologistManipulator::setLiftToPosition(int target, float power)
{
	if(rightLiftEncoder->Get() < target && leftLiftEncoder->Get() < target)
	{
		leftLiftMotor->Set(power);
		rightLiftMotor->Set(power);
	}
	else
	{
		if(rightLiftEncoder->Get() < target + LIFTDEADZONE && rightLiftEncoder->Get() < target + LIFTDEADZONE)
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
		else
		{
			leftLiftMotor->Set(-power);
			rightLiftMotor->Set(-power);
		}
	}
}

void HematologistManipulator::preSetHeight(bool low, bool mid, bool high, float power)
{
	if(low)
	{
		setLiftToPosition(PRE_SET_LOW, power);
	}
	if(mid)
	{
		setLiftToPosition(PRE_SET_MID, power);
	}
	if(high)
	{
		setLiftToPosition(PRE_SET_HIGH, power);
	}
}

void HematologistManipulator::toggleBinHugger(bool on, bool off)
{
	if (on)
	{ 
		binHuggerSol->Set(DoubleSolenoid::kReverse);
	}
	else if (off)
	{
		binHuggerSol->Set(DoubleSolenoid::kForward);
	}
}

