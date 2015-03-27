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