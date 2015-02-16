#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip)
{
	this->drive = drive;
	this->manip = manip;
	step1 = true;	
	step2 = false;	//this step will not start, must be told when to
	step3 = false;	//this step will not start, must be told when to
	step4 = false;	//this step will not start, must be told when to
	step5 = false;	//this step will not start, must be told when to
	step6 = false;	//this step will not start, must be told when to
	step7 = false;	//this step will not start, must be told when to
	step8 = false;	//this step will not start, must be told when to
	step9 = false;
}
HematologistAutonomous::~HematologistAutonomous(){
	delete drive;
	delete manip;

	drive = NULL;
	manip = NULL;
}

void HematologistAutonomous::strafeRight()
{
	drive->drive(0, 0, .4);
	Wait(.3);
	drive->drive(0, 0, 0);
}

void HematologistAutonomous::getTwoTotes()
{
	if (step1){
		drive->getEncoder(true, true)->Reset();
		drive->getEncoder(true, false)->Reset();
		drive->getEncoder(false, true)->Reset();
		drive->getEncoder(false, false)->Reset();
		manip->getLiftEncoder()->Reset();
		step1 = false;
		step2 = true;
	}
	if (step2)
	{
		if (getForwardAverage() < 20 - LIFT_DEADZONE)
			drive->drive(.1,0,0);
		else if (getForwardAverage() > 20 + LIFT_DEADZONE)
			drive->drive(-.1, 0, 0);
		else
		{
			step3 = true;
			step4 = true;
			manip->closePiston(true, true);
			step2 = false;
		}
	}
	if (step3)
	{
		drive->getEncoder(true, true)->Reset();
		drive->getEncoder(true, false)->Reset();
		drive->getEncoder(false, true)->Reset();
		drive->getEncoder(false, false)->Reset();
		if (getForwardAverage() < 100 - LIFT_DEADZONE)
			drive->drive(.1, 0, 0);
		else if (getForwardAverage() > 100 + LIFT_DEADZONE)
			drive->drive(-.1, 0, 0);
		else
		{
			drive->drive(0, 0, 0);
			step3 = false;
			step5 = true;
			drive->getEncoder(true, true)->Reset();
			drive->getEncoder(true, false)->Reset();
			drive->getEncoder(false, true)->Reset();
			drive->getEncoder(false, false)->Reset();
		}
	}
	if (step4)
	{
		if (manip->getLiftEncoder()->Get() < 30 - LIFT_DEADZONE)
			manip->moveLift(.1);
		else if (manip->getLiftEncoder()->Get() > 30 + LIFT_DEADZONE)
			manip->moveLift(-.1)
		else
		{
			manip->moveLift(0);
			step4 = false;
			manip->getLiftEncoder()->Reset();
			manip->closePiston(false, true);
			step6 = true;
		}
	}

	if (step5)
	{
		if (getTurnAverage() < 100 - LIFT_DEADZONE)
			drive->drive(0, .3, 0);
		else if (getTurnAverage() > 100 + LIFT_DEADZONE)
			drive->drive(0, -.3, 0);
		else
		{
			drive->drive(0,0,0);
			step5 = false;
			step7 = true;
			drive->getEncoder(true, true)->Reset();
			drive->getEncoder(true, false)->Reset();
			drive->getEncoder(false, true)->Reset();
			drive->getEncoder(false, false)->Reset();

		}
	}

	if (step6)
	{
		if (manip->getLimitSwitch(false)->limitSwitchIsPressed())
		{
			manip->moveLift(-.1);
		}else
		{
			manip->move(0);
			manip->getLiftEncoder()->Reset();
		}
	}

	if (step7)
	{
		if (getForwardAverage() < 100 - LIFT_DEADZONE)
			drive->drive(.1, 0, 0);
		else if (getForwardAverage() > 100 - LIFT_DEADZONE)
			drive->drive(-.1, 0, 0);
		else
		{
			step7 = false;
			drive->drive(0, 0, 0);
			manip->closePiston(true, true);
			step4 = true;
			step8 = true;
			drive->getEncoder(true, true)->Reset();
			drive->getEncoder(true, false)->Reset();
			drive->getEncoder(false, true)->Reset();
			drive->getEncoder(false, false)->Reset();

		}
	}

	if (step8)
	{
		if (getTurnAverage() < 200 - LIFT_DEADZONE)
			drive->drive(0, .3, 0);
		else if (getTurnAverage() > 200 + LIFT_DEADZONE)
			drive->drive(0, -.3, 0);
		else
		{
			drive->drive(0,0,0);
			drive->getEncoder(true, true)->Reset();
			drive->getEncoder(true, false)->Reset();
			drive->getEncoder(false, true)->Reset();
			drive->getEncoder(false, false)->Reset();
			step9 = true;
		}
	}

	if (step9)
	{
		if (getForwardAverage() < 100 - LIFT_DEADZONE)
			drive->drive(.1, 0, 0);
		else if (getForwardAverage() > 100 - LIFT_DEADZONE)
			drive->drive(-.1, 0, 0);
		else
		{
			drive->drive(0, 0, 0);
			drive->getEncoder(true, true)->Reset();
			drive->getEncoder(true, false)->Reset();
			drive->getEncoder(false, true)->Reset();
			drive->getEncoder(false, false)->Reset();
	}
}

void HematologistAutonomous::getThreeTotes()
{
	getTwoTotes();
	/*
	 * continue logic of the previous totes.
	 * */
}



int HematologistAutonomous::getStrafeAverage()
{
	return abs(drive->getEncoder(true, true)->Get() + drive->getEncoder(false, false)->Get() - drive->getEncoder(true, false)->Get() - drive->getEncoder(false, true)->Get())/4;
	
}
int HematologistAutonomous::getTurnAverage()
{
	return abs(drive->getEncoder(true, true)->Get() + drive->getEncoder(false, true)->Get() - drive->getEncoder(true, false)->Get() - drive->getEncoder(false, false)->Get())/4;
}
int HematologistAutonomous::getForwardAverage()
{
	return (drive->getEncoder(true, true)->Get() + drive->getEncoder(false, true)->Get() - drive->getEncoder(true, false)->Get() - drive->getEncoder(false, false)->Get())/4;
}
