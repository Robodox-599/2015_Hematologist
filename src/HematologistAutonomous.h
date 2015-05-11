#ifndef HEMATOLOGIST_AUTONOMOUS_H
#define HEMATOLOGIST_AUTONOMOUS_H

/*
	All files included as Autonomous needs to use the oi, manip, and drive, to move every aspect of the robot
*/
#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"
#include "HematologistDrive.h"
#include "HematologistManipulator.h"

class HematologistAutonomous
{
public:
	HematologistAutonomous(HematologistOperatorInterface* oi, HematologistManipulator* manip, HematologistDrive* drive);
	~HematologistAutonomous();

	/*
		param: bool right
		Will strafe right if you pass in true
		Will strafe left if you pass in false
	*/
	void strafe(bool right);

	//Will do long arm auto
	//logic explanation in code in  .cpp file
	void longArmAuto();

private:
	HematologistOperatorInterface* oi;
	HematologistManipulator* manip;
	HematologistDrive* drive;

	//steps here used to determine which part of auto is to be done
	int driveStep;	
	int manipStep;

	
};

#endif