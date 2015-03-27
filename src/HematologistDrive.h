#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H

#include "HematologistMacros.h"

class HematologistDrive
{
public:

private:
	Talon* frontLeftMotor;
	Talon* frontRightMotor;
	Talon* backLeftMotor;
	Talon* backRightMotor;

	Encoder* frontLeftEncoder;
	Encoder* frontRightEncoder;
	Encoder* backLeftEncoder;
	Encoder* backRightEncoder;
};

#endif
