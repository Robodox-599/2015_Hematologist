#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip, HematologistOperatorInterface* oi)
{
	this->drive = drive;
	this->manip = manip;
	this->oi = oi;
	step1 	= true;	
	step2 	= false;	//this step will not start, must be told when to
	step3 	= false;	//this step will not start, must be told when to
	step4 	= false;	//this step will not start, must be told when to
	step5 	= false;	//this step will not start, must be told when to
	step6 	= false;	//this step will not start, must be told when to
	step7 	= false;	//this step will not start, must be told when to
	step8 	= false;	//this step will not start, must be told when to
	step9 	= false;	//this step will not start, must be told when to
	step10	= false;	//this step will not start, must be told when to	
	step11	= false;	//this step will not start, must be told when to	
	step12	= false;	//this step will not start, must be told when to	
	step13	= false;	//this step will not start, must be told when to	
	step14	= false;	//this step will not start, must be told when to	
	step15	= false;	//this step will not start, must be told when to	
	step16	= false;	//this step will not start, must be told when to	
	step17	= false;	//this step will not start, must be told when to	
	step18	= false;	//this step will not start, must be told when to		
}

HematologistAutonomous::~HematologistAutonomous(){
	delete drive;
	delete manip;

	drive = NULL;
	manip = NULL;
}

void HematologistAutonomous::strafeRight()
{
	oi->getDashboard()->PutBoolean("Step1", step1);
	oi->getDashboard()->PutBoolean("Step2", step2);
	oi->getDashboard()->PutBoolean("Step3", step3);
	oi->getDashboard()->PutNumber("Strafe Avg Auto:", getStrafeAverage());


	if (step1)
	{
		step1 = false;
		step2 = false;
		step3 = true;
		drive->getEncoder(true, true)->Reset();
		drive->getEncoder(true, false)->Reset();
		drive->getEncoder(false, true)->Reset();
		drive->getEncoder(false, false)->Reset();
		manip->getLiftEncoder()->Reset();
		manip->closePiston(false, true);
		manip->closePiston(true, true);
	}
	if (step2)
	{
		//strafe left
#if 1
		if (getStrafeAverage() < 2000 - LIFT_DEADZONE)
			drive->drive(0, 0, -.8);
		else if (getStrafeAverage() > 2000 + LIFT_DEADZONE)
			drive->drive(0, 0, .8);
		else
		{
			drive->drive(0, 0, 0);
			step2 = false;
		}
#endif
		//strafe right
#if 0
		if (getStrafeAverage() < 2000 - LIFT_DEADZONE)
			drive->drive(0, 0, .6);
		else if (getStrafeAverage() > 2000 + LIFT_DEADZONE)
			drive->drive(0, 0, -.6);
		else
		{
			drive->drive(0, 0, 0);
			step2 = false;
		}
#endif


	}
	if (step3)
	{
		if (manip->getLiftEncoder()->Get() < 750 - LIFT_DEADZONE)
		{
			manip->moveLift(-.5);
		}else
		{
			if (manip->getLiftEncoder()->Get() > 750 + LIFT_DEADZONE)
				manip->moveLift(.5);
			else{
				manip->moveLift(0);
				step3 = false;
				step2 = true;
			}
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
			drive->drive(.5,0,0);
		else if (getForwardAverage() > 20 + LIFT_DEADZONE)
			drive->drive(-.5, 0, 0);
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
			drive->drive(.5, 0, 0);
		else if (getForwardAverage() > 100 + LIFT_DEADZONE)
			drive->drive(-.5, 0, 0);
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
			manip->moveLift(.2);
		else if (manip->getLiftEncoder()->Get() > 30 + LIFT_DEADZONE)
			manip->moveLift(-.2);
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
			drive->drive(0, .5, 0);
		else if (getTurnAverage() > 100 + LIFT_DEADZONE)
			drive->drive(0, -.5, 0);
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
			manip->moveLift(-.3);
		}else
		{
			manip->moveLift(0);
			manip->openPiston(true, true);
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
			drive->drive(.5, 0, 0);
		else if (getForwardAverage() > 100 - LIFT_DEADZONE)
			drive->drive(-.5, 0, 0);
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
			drive->drive(0, .5, 0);
		else if (getTurnAverage() > 200 + LIFT_DEADZONE)
			drive->drive(0, -.5, 0);
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
			drive->drive(.5, 0, 0);
		else if (getForwardAverage() > 100 - LIFT_DEADZONE)
			drive->drive(-.5, 0, 0);
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
			manip->openPiston(true, true);
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
		turn to align to third tote
		reset encoders, stop motors
	*/
	if(step8)
	{
		if (getTurnAverage() < 100 - LIFT_DEADZONE)
			drive->drive(0, .1, 0);
		else if (getTurnAverage() > 100 + LIFT_DEADZONE)
			drive->drive(0, -.1, 0);
		else
		{
			step8 = false;
			drive->drive(0, 0, 0);
			drive->getEncoder(true, true)->Reset();
			drive->getEncoder(true, false)->Reset();
			drive->getEncoder(false, true)->Reset();
			drive->getEncoder(false, false)->Reset();
			step9 = true;
		}
	}
	/*
	step9
		move towrard third tote
		when there, close piston
		reset encoders, start 4
	*/
	if (step9)
	{
		if (getForwardAverage() < 100 - LIFT_DEADZONE)
			drive->drive(.1, 0, 0);
		else if (getForwardAverage() > 100 + LIFT_DEADZONE)
			drive->drive(-.1, 0, 0);
		else
		{
			step9 = false;
			drive->drive(0, 0, 0);
			manip->closePiston(true, true);
			step4 = true;
			step10 = true;
		}
	}
	/*
	step10
		turn to move to loading zone
		stop, reset encoders
	*/
	if (step10)
	{
		if (getTurnAverage() < 100 - LIFT_DEADZONE)
			drive->drive(.1, 0, 0);
		else if (getTurnAverage() > 100 + LIFT_DEADZONE)
			drive->drive(-.1, 0, 0);
		else 
		{
			step10 = false;
			drive->drive(0, 0, 0);
			step11 = true;
		}
	}
	if (step11)
	{
		if (getForwardAverage() < 100 - LIFT_DEADZONE)
			drive->drive(.1, 0, 0);
		else if (getForwardAverage() > 100 - LIFT_DEADZONE)
			drive->drive(-.1, 0, 0);
		else
		{
			step11 = false;
			drive->drive(0, 0, 0);
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
	return (drive->getEncoder(true, true)->Get() + drive->getEncoder(false, true)->Get() + drive->getEncoder(true, false)->Get() + drive->getEncoder(false, false)->Get())/4;
}
