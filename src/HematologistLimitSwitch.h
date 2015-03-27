#ifndef HEMATOLOGIST_LIMIT_SWITCH_H
#define HEMATOLOGIST_LIMIT_SWITCH_H

#include "HematologistMacros.h"

class HematologistLimitSwitch
{
public:
	HematologistLimitSwitch(int limitSwitchChannel);
	~HematologistLimitSwitch();

	bool isPressed();
private:
	AnalogInput* ai;
};

#endif
