#include "HematologistAnalogLimitSwitch.h"

HematologistAnalogLimitSwitch::HematologistAnalogLimitSwitch()
{
	ai = new AnalogInput(LIMIT_SWITCH_CHANNEL);

}

HematologistAnalogLimitSwitch::~HematologistAnalogLimitSwitch()
{
	delete ai;

	ai = NULL;
}

bool HematologistAnalogLimitSwitch::limitSwitchIsPressed()
{
	if (ai->GetVoltage() > 4)
	{
		return false;
	}
	else
	{
		if (ai->GetVoltage() < 1)
		{
			return true;
		}
	}
	
	return false;
}