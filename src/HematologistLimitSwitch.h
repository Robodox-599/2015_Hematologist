#ifndef HEMATOLOGIST_LIMIT_SWITCH_H
#define HEMATOLOGIST_LIMIT_SWITCH_H

#include "HematologistMacros.h"

/*
    this class is special
    for one limitswitches are not usually coded this way and the only reason why we did it here is because we ran out of digital ports
    so, we had to use an analog port which mean't sautering for electornics and a really weird coding problem for software
    here's how it works
*/
class HematologistLimitSwitch
{
public:
	HematologistLimitSwitch(int limitSwitchChannel);
	~HematologistLimitSwitch();

    //tells us if the limit switch is pressed. the logic is more talked about in the .cpp file
	bool isPressed();
private:
    //because we had to use an analog port, that meant we had to read the analog port
    //this analog input lets us do that
	AnalogInput* ai;  
};

#endif
