#ifndef HEMATOLOGIST_MANIPULATOR_H
#define HEMATOLOGIST_MANIPULATOR_H

#include "HematologistMacros.h"

class HematologistManipulator
{
public:

private:
	DoubleSolenoid* forkliftPiston;	
	DoubleSolenoid* secondTierPiston;
	DoubleSolenoid* binHuggerPiston;
	DoubleSolenoid* longArmPiston;

	Relay* flapOpenRelay;
	Relay* flapCloseRelay;

	Encoder* liftEncoder;

	Compressor* compressor

};

#endif