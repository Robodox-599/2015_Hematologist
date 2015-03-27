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

HematologistAutonomous::longArmAuto()
{
	if (driveStep == 0)
	{
		drive->resetEncoders();
		driveStep++;
	}
	if (manipStep == 0)
	{
		manip->resetEncoder();
		manipStep++;
		closeForklift(true);
		closeSecondtier(true);
	}
	if (manipStep == 1)
	{
		if (manip->getEncoderValue() < 1000 + ENCODER_DEADZONE)
		{
			manip->moveLift(.4);
		}else
		{
			manip->moveLift(0);
			manipStep++;
		}
	}
	if (driveStep == 1)
	{
		if (drive->getForwardAverage() > -500 - ENCODER_DEADZONE)
		{
			drive->drive(-.7, 0, 0);
		}else
		{
			drive->drive(0, 0, 0);
		}
	}
	if (manipStep == 2)
	{
		manip->extendLongArm();
		Wait(1.5);
		drive->resetEncoders();
		manip->openFlaps();
		driveStep++;
	}
	if (driveStep == 2)
	{
		if (drive->getForwardAverage() < 1200 + ENCODER_DEADZONE)
			drive->drive(.5, 0, 0);
		else
		{
			drive->drive(0, 0, 0);
			driveStep++;
			manipStep++;
		}
	}
	if (manipStep == 3)
	{
		manip->retractLongArm();
		manip->closeFlaps();
		manipStep++;
	}


}




























