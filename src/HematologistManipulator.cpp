#include "HematologistManipulator.h"
#include "HematologistMacros.h"

HematologistManipulator::HematologistManipulator(Joystick* manipJoystick)
{
	secondTierPiston = new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A, SECOND_TIER_PISTON_CHANNEL_B);
	binHuggerPiston = new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A, BIN_HUGGER_PISTON_CHANNEL_B);
	forkliftPiston = new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A, FORKLIFT_PISTON_CHANNEL_B);
	longArmPiston = new DoubleSolenoid(LONG_ARM_PISTON_CHANNEL_A, LONG_ARM_PISTON_CHANNEL_B);

	longArmFlapOpen = new Relay(LONG_ARM_RELAY_OPEN_CHANNEL, Relay::kForwardOnly);
	longArmFlapClose = new Relay(LONG_ARM_RELAY_CLOSE_CHANNEL, Relay::kForwardOnly);

	closePiston(true, true);
	closePiston(false, true);

	leftLiftMotor = new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor = new Talon(RIGHT_LIFT_MOTOR_CHANNEL);

	leftRollerMotor = new Talon(LEFT_ROLLER_MOTOR_CHANNEL);
	rightRollerMotor = new Talon(RIGHT_ROLLER_MOTOR_CHANNEL);

	liftEncoder = new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B);
	compressor = new Compressor(0);

	compressor->SetClosedLoopControl(true);

	this->manipJoystick = manipJoystick;

	topLimitSwitch = new HematologistAnalogLimitSwitch(TOP_LIMIT_SWITCH_CHANNEL);
	bottomLimitSwitch = new HematologistAnalogLimitSwitch(BOTTOM_LIMIT_SWITCH_CHANNEL);

	disableEncoders = false;

	forkliftOpen = true;
	secondTierOpen = true;

	flapsOpen = false;

	automaticActivation = false;

	longArmOpen1 = longArmOpen2 = longArmOpen3 = false;
	longArmClose1 = longArmClose2 = longArmClose3 = false;

	timer = new Timer();
	autoRollerStep = 0;
}

HematologistManipulator::~HematologistManipulator()
{
	delete secondTierPiston;
	delete binHuggerPiston;
	delete forkliftPiston;
	delete manipJoystick;
	delete topLimitSwitch;
	delete bottomLimitSwitch;
	delete compressor;
	delete timer;

	secondTierPiston = NULL;
	binHuggerPiston = NULL;
	forkliftPiston = NULL;
	manipJoystick = NULL;
	topLimitSwitch= NULL;
	bottomLimitSwitch = NULL;
	compressor = NULL;
	timer = NULL;
}

void HematologistManipulator::moveLift(float speed)
{
	if (topLimitSwitch->limitSwitchIsPressed())
	{
		if (-speed > DEADZONE)
		{
			leftLiftMotor->Set(0);
			rightLiftMotor->Set(0);
		}
		else
		{
			if (-speed < -DEADZONE)
			{
				leftLiftMotor->Set(-speed);
				rightLiftMotor->Set(-speed);
			}
			else
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}
		}
	}
	else
	{
		if (bottomLimitSwitch->limitSwitchIsPressed())
		{
			liftEncoder->Reset();
			if (-speed < -DEADZONE)
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}
			else
			{
				if (-speed > DEADZONE)
				{
					leftLiftMotor->Set(-speed);
					rightLiftMotor->Set(-speed);
				}
				else
				{
					leftLiftMotor->Set(0);
					rightLiftMotor->Set(0);
				}
			}
		}
		else
		{
			if (-speed > DEADZONE || -speed < -DEADZONE)
			{
				leftLiftMotor->Set(-speed);
				rightLiftMotor->Set(-speed);
			}
			else
			{
				leftLiftMotor->Set(0);
				rightLiftMotor->Set(0);
			}
		}
	}
}

HematologistAnalogLimitSwitch* HematologistManipulator::getLimitSwitch(bool top)
{
	if (top)
		return topLimitSwitch;
	else
		return bottomLimitSwitch;
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
		automaticActivation = true;
	if (automaticActivation)
	{
		closePiston(true, true);
		if (liftEncoder->Get() < 2000 - LIFT_DEADZONE)
		{
			leftLiftMotor->Set(.3);
			rightLiftMotor->Set(.3);
		}
		if (liftEncoder->Get() > 2000 - LIFT_DEADZONE && liftEncoder->Get() < 2000 + LIFT_DEADZONE)
		{
			openPiston(false, true);
		}
		if (liftEncoder->Get() > 2500 - LIFT_DEADZONE && liftEncoder->Get() < 2500 + LIFT_DEADZONE)
		{
			closePiston(false, true);
			leftLiftMotor->Set(-.2);
			rightLiftMotor->Set(-.2);
			automaticActivation = false;
		}
	}
	else
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
		{
			forkliftPiston->Set(DoubleSolenoid::kReverse);
			forkliftOpen = true;
		}else{
			secondTierPiston->Set(DoubleSolenoid::kForward);
			secondTierOpen = true;
		}
	}
	else
		return;
}

