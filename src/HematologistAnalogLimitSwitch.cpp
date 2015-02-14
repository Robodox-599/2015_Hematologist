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
		return true;
	}
	else
	{
		if (ai->GetVoltage() < 1)
		{
			return false;
		}
	}
	
	return false;
}
