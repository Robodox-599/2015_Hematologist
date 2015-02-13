#ifndef HEMATOLOGIST_AUTONOMOUS_H_
#define HEMATOLOGIST_AUTONOMOUS_H_

#include "HematologistMacros.h"
#include "HematologistManipulator.h"
#include "HematologistDrive.h"

class HematologistAutonomous
{
private:
	HematologistManipulator *manip;
	HematologistDrive* drive;

public:
	HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip);
	~HematologistAutonomous();
	
	void firstHemanAuto();
	void secondHemanAuto();
	void thirdHemanAuto(); // gets 3 totes and stack it
	int encoderAverage();
};

#endif
