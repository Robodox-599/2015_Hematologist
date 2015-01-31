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

void HematologistAutonomous::drive()
{
	drive->setLinearDrive(linearValue);
	drive->setTurn(turnValue);
	drive->setStrafe(sideValue);
	drive->frontLeftMotor->Set(forward + side + spin);
	drive->frontRightMotor->Set(-forward + side + spin);
	drive->backLeftMotor->Set(forward - side + spin);
	drive->backRightMotor->Set(-forward - side + spin);
}

/*
12.5 feet per sec
*/
