#ifndef HEMATOLOGIST_AUTONOMOUS_H_
#define HEMATOLOGIST_AUTONOMOUS_H_

#include "WPILib.h"

class HematologistAutonomous
{
private:
	HematologistManipulator *manip;
	HematologistDrive* drive;

public:
	HematologistAutonomous();
	~HematologistAutonomous();
	
	void firstHemanAuto();
	void secondHemanAuto();
	void thirdHemanAuto(); // gets 3 totes and stack it
};
