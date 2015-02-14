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

bool HematologistAnalogLimitSwitch::topLimitSwitchIsPressed()
{
	if (aiTop->GetVoltage() > 4)
	{
		return false;
	}
	else
	{
		if (aiTop->GetVoltage() < 1)
		{
			return true;
		}
	}
	
	return true;
}

bool HematologistAnalogLimitSwitch::bottLimitSwitchIsPressed()
{
	if (aiBottom->GetVoltage() > 4)
	{
		return false;
	}
	else
	{
		if (aiBottom->GetVoltage() < 1)
		{
			return true;
		}
	}
	
	return true;
}