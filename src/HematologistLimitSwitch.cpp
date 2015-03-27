#include "HematologistLimitSwitch.h"

HematologistLimitSwitch::HematologistLimitSwitch(int limitSwitchChannel)
{
	ai = new AnalogInput(limitSwitchChannel);
}

HematologistLimitSwitch::~HematologistLimitSwitch()
{
	delete ai;
	ai = NULL;
}


bool HematologistLimitSwitch::isPressed()
{
	if (ai->GetVoltage() > 4)
		return true;
	else
		if (ai->GetVoltage() < 1)
			return false;
	return false;

}
