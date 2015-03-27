#include "HematologistAutonomous.h"

HematologistAutonomous::HematologistAutonomous(HematologistOperatorInterface* oi, HematologistManipulator* manip, HematologistDrive* drive)
{
	this->oi = oi;
	this->manip = manip;
	this->drive = drive;
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

