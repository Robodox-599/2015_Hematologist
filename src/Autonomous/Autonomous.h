#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "../HematologistMacros.h"
#include "../HematologistOperatorInterface.h"
#include "../Drive/Drive.h"
#include "../Manipulator/Manipulator.h"

class Autonomous
{
public:
	//Send in these Hematologist Objects rather than creating new ones
	//If you create them again, you'll create a memory conflict
	//You need these to control the robot
	Autonomous(HematologistOperatorInterface* oi, Manipulator* manip, Drive* drive);
	~Autonomous();

	//Send in true to strafe right, false to strafe left	
	void strafeRight();
	void strafeLeft();

	//Moves back, flips long arm back, flips flaps open, moves forward with two bins
	void longArmAuto();

private:
	//I need these Hematologist Objects to control the robot
	HematologistOperatorInterface* oi;
	Manipulator* manip;
	Drive* drive;

	int autonDriveStep;	
	int autonManipStep;
};

#endif
