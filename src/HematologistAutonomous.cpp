#include "HematologistAutonomous.h"
#include "HematologistDrive.h"
#include "HematologistManipulator.h"

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip)
{
	this->drive = drive;
	this->manip = manip;
	timer = new Timer();
}

virtual HematologistAutonomous::~HematologistAutonomous()
{
	delete drive();
	drive = NULL;
}

void HematologistAutonomous::strafeRight()
{
	timer->Reset();
	timer->Start();
	while(timer->Get() < 5000)
	{
		drive(.5, 0, 0);
	}
	drive(0, 0, 0);

}
/