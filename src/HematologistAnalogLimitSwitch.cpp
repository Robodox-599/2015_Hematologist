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
	if (aiTop->GetVoltage() > 4)
	{
		return true;
	}
	else
	{
		if (aiTop->GetVoltage() < 1)
		{
			return false;
		}
	}
	
	return false;
}