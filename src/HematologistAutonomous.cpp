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
	step9 = false;	//this step will not start, must be told when to
	step10 = false;	//this step will not start, must be told when to	
	step11 = false;	//this step will not start, must be told when to	
	step12 = false;	//this step will not start, must be told when to	
	step13 = false;	//this step will not start, must be told when to	
	step14 = false;	//this step will not start, must be told when to	
	step15 = false;	//this step will not start, must be told when to	
	step16 = false;	//this step will not start, must be told when to	
	step17 = false;	//this step will not start, must be told when to	
	step18 = false;	//this step will not start, must be told when to		
}
HematologistAutonomous::~HematologistAutonomous(){
	delete drive;
	delete manip;

	drive = NULL;
	manip = NULL;
}

void HematologistAutonomous::strafeRight()
{
	if (step1)
	{
		step1 = false;
		step2 = true;
	}
	if (step2)
	{
		if (getStrafeAverage() < 100 - LIFT_DEADZONE)
			drive->drive(0, 0, .2);
		else if (getStrafeAverage() > 100 + LIFT_DEADZONE)
			drive->drive(0, 0, -.2);
		else
		{
			drive->drive(0, 0, 0);
			step2 = false;
		}
	}
}

void HematologistAutonomous::getTwoTotes()
{
	/*
	step1
		reset encoders
		decide which step to go from there
	*/
	if (step1){
		drive->getEncoder(true, true)->Reset();
		drive->getEncoder(true, false)->Reset();
		drive->getEncoder(false, true)->Reset();
		drive->getEncoder(false, false)->Reset();
		manip->getLiftEncoder()->Reset();
		step1 = false;
		step2 = true;
	}
	/*
	step2
		drive forward up to tote as needed
		close piston when there
		decide on next step
	*/
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
	/*
	step3
		reset drive encoders
		move up to point where in we will turn to get the second tote
		pick next step
		reset drive encoders
	*/
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
	/*
	step4
		move lift up to the point in which second tier pistons will shut
		reset lift encoder
		decide which step
	*/
	if (step4)
	{
		if (manip->getLiftEncoder()->Get() < 30 - LIFT_DEADZONE)
			manip->moveLift(.1);
		else if (manip->getLiftEncoder()->Get() > 30 + LIFT_DEADZONE)
			manip->moveLift(-.1);
		else
		{
			manip->moveLift(0);
			step4 = false;
			manip->getLiftEncoder()->Reset();
			manip->closePiston(false, true);
			step6 = true;
		}
	}
	/*
	step5
		turn until aligned to get to second tote
		stop drive
		reset encoders
		decide next step
	*/
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
	/*
	step6 
		move lift down until limit swich is pressed
		reset encoders, stop motor
	*/
	if (step6)
	{
		if (!manip->getLimitSwitch(false)->limitSwitchIsPressed())
		{
			manip->moveLift(-.1);
		}else
		{
			manip->moveLift(0);
			manip->getLiftEncoder()->Reset();
			step6 = false;
		}
	}
	/*
	step7
		drive until you reach the next tote
		close pistons
		go to step 4 to repeat process with lift
		reset encoders
	*/
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
	/*
	step8
		turn until we're ready to move forward across the bump
		stop drive, reset encoders
	*/
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
			step8 = false;
			step9 = true;
		}
	}
	/*
	step9
		drive across bump
		stop when across
		reset encoders
	*/
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
			step9 = false;
		}
	}
}

void HematologistAutonomous::getThreeTotes()
{
	/*
	step1
		reset encoders
		decide which step to go from there
	*/
	if (step1){
		drive->getEncoder(true, true)->Reset();
		drive->getEncoder(true, false)->Reset();
		drive->getEncoder(false, true)->Reset();
		drive->getEncoder(false, false)->Reset();
		manip->getLiftEncoder()->Reset();
		step1 = false;
		step2 = true;
	}
	/*
	step2
		drive forward up to tote as needed
		close piston when there
		decide on next step
	*/
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
	/*
	step3
		reset drive encoders
		move up to point where in we will turn to get the second tote
		pick next step
		reset drive encoders
	*/
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
	/*
	step4
		move lift up to the point in which second tier pistons will shut
		reset lift encoder
		decide which step
	*/
	if (step4)
	{
		if (manip->getLiftEncoder()->Get() < 30 - LIFT_DEADZONE)
			manip->moveLift(.1);
		else if (manip->getLiftEncoder()->Get() > 30 + LIFT_DEADZONE)
			manip->moveLift(-.1);
		else
		{
			manip->moveLift(0);
			step4 = false;
			manip->getLiftEncoder()->Reset();
			manip->closePiston(false, true);
			step6 = true;
		}
	}
	/*
	step5
		turn until aligned to get to second tote
		stop drive
		reset encoders
		decide next step
	*/
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
	/*
	step6 
		move lift down until limit swich is pressed
		reset encoders, stop motor
	*/
	if (step6)
	{
		if (!manip->getLimitSwitch(false)->limitSwitchIsPressed())
		{
			manip->moveLift(-.1);
		}else
		{
			manip->moveLift(0);
			manip->getLiftEncoder()->Reset();
			step6 = false;
		}
	}
	/*
	step7
		drive until you reach the next tote
		close pistons
		go to step 4 to repeat process with lift
		reset encoders
	*/
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
	/*
	step8
		turn until we're ready to move forward across the bump
		stop drive, reset encoders
	*/
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
			step8 = false;
			step9 = true;
		}
	}
	/*
	step9
		drive across bump
		stop when across
		reset encoders
	*/
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
			step9 = false;
		}
	}
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
