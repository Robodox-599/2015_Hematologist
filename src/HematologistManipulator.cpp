#include "HematologistManipulator.h"
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator(Joystick* manipJoystick)
{
	secondTierPiston = new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A, SECOND_TIER_PISTON_CHANNEL_B);
	binHuggerPiston = new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A, BIN_HUGGER_PISTON_CHANNEL_B);
	forkliftPiston = new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A, FORKLIFT_PISTON_CHANNEL_B);

	secondTierPiston->Set(DoubleSolenoid::kReverse);
	forkliftPiston->Set(DoubleSolenoid::kReverse);

	leftLiftMotor = new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor = new Talon(RIGHT_LIFT_MOTOR_CHANNEL);

	liftEncoder = new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B);
	compressor = new Compressor(0);

	toggleCompressor(true, false);

	this->manipJoystick = manipJoystick;

	topLimitSwitch = new HematologistAnalogLimitSwitch(TOP_LIMIT_SWITCH_CHANNEL);
	bottomLimitSwitch = new HematologistAnalogLimitSwitch(BOTTOM_LIMIT_SWITCH_CHANNEL);

	disableEncoders = false;

	forkliftOpen = false;
	secondTierOpen = false;

	automaticActivation = false;
}

HematologistManipulator::~HematologistManipulator()
{
	delete secondTierPiston;
	delete binHuggerPiston;
	delete forkliftPiston;
	delete manipJoystick;
	delete topLimitSwitch;
	delete bottomLimitSwitch;
	delete 	compressor;

	secondTierPiston = NULL;
	binHuggerPiston = NULL;
	forkliftPiston = NULL;
	manipJoystick = NULL;
	topLimitSwitch= NULL;
	bottomLimitSwitch = NULL;
	compressor = NULL;
}

void HematologistManipulator::moveLift(float speed)
{
	if (topLimitSwitch->limitSwitchIsPressed())
	{
		if (speed > DEADZONE)
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}else
		{
			if (speed < -DEADZONE)
			{
				leftLiftMotor->Set(speed);
				rightLiftMotor->Set(speed);
			}else
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}
		}
	}else
	{
		if (bottomLimitSwitch->limitSwitchIsPressed())
		{
			liftEncoder->Reset();
			if (speed < -DEADZONE)
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}else
			{
				if (speed > DEADZONE)
				{
					leftLiftMotor->Set(speed);
					rightLiftMotor->Set(speed);
				}else
				{
					leftLiftMotor->Set(0);
					rightLiftMotor->Set(0);
				}
			}
		}else
		{
			if (speed > DEADZONE || speed < -DEADZONE)
			{
				leftLiftMotor->Set(speed);
				rightLiftMotor->Set(speed);
			}else
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}
		}
	}
}

void HematologistManipulator::openBinHugger()
{
	if (manipJoystick->GetRawButton(IGNORE_ENCODERS_BUTTON))
	{
		disableEncoders = !disableEncoders;
	}
	if (disableEncoders)
	{
		if(manipJoystick->GetRawButton(BIN_HUGGER_OPEN_BUTTON))
		{
			binHuggerPiston->Set(DoubleSolenoid::kForward);
		}
		else
		{
			if(manipJoystick->GetRawButton(BIN_HUGGER_CLOSE_BUTTON))
			{
				binHuggerPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				binHuggerPiston->Set(DoubleSolenoid::kOff);
			}
		}
	}
	else
	{
		/*
		if(liftEncoder->Get() < LIFT_DEADZONE && liftEncoder->Get() > -LIFT_DEADZONE)
		{
			binHuggerPiston->Set(DoubleSolenoid::kForward);
		}
		else
		{
			if(liftEncoder->Get() < -LIFT_DEADZONE || liftEncoder->Get() > LIFT_DEADZONE)
			{
				binHuggerPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				binHuggerPiston->Set(DoubleSolenoid::kOff);
			}
		}
		*/
	}
}



void HematologistManipulator::openSecondTier()
{
	if (manipJoystick->GetRawButton(IGNORE_ENCODERS_BUTTON))
	{
		disableEncoders = !disableEncoders;
	}
	if (disableEncoders)
	{
		if(manipJoystick->GetRawButton(SECOND_TIER_OPEN_BUTTON))
		{
			secondTierPiston->Set(DoubleSolenoid::kForward);
		}
		else
		{
			if(manipJoystick->GetRawButton(SECOND_TIER_CLOSE_BUTTON))
			{
				secondTierPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				secondTierPiston->Set(DoubleSolenoid::kOff);
			}
		}
	}
	else
	{	
		/*
		if(liftEncoder->Get() < LIFT_DEADZONE && liftEncoder->Get() > -LIFT_DEADZONE)
		{
			secondTierPiston->Set(DoubleSolenoid::kForward);
		}
		else
		{
			if(liftEncoder->Get() < -LIFT_DEADZONE || liftEncoder->Get() > LIFT_DEADZONE)
			{
			secondTierPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				secondTierPiston->Set(DoubleSolenoid::kOff);
			}
		}
		*/
	}
}


