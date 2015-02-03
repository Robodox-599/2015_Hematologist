#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
{
	//Motor-based manipulators
	leftLiftMotor = new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor = new Talon(RIGHT_LIFT_MOTOR_CHANNEL);

	//Solenoids
	binHuggerSol = new DoubleSolenoid(BIN_HUGGER_SOL_CHANNEL_A, BIN_HUGGER_SOL_CHANNEL_B);
	secondTierSol = new DoubleSolenoid(SECOND_TIER_SOL_CHANNEL_A, SECOND_TIER_SOL_CHANNEL_B);
	forkliftSol = new DoubleSolenoid(FORKLIFT_SOL_CHANNEL_A, FORKLIFT_SOL_CHANNEL_B);

	//Encoders
	liftEncoder = new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B, false, Encoder::EncodingType::k4X);
	liftEncoder->Encoder::SetMaxPeriod(1);
	liftEncoder->Encoder::SetMinRate(10);
	liftEncoder->Encoder::SetDistancePerPulse(5);
	liftEncoder->Encoder::SetReverseDirection(true);
	liftEncoder->Encoder::SetSamplesToAverage(7);
}


HematologistManipulator::~HematologistManipulator()
{
	delete leftLiftMotor;
	delete rightLiftMotor;
	delete binHuggerSol;
	delete secondTierSol;
	delete forkliftSol;
	delete liftEncoder;

	leftLiftMotor = NULL;
	rightLiftMotor = NULL;
	binHuggerSol = NULL;
	secondTierSol = NULL;
	forkliftSol = NULL;
	liftEncoder = NULL;
}

void HematologistManipulator::setBinHuggerSol(int input)
{
	if(input == 0)
	{
		binHuggerSol->Set(DoubleSolenoid::kForward);
	}
	else
	{
		if(input == 1)
		{
			binHuggerSol->Set(DoubleSolenoid::kReverse);
		}
		else
		{
			binHuggerSol->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::setSecondTierSol(int input)
{
	if(input == 0)
	{
		secondTierSol->Set(DoubleSolenoid::kReverse);
	}
	else
	{
		if(input == 1)
		{
			secondTierSol->Set(DoubleSolenoid::kForward);
		}
		else
		{
			secondTierSol->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::setForkliftSol(int input)
{
	if(input == 0)
	{
		forkliftSol->Set(DoubleSolenoid::kReverse);
	}
	else
	{
		if(input == 1)
		{
			forkliftSol->Set(DoubleSolenoid::kForward);
		}
		else
		{
			forkliftSol->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::activateSecondTier(int target)
{
	if(liftEncoder->Get() > target && liftEncoder->Get() < target + LIFT_DEADZONE)
	{
		setSecondTierSol(0);
	}
	else
	{
		setSecondTierSol(1);
	}
}

void HematologistManipulator::activateBinHugger(bool open, bool close)
{
	if(open)
	{
		setBinHuggerSol(1);
	}
	else if(close)
	{
		setBinHuggerSol(0);
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
	if(liftEncoder->Get() < target)
	{
		leftLiftMotor->Set(power);
		rightLiftMotor->Set(power);
	}
	else
	{
		if(liftEncoder->Get() < target + LIFT_DEADZONE)
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

