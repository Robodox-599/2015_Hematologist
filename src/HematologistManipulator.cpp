#include "HematologistManipulator.h"
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator(Joystick* manipJoystick)
{
	secondTierPiston = new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A, SECOND_TIER_PISTON_CHANNEL_B);
	binHuggerPiston = new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A, BIN_HUGGER_PISTON_CHANNEL_B);
	forkliftPiston = new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A, FORKLIFT_PISTON_CHANNEL_B);

	leftLiftMotor = new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor = new Talon(RIGHT_LIFT_MOTOR_CHANNEL);

	liftEncoder = new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B);
	compressor = new Compressor(0);

	toggleCompressor(true, false);

	this->manipJoystick = manipJoystick;

	limitSwitch = new HematologistAnalogLimitSwitch();

	disableEncoders = false;
}

HematologistManipulator::~HematologistManipulator()
{
	delete secondTierPiston;
	delete binHuggerPiston;
	delete forkliftPiston;
	delete manipJoystick;
	delete limitSwitch;
	delete 	compressor;

	secondTierPiston = NULL;
	binHuggerPiston = NULL;
	forkliftPiston = NULL;
	manipJoystick = NULL;
	limitSwitch= NULL;
	compressor = NULL;
}

void HematologistManipulator::moveLift(float speed)
{
	if (!limitSwitch->limitSwitchIsPressed())
	{

		if (speed > DEADZONE || speed < -DEADZONE)
		{
			leftLiftMotor->Set(speed);
			rightLiftMotor->Set(speed);
		}
		else
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
	}
	else
	{
		if (speed > DEADZONE)
		{
			leftLiftMotor->Set(speed);
			rightLiftMotor->Set(speed);
		}
		else
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
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
<<<<<<< HEAD
			if(liftEncoder->Get() < LIFT_DEADZONE && liftEncoder->Get() > LIFT_DEADZONE)
			{
				binHuggerPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				binHuggerPiston->Set(DoubleSolenoid::kOff);
			}
=======
			if(liftEncoder->Get() < -LIFT_DEADZONE || liftEncoder->Get() > LIFT_DEADZONE)
			{
				binHuggerPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				binHuggerPiston->Set(DoubleSolenoid::kOff);
>>>>>>> master
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

HematologistAnalogLimitSwitch* getLimitSwitch()
{
	return limitSwitch;
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

Talon* getManipTalon(bool right)
{
  if (right)
    return rightLiftMotor;
  else
    return leftLiftMotor;
}

Encoder* getLiftEncoder()
{
  return liftEncoder;
}  