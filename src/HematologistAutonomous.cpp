#include "HematologistAutonomous.h"

HematologistAutonomous::HematologistAutonomous(HematologistOperatorInterface* oi, HematologistManipulator* manip, HematologistDrive* drive)
{
	this->oi = oi;
	this->manip = manip;
	this->drive = drive;
	int driveStep = 0;
	int manipStep = 0;
}

HematologistAutonomous::~HematologistAutonomous()
{
	delete oi;
	delete manip;
	delete drive;
	oi = NULL;
	manip = NULL;
	drive = NULL;
}

HematologistAutonomous::strafe(bool right)
{
	if (right)
	{
		if (drive->getStrafeAverage() < 2000 + ENCODER_DEADZONE)
		{
			drive->drive(0, 0, .8);
		}else
		{
			drive->drive(0, 0, 0);
		}
	}else
	{
		if (drive->getStrafeAverage() > -2000 - ENCODER_DEADZONE)
			drive->drive(0, 0, -.8);
		else
			drive->drive(0, 0, 0);
	}
}