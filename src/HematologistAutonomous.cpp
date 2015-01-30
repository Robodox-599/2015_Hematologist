#include "HematologistAutonomous.h"

HematologistAutonomous::HematologistAutonomous()
{
	drive = new Drive();
}

virtual HematologistAutonomous::~HematologistAutonomous()
{
	delete drive();

	drive = NULL;
}

void HematologistAutonomous::autonStrafeRight()
{
	drive->setStrafe(1);
	drive->drive();
	sleep(1000);
}
