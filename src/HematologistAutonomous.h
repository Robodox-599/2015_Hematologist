#ifndef HEMATOLOGIST_AUTONOMOUS_H
#define HEMATOLOGIST_AUTONOMOUS_H

#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"
#include "HematologistDrive.h"
#include "HematologistManipulator.h"

class HematologistAutonomous
{
public:
	HematologistAutonomous(HematologistOperatorInterface* oi, HematologistManipulator* manip, HematologistDrive* drive);
	~HematologistAutonomous();

	int driveStep;
	int manipStep;
private:
	HematologistOperatorInterface* oi;
	HematologistManipulator* manip;
	HematologistDrive* drive;
};

#endif