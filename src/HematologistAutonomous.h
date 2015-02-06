#ifndef HEMATOLOGIST_AUTONOMOUS_H_
#define HEMATOLOGIST_AUTONOMOUS_H_

#include "WPILib.h"

class HematologistAutonomous
{
private:
	HematologistManipulator *man;
	HematologistDrive* drive;
	Encoder* frontLeftEnc; //encoders for drive motor
	Encoder* frontRightEnc;
	Encoder* backLeftEnc;
	Encoder* backRightEnc;

public:
	HematologistAutonomous();
	~HematologistAutonomous();

	void secondHemanAuto(); // gets 3 totes and stack it
};
