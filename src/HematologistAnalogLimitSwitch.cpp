#include "HematologistAnalogLimitSwitch.h"

HematologistAnalogLimitSwitch::HematologistAnalogLimitSwitch(int limitSwitchChannel)
{
	ai = new AnalogInput(limitSwitchChannel);

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
