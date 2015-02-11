#ifndef HEMATOLOGIST_ANALOG_LIMIT_SWITCH_H_
#define HEMATOLOGIST_ANALOG_LIMIT_SWITCH_H_

#include "HematologistMacros.h"

class HematologistAnalogLimitSwitch
{
public:
	HematologistAnalogLimitSwitch();
	~HematologistAnalogLimitSwitch();

private:
	AnalogInput* ai;

}