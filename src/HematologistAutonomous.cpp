#include "HematologistAutonomous.h"
#include "HematologistDrive.h"

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip)
{
	this->drive = drive;
	this->manip = manip;
}

virtual HematologistAutonomous::~HematologistAutonomous()
{
	delete drive();

	drive = NULL;
}

void HematologistAutonomous::autonStrafeRight()
{
	drive->setAutonStrafe(1);
	drive->HematologistStrafeDrive();
	sleep(1000);
}
/*
12.5 feet per sec
*/
