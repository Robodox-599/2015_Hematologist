#include "HematologistAutonomous.h"
#include "HematologistDrive.h"
#include "HematologistManipulator.h"

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

void HematologistAutonomous::strafeRight()
{

	drive(0, 0, .2);
}
/*
12.5 feet per sec
*/
