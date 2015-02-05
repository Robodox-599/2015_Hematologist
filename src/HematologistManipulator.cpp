#include "HematologistManipulator.h"
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator()
{
	secondTierPiston = new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A);
	binHuggerPiston = new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A);
	forkliftPiston = new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A);
	manipJoystick = new Joystick(MANIP_JOYSTICK);
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
	if(liftEncoder->Get() < LIFTDEADZONE && liftEncoder->Get() > -LIFTDEADZONE)
	{
		binHuggerPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		if(liftEncoder->Get < LIFTDEADZONE < -LIFTDEADZONE && liftEncoder->Get() > LIFTDEADZONE)
		{
			binHuggerPiston->Set(DoubleSolenoid::kBackward);
		}
		else
		{
			binHuggerPiston->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::openSecondTier()
{
	if(liftEncoder->Get() < LIFTDEADZONE && liftEncoder->Get() > -LIFTDEADZONE)
	{
		secondTierPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		if(liftEncoder->Get < LIFTDEADZONE < -LIFTDEADZONE && liftEncoder->Get() > LIFTDEADZONE)
		{
			secondTierPiston->Set(DoubleSolenoid::kBackward);
		}
		else
		{
			secondTierPiston->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::openForklift()
{
	if(liftEncoder->Get() < LIFTDEADZONE && liftEncoder->Get() > -LIFTDEADZONE)
	{
		forkliftPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		if(liftEncoder->Get < LIFTDEADZONE < -LIFTDEADZONE && liftEncoder->Get() > LIFTDEADZONE)
		{
			forkliftPiston->Set(DoubleSolenoid::kBackward);
		}
		else
		{
			forkliftPiston->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::openBinHuggerButton()
{
	if(manipJoystick->GetRawButton(BIN_HUGGER_OPEN_BUTTON))
	{
		binHuggerPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		if(manipJoystick->GetRawButton(BIN_HUGGER_OPEN_BUTTON))
		{
			binHuggerPiston->Set(DoubleSolenoid::kBackward);
		}
		else
		{
			binHuggerPiston->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::openForkliftButton()
{
	if(manipJoystick->GetRawButton(FORKLIFT_OPEN_BUTTON))
	{
		forkliftPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		if(manipJoystick->GetRawButton(FORKLIFT_OPEN_BUTTON))
		{
			forkliftPiston->Set(DoubleSolenoid::kBackward);
		}
		else
		{
			forkliftPiston->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulator::openSecondTierButton()
{
	if(manipJoystick->GetRawButton(SECOND_TIER_OPEN_BUTTON))
	{
		secondTierPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		if(manipJoystick->GetRawButton(SECOND_TIER_OPEN_BUTTON))
		{
			secondTierPiston->Set(DoubleSolenoid::kBackward);
		}
		else
		{
			secondTierPiston->Set(DoubleSolenoid::kOff);
		}
	}
}

void HematologistManipulators::ignoreEncoders()
{
	if(manipJoystick->GetRawButton(IGNORE_ENCODERS_BUTTON))
	{
		//ignore encoders thing
	}
}

void HematologistManipulators::resetEncoders()
{
	
}