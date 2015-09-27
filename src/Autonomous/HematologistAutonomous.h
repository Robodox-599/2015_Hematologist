#ifndef HEMATOLOGIST_AUTONOMOUS_H
#define HEMATOLOGIST_AUTONOMOUS_H

#include "../HematologistMacros.h"
#include "../HematologistOperatorInterface.h"
#include "../Drive/HematologistDrive.h"
#include "../Manipulator/HematologistManipulator.h"

class HematologistAutonomous
{
public:
	//Send in these Hematologist Objects rather than creating new ones
	//If you create them again, you'll create a memory conflict
	//You need these to control the robot
	HematologistAutonomous(HematologistOperatorInterface* oi, HematologistManipulator* manip, HematologistDrive* drive);
	~HematologistAutonomous();

	//Send in true to strafe right, false to strafe left	
	void strafe(bool right);

	//Moves back, flips long arm back, flips flaps open, moves forward with two bins
	void longArmAuto();

private:
	//I need these Hematologist Objects to control the robot
	HematologistOperatorInterface* oi;
	HematologistManipulator* manip;
	HematologistDrive* drive;

	//These two variables are used to keep track of where in the sequence the robot is in
	int driveStep;	
	int manipStep;

	
};

#endif