void HematologistManipulator::closePiston(bool forklift, bool open)
{
	if (open)
	{
		if (forklift){
			forkliftPiston->Set(DoubleSolenoid::kForward);
			forkliftOpen = false;
		}
		else
		{
			secondTierPiston->Set(DoubleSolenoid::kReverse);
			secondTierOpen = false;
		}
	}
	else
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

void HematologistManipulator::openBinHugger(bool open)
{
	if (open)
	{
		binHuggerPiston->Set(DoubleSolenoid::kReverse);
		binHuggerOpen = false;
	}
	else
		return;
}

void HematologistManipulator::closeBinHugger(bool close)
{
	if (close)
	{
		binHuggerPiston->Set(DoubleSolenoid::kForward);
		binHuggerOpen = false;
	}
	else
		return;
}

bool HematologistManipulator::binHuggerIsOpen()
{
	return binHuggerOpen;
}

bool HematologistManipulator::forkliftIsOpen()
{
	return forkliftOpen;
}

bool HematologistManipulator::secondTierIsOpen()
{
	return secondTierOpen;
}

void HematologistManipulator::longArmMoveOut(bool move, bool confirm)
{
	if (move && confirm)
		longArmPiston->Set(DoubleSolenoid::kForward);
	else
		return;

}

void HematologistManipulator::longArmMoveIn(bool move, bool confirm)
{
	if (move && confirm)
		longArmPiston->Set(DoubleSolenoid::kReverse);
	else
		return;
}

void HematologistManipulator::automaticallyOpenTier()
{
	if (liftEncoder->Get() < 1700 - LIFT_DEADZONE)
		automaticActivation = true;
	if (liftEncoder->Get() > 1700 - LIFT_DEADZONE && liftEncoder->Get() < 1800 + LIFT_DEADZONE && automaticActivation)
	{
		openPiston(false, true);
		automaticActivation = false;
	}
	if (liftEncoder->Get() > 1800 + LIFT_DEADZONE)
		automaticActivation = false;
}

Relay* HematologistManipulator::getLongArmFlap(bool open)
{
	if (open)
		return longArmFlapOpen;
	else
		return longArmFlapClose;
}

bool HematologistManipulator::flapsIsOpen()
{
	return flapsOpen;
}

void HematologistManipulator::openFlaps(bool open)
{
	if (open)
	{
		longArmFlapOpen->Set(Relay::kForward);
		longArmFlapClose->Set(Relay::kOff);
		flapsOpen = true;
	}else
		return;
}

void HematologistManipulator::closeFlaps(bool close)
{
	if (close)
	{
		longArmFlapOpen->Set(Relay::kOff);
		longArmFlapClose->Set(Relay::kForward);
		flapsOpen = false;
	}else
		return;
}

void HematologistManipulator::toggleRollers(bool toggle, float direction)
{
	if(toggle)
	{
		if(direction > 0)
		{
			leftRollerMotor->Set(-1);
			rightRollerMotor->Set(-1);
		}
		else if(direction <= 0)
		{
			leftRollerMotor->Set(1);
			rightRollerMotor->Set(1);
		}
	}
	else
    {
    	leftRollerMotor->Set(0);
    	rightRollerMotor->Set(0);
    }
}

void HematologistManipulator::autoRollers()
{
	if(!forkliftOpen && autoRollerStep == 0)
	{
		autoRollerStep = 1;
		timer->Start();
	}
	if(autoRollerStep == 1)
	{
		if(timer->Get() < 5)
		    toggleRollers(true, -1);
		else
			autoRollerStep = 2;
	}
	if(autoRollerStep == 2)
	{
		toggleRollers(false, 1);
		autoRollerStep = 3;
	}
	if(autoRollerStep == 3 && forkliftOpen)
	{
		autoRollerStep = 0;
		timer->Reset();
	}
	if (autoRollerStep == 1 && forkliftOpen)
	{
		autoRollerStep = 2;
	}
}

void HematologistManipulator::lift(float speed, bool buttonIsPressed)
{
	if(buttonIsPressed)
	{
		autoLiftIsActive = true;
	}
	if(autoLiftIsActive)
	{
		if(liftEncoder->Get() < 1550)
		{
			moveLift(0.4);
		}
		else if(liftEncoder->Get() < 1600)
		{
			moveLift(0);
			openPiston(true, true);
			lowerForklift = true;
		}
		if(lowerForklift)
		{
			moveLift(-0.4);
		}

	}
	else
	{
		autoLiftIsActive = false;
	}
	if(bottomLimitSwitch)
	{
		autoLiftIsActive = false;
		lowerForklift = true;
	}
}
