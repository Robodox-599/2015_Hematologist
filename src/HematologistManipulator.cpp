#include "HematologistManipulator.h"
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator(Joystick* manipJoystick)
{
	secondTierPiston = new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A);
	binHuggerPiston = new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A);
	forkliftPiston = new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A);

	leftLiftMotor = new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor = new Talon(RIGHT_LIFT_MOTOR_CHANNEL);

	liftEncoder = new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B);

	this->manipJoystick = manipJoystick;

	disableEncoders = false;
}

virtual HematologistManipulator::~HematologistManipulator()
{
	delete secondTierPiston;
	delete binHuggerPiston;
	delete forkliftPiston;
	delete manipJoystick;

	secondTierPiston = NULL;
	binHuggerPiston = NULL;
	forkliftPiston = NULL;
	manipJoystick = NULL;
}

void HematologistManipulator::openBinHugger()
{
	if (manipJoystick->GetRawButton(IGNORE_ENCODERS_BUTTON))
	{
		disableEncoders != disableEncoders; 
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
			if(liftEncoder->Get() < LIFT_DEADZONE && liftEncoder->Get() > -LIFT_DEADZONE)
			{
				binHuggerPiston->Set(DoubleSolenoid::kForward);
			}
			else
			{
			if(liftEncoder->Get < LIFT_DEADZONE && liftEncoder->Get() > LIFT_DEADZONE)
			{
				binHuggerPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				binHuggerPiston->Set(DoubleSolenoid::kOff);
			}
		}
	}
}

void HematologistManipulator::openSecondTier()
{
	if (IGNORE_ENCODERS_BUTTON)
	{
		disableEncoders != disableEncoders; 
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
		if(liftEncoder->Get() < LIFT_DEADZONE && liftEncoder->Get() > -LIFT_DEADZONE)
		{
			secondTierPiston->Set(DoubleSolenoid::kForward);
		}
		else
		{
			if(liftEncoder->Get < LIFT_DEADZONE < -LIFT_DEADZONE && liftEncoder->Get() > LIFT_DEADZONE)
			{
			secondTierPiston->Set(DoubleSolenoid::kReverse);
			}
		}
	}

}

void HematologistManipulator::openForklift()
{
	if (IGNORE_ENCODERS_BUTTON)
	{
		disableEncoders != disableEncoders; 
	}

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
			if(liftEncoder->Get() < LIFT_DEADZONE && liftEncoder->Get() > -LIFT_DEADZONE)
			{
			forkliftPiston->Set(DoubleSolenoid::kForward);
			}
		else
		{
			if(liftEncoder->Get < LIFT_DEADZONE < -LIFT_DEADZONE && liftEncoder->Get() > LIFT_DEADZONE)
			{
				forkliftPiston->Set(DoubleSolenoid::kReverse);
			}
			else
			{
				forkliftPiston->Set(DoubleSolenoid::kOff);
			}
		}
	}
}


void HematologistManipulator::resetEncoders()
{
	liftEncoder->Reset();
}
