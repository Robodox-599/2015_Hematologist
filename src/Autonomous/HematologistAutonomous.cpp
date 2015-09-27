#include "HematologistAutonomous.h"

HematologistAutonomous::HematologistAutonomous(HematologistOperatorInterface* oi, HematologistManipulator* manip, HematologistDrive* drive)
{
	this->oi = oi;
	this->manip = manip;
	this->drive = drive;
	//You have to initialize these steps to make the sequence work
	driveStep = 0;
	manipStep = 0;
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

void HematologistAutonomous::strafe(bool right)
{
	if (right)
	{
		if (drive->getStrafeAverage() < 1500 + ENCODER_DEADZONE)	//check if the encoder value is too low
		{
			drive->drive(0, 0, -.8);	//moves right
		}else
		{
			drive->drive(0, 0, 0);	//stops when enoder value is too high
		}
	}else
	{
		if (drive->getStrafeAverage() > -1500 - ENCODER_DEADZONE)	//checks a neg b/c if you move left, the encoder value decreases
			drive->drive(0, 0, .8);	//moves left
		else
			drive->drive(0, 0, 0);	//stops when encoder value too big (neg)	
	}
}

//set up the lift slightly above the ground and face away from the step and toward the driver stations
void HematologistAutonomous::longArmAuto()
{

	//driveStep will deal with drive stuff
	//manipStep will deal with manipulator stuff

	if (driveStep == 0)
	{
		drive->resetEncoders();
	}
	if (manipStep == 0)
	{
		manip->resetEncoder();
		manipStep++;
		//close all pistons b/c necessary to drive over the scoring platform
		manip->closeForklift(true);
		manip->closeSecondTier(true);
		// manip->openFlaps(true);
		driveStep++;
		Wait(3);	
	}
	/*took this part out as the lift would instead be position high enough so we don't have to wait for it to lift
	if (manipStep == 1)
	{
		if (manip->getEncoderValue() < 1000 + ENCODER_DEADZONE)
		{
			//manip->moveLift(.4);
		}else
		{
			//manip->moveLift(0);
		}
	}*/

	//drives backward using encoder to check if he's far enought, all the way to the step
	if (driveStep == 1)
	{
		if (drive->getForwardAverage() > -550 - ENCODER_DEADZONE)
		{
			drive->drive(-.7, 0, 0);
		}else
		{
			drive->drive(0, 0, 0);
			manipStep++;	//once at the step, robot doesn't move until after manipulator shit has gone down so drive++ not done
		}
	}
	if (manipStep == 2)
	{
		manip->extendLongArm(true);	
		Wait(3);	//b/c long arm takes forever
		manip->openFlaps(true);
		drive->resetEncoders();	//reset encoders so that some of the slack doesn't affect how far the robot would move
		driveStep++;
		manipStep++;
	}
	//drives forward
	if (driveStep == 2)
	{
		if (drive->getForwardAverage() < 1200 + ENCODER_DEADZONE)
			drive->drive(.5, 0, 0);
		else
		{
			drive->drive(0, 0, 0);
			manipStep++;
		}
	}
	//close all of the log arm stuff
	if (manipStep == 4)	//manipStep not checking 3 b/c in manipStep==2, we increased manipStep so that we don't 
											//repeat that if statement but we don't want to do the next step for manip until after driveStep was done
	{
		manip->retractLongArm(true);	//do long arm first b/c if you try the flaps first you'll knock something over
		manip->closeFlaps(true);
	}
}




