void HematologistManipulator::openForklift()
{
	if (IGNORE_ENCODERS_BUTTON)
		disableEncoders = !disableEncoders;

	if (disableEncoders)
	{
		if(manipJoystick->GetRawButton(FORKLIFT_OPEN_BUTTON))
		{
			forkliftPiston->Set(DoubleSolenoid::kForward);
		}
		else
		{
			if(manipJoystick->GetRawButton(FORKLIFT_CLOSE_BUTTON))
			{
				forkliftPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				forkliftPiston->Set(DoubleSolenoid::kOff);
			}
		}
	}
	else
	{	
		/*
		if(liftEncoder->Get() < LIFT_DEADZONE && liftEncoder->Get() > -LIFT_DEADZONE)
		{
			forkliftPiston->Set(DoubleSolenoid::kForward);
		}
		else
		{
			if(liftEncoder->Get() < LIFT_DEADZONE || liftEncoder->Get() > LIFT_DEADZONE)
			{
				forkliftPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				forkliftPiston->Set(DoubleSolenoid::kOff);
			}
		}
		*/
	}
}


void HematologistManipulator::resetEncoders()
{
	liftEncoder->Reset();
}

void HematologistManipulator::toggleCompressor(bool start, bool stop)
{
	if (start)
		compressor->SetClosedLoopControl(start);
	if (stop)
		compressor->SetClosedLoopControl(stop);
}

HematologistAnalogLimitSwitch* HematologistManipulator::getLimitSwitch(bool top)
{
	if (top)
		return topLimitSwitch;
	else
		return bottomLimitSwitch;
}

void HematologistManipulator::activateCompressor(bool start)
{
	if (start)
		compressor->Start();
	else
		compressor->Stop();
}

void HematologistManipulator::controlCompressor(bool change)
{
	if (change)
		compressorOn = !compressorOn;
	activateCompressor(compressorOn);
}

bool HematologistManipulator::getCompressorOn()
{
	return compressorOn;
}

Talon* HematologistManipulator::getManipTalon(bool right)
{
  if (right)
    return rightLiftMotor;
  else
    return leftLiftMotor;
}

Encoder* HematologistManipulator::getLiftEncoder()
{
  return liftEncoder;
}

void HematologistManipulator::activateForklift(bool change)
{
	if (change)
	{
		if (forkliftPiston->Get() == DoubleSolenoid::kReverse)
		{
			forkliftPiston->Set(DoubleSolenoid::kForward);
			forkliftOpen = false;
		}else
		{
			forkliftPiston->Set(DoubleSolenoid::kForward);
			forkliftOpen = true;
		}
	}
}

void HematologistManipulator::activateSecondTier(bool change)
{
	if (change)
	{
		if (secondTierPiston->Get() == DoubleSolenoid::kReverse)
		{
			secondTierPiston->Set(DoubleSolenoid::kForward);
			secondTierOpen = false;
		}else
		{
			secondTierPiston->Set(DoubleSolenoid::kReverse);
			secondTierOpen = true;
		}
	}
}

bool HematologistManipulator::getSecondTierState()
{
	return secondTierOpen;
}

bool HematologistManipulator::getForkliftState()
{
	return forkliftOpen;
}

void HematologistManipulator::automaticallyActivate(bool activate)
{
	//wrong number
	if (activate)
		automaticActivation = !automaticActivation;
	if (automaticActivation)
	{
		if (liftEncoder->Get() < 100 - LIFT_DEADZONE)
		{
			leftLiftMotor->Set(.3);
			rightLiftMotor->Set(.3);
		}
		if (liftEncoder->Get() > 100 - LIFT_DEADZONE && liftEncoder->Get() < 100 + LIFT_DEADZONE)
		{
			secondTierPiston->Set(DoubleSolenoid::kForward);
		}
		if (liftEncoder->Get() > 200 - LIFT_DEADZONE && liftEncoder->Get() < 200 - LIFT_DEADZONE)
		{
			secondTierPiston->Set(DoubleSolenoid::kReverse);
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
			automaticActivation = false;
		}
	}else
		return;
}

DoubleSolenoid* HematologistManipulator::getSecondTierPiston()
{
	return secondTierPiston;
}

DoubleSolenoid* HematologistManipulator::getForkliftPiston()
{
	return forkliftPiston;
}

void HematologistManipulator::openPiston(bool forklift, bool open)
{
	if (open)
	{
		if (forklift)
			forkliftPiston->Set(DoubleSolenoid::kReverse);
		else
			secondTierPiston->Set(DoubleSolenoid::kReverse);
	}else
		return;
}

void HematologistManipulator::closePiston(bool forklift, bool open)
{
	if (open)
	{
		if (forklift)
			forkliftPiston->Set(DoubleSolenoid::kForward);
		else
			secondTierPiston->Set(DoubleSolenoid::kForward);
	}else
		return;
}

void HematologistManipulator::turnOffCompressor(bool stop)
{
	if (stop)
	{
		compressor->Stop();
		compressorOn = false;
	}
	return;
}

void HematologistManipulator::turnOnCompressor(bool start)
{
	if (start){
		compressor->Start();
		compressorOn = true;
	}
	return;
}

bool HematologistManipulator::compressorIsOn()
{
	return compressorOn;
}

