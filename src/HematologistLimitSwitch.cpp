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

/*
    the analog input lets us do a few things but the most important is tell us the voltage going through it

    imagine a wire and imagine that there is a switch there that is open. 
        this means no current and so no voltage. so when the voltage is 0 (or to allow for some error < 1), the switch is open
        if the switch is open, that means it's not being pressed down to close the switch
    when the switch is closed (when the limit switch is pressed) there is a voltage
        now the voltage across any port in the roboRio can be found with the ground pin (ask electornics to show you where that is)
        for the analog port, it was 5. but testing showed that we would get something like 4.8
        so instead of checking if the voltage == 5, we just checked if it was greater than 4
*/
bool HematologistLimitSwitch::isPressed()
{
	if (ai->GetVoltage() > 4)
		return true;
	else
		if (ai->GetVoltage() < 1)
			return false;
    //see how the two return statements above are in if statements. 
    //the compiler sees that and says that I have to have a return statement outside if statements
    //so i made one and made it the most sense-making default, false
    //remember, I only want the control of the lift to be limited when the switch is hit. Unless I'm sure, 
    //I don't want to take that control away from the drivers by returning true by default
	return false;

}
