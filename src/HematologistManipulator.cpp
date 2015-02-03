#include "HematologistManipulator.h"

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
	liftEncoder = new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B, false, Encoder::EncodingType::k4X);
	forkliftEncoder = new Encoder(FORKLIFT_ENCODER_CHANNEL_A, FORKLIFT_ENCODER_CHANNEL_B, false, Encoder::EncodingType::k4X);
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
	delete leftForkliftMotor;
	delete rightForkliftMotor;
	delete binHuggerSol;
	delete secondTierSol;
	delete liftEncoder;
	delete forkliftEncoder;

	leftLiftMotor = NULL;
	rightLiftMotor = NULL;
	leftForkliftMotor = NULL;
	rightForkliftMotor = NULL;
	binHuggerSol = NULL;
	secondTierSol = NULL;
	liftEncoder = NULL;
	forkliftEncoder = NULL;
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

void HematologistManipulator::openSecondTierSol()
{
	secondTierSol->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::closeSecondTierSol()
{
	secondTierSol->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::stopSecondTierSol()
{
	secondTierSol->Set(DoubleSolenoid::kOff);
}

void HematologistManipulator::activateSecondTier(int target)
{
	if(liftEncoder->Get() > target && liftEncoder->Get() < target + LIFT_DEADZONE)
	{
		closeSecondTierSol();
	}
	else
	{
		openSecondTierSol();
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

