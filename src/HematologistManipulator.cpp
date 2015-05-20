#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator(HematologistOperatorInterface* oi)
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

	sequenceStarted	= false;
	sequenceStep	= 0;

	binSequenceStarted 	= false;
	binSequenceStep 	= 0;

	forkliftOpen = false;

	this->oi = oi;
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

void HematologistManipulator::openForklift(bool open)
{
	if(open){
		forkliftPiston->Set(DoubleSolenoid::kReverse);
		forkliftOpen = true;
	}
}

void HematologistManipulator::closeForklift(bool close)
{
	if (close){
		forkliftPiston->Set(DoubleSolenoid::kForward);
		forkliftOpen = false;
	}
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
		binHuggerPiston->Set(DoubleSolenoid::kForward);
}

void HematologistManipulator::closeBinHugger(bool close)
{
	if (close)
		binHuggerPiston->Set(DoubleSolenoid::kReverse);
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

void HematologistManipulator::autoSequence(float input)
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
	if (sequenceStep == 2)
	{
		sequenceStarted = false;
	}
	if (input > LIFT_DEADZONE || input < -LIFT_DEADZONE)
	{
		moveLift(input);
		sequenceStarted = false;
	}
}

void HematologistManipulator::controlLift(float input, bool startSequence, bool binStartSequence)
{

	oi->getDashboard()->PutBoolean("SequenceStarted", sequenceStarted);
	oi->getDashboard()->PutBoolean("Bin Sequence Started", binSequenceStarted);

	oi->getDashboard()->PutNumber("SequenceStep", sequenceStep);
	oi->getDashboard()->PutNumber("Bin Sequence Step", binSequenceStep);
	if (startSequence && !binSequenceStarted)
	{
		sequenceStarted = true;
	}else
	{
		if (binStartSequence && !sequenceStarted)
		{
			binSequenceStarted = true;
		}
	}
	if (sequenceStarted){
		autoSequence(input);
	}else
	{
		if (binSequenceStarted)
		{
			binAutoSequence(input);
		}else
		{
			moveLift(input);
			sequenceStep = 0;
			binSequenceStep = 0;
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

HematologistLimitSwitch* HematologistManipulator::getTopLimitSwitch()
{
	return topLimitSwitch;
}

HematologistLimitSwitch* HematologistManipulator::getBottomLimitSwitch()
{
	return bottomLimitSwitch;
}

bool HematologistManipulator::highEnough()
{
	if (getEncoderValue() > 3000 - LIFT_DEADZONE && getEncoderValue() < 3100 + LIFT_DEADZONE)
	{
		return true;
	}
	return false;
}

void HematologistManipulator::binAutoSequence(float input)
{
	if(binSequenceStep == 0)
	{
		openBinHugger(true);
		moveLift(0.8);
		if(topLimitSwitch->isPressed())
		{
			binSequenceStep++;
		}
	}
	if (binSequenceStep == 1)
	{
		moveLift(0);
		closeBinHugger(true);
		binSequenceStep++;
	}
	if (binSequenceStep == 2)
	{
		moveLift(-.8);
		if (bottomLimitSwitch->isPressed())
		{
			binSequenceStep++;
		}
	}
	if(binSequenceStep == 3)
	{
		binSequenceStarted = false;
	}
	if(input > DEADZONE || input < -DEADZONE){
		binSequenceStarted = false;
	}
}















































