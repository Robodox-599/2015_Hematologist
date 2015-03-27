#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
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
	compressor->SetClosedLoopControl(true);

	topLimitSwitch 		= new HematologistLimitSwitch(TOP_LIMIT_SWITCH_CHANNEL);
	bottomLimitSwitch 	= new HematologistLimitSwitch(BOTTOM_LIMIT_SWITCH_CHANNEL);
}

HematologistManipulator::~HematologistManipulator()
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

void HematologistManipulator::openForkLift(bool open)
{
	if(open)
		forkLiftPiston->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::closeForkLift(bool close)
{
	if (close)
		forkLiftPiston->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::openSecondTier(bool open)
{
	if (open)
		secondTierPiston->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::closeSecondTier(bool close)
{
	if (close)
		secondTierPiston->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::openBinHugger(bool open)
{
	if (open)
		binHuggerPiston->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::closeBinHugger(bool close)
{
	if (close)
		binHuggerPiston->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::openFlaps(bool open)
{
	if (open)
	{
		flapOpenRelay->Set(Relay::kForward);
		flapCloseRelay->Set(Relay::kOff);
	}
}

void HematologistManipulator::closeFlaps(bool close)
{
	if (close)
	{
		flapOpenRelay->Set(Relay::kOff);
		flapCloseRelay->Set(Relay::kForward);
	}
}

void HematologistManipulator::extendLongArm(bool extend)
{
	if (extend)
		longArmPiston->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::retractLongArm(bool retract)
{
	if (retract)
		longArmPiston->Set(DoubleSolenoid::kReverse);
}

void HematologistManipulator::moveLift(float input)
{
	//different deadzone used here b/c drivers want different deadzone values
	if (topLimitSwitch->isPressed())
	{
		if (input < -LIFT_DEADZONE)
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
			if (input > LIFT_DEADZONE)
			{
				leftLiftMotor->Set(input);
				rightLiftMotor->Set(input);
			}else
			{
				leftLiftMotor->Set(0):
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

void HematologistManipulator::resetEncoder()
{
	liftEncoder->Reset();
}

float HematologistManipulator::getEncoderValue()
{
	return liftEncoder->Get();
}

void HematologistManipulator::intakeWithRoller(bool intake)
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

void HematologistManipulator::turnOnCompressor(bool turnOn)
{
	if (turnOn)
		compressor->Start();
}

void HematologistManipulator::turnOffCompressor(bool turnOff)
{
	if (turnOff)
		compressor->Stop();
}


















































