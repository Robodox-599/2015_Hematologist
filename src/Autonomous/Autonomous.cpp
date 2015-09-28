#include "Autonomous.h"

Autonomous::Autonomous(HematologistOperatorInterface* oi, Manipulator* manip, Drive* drive)
{
	this->oi = oi;
	this->manip = manip;
	this->drive = drive;

	autonDriveStep = 0;
	autonManipStep = 0;
}

Autonomous::~Autonomous()
{
	delete oi;
	delete manip;
	delete drive;
	oi = NULL;
	manip = NULL;
	drive = NULL;
}

void Autonomous::strafeRight()
{
	if (drive->getStrafeAverage() < 1500 + ENCODER_DEADZONE)
		drive->drive(0, 0, -.8);
	else
		drive->drive(0, 0, 0);
}

void Autonomous::strafeLeft()
{
	if (drive->getStrafeAverage() > -1500 - ENCODER_DEADZONE)
		drive->drive(0, 0, .8);
	else
		drive->drive(0, 0, 0);
}

//set up the lift slightly above the ground and face away from the step and toward the driver stations
void Autonomous::longArmAuto()
{
	//if (autonDriveStep == 0)
		drive->resetEncoders();
	if (autonManipStep == 0)
	{
		manip->resetEncoder();
		autonManipStep++;
		manip->closeForklift(true);
		manip->closeSecondTier(true);
		manip->openFlaps(true);
		Wait(1.5);
		autonDriveStep++;	
	}

	if (autonDriveStep == 1)
	{
		drive->resetEncoders();
		if (drive->getForwardAverage() > -550 - ENCODER_DEADZONE)
		{
			drive->drive(-.7, 0, 0);
		}else
		{
			drive->drive(0, 0, 0);
			autonManipStep++;
		}
	}
	
	if (autonManipStep == 2)
	{
		manip->extendLongArm(true);	
		Wait(1);
		manip->openFlaps(true);
		drive->resetEncoders();	//reset encoders so that some of the slack doesn't affect how far the robot would move
		autonDriveStep++;
		autonManipStep++;
	}

	if (autonDriveStep == 2)
	{
		if (drive->getForwardAverage() < 1200 + ENCODER_DEADZONE)
			drive->drive(.5, 0, 0);
		else
		{
			drive->drive(0, 0, 0);
			autonManipStep++;
		}
	}

	if (autonManipStep == 4)	//autonManipStep not checking 3 b/c in autonManipStep==2, we increased autonManipStep so that we don't 
											//repeat that if statement but we don't want to do the next step for manip until after autonDriveStep was done
	{
		manip->retractLongArm(true);	//do long arm first b/c if you try the flaps first you'll knock something over
		manip->closeFlaps(true);
	}
}




























