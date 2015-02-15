#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip)
{
	this->drive = drive;
	this->manip = manip;
}

HematologistAutonomous::~HematologistAutonomous(){
	delete drive;
	delete manip;

	drive = NULL;
	manip = NULL;
}

/*
void HematologistAutonomous::graberAutomomous()
{
	while(drive->backLeftEncoder->Get() < 1840)
	{
		if(drive->backLeftEncoder->Get() < 1840)
		{
			drive->drive(0.3,0,0);
		}
		if(drive->backLeftEncoder->Get() < 1840)
		{
			//activate solenoid
		}
		if(drive->backLeftEncoder->Get() < 1840)
		{
			//deactivate solenoid
		}
		if(drive->backLeftEncoder->Get() < 1840)
		{
			drive->drive(-0.3,0,0);
		}
	}
}


void HematologistAutonomous::firstHemanAuto()
{
	while(encoderAverage() < 1840) //actual value is 1089.05
	{
		if(encoderAverage() < 1800)
		{
			drive->drive(0, 0, 0.1);
		}
		else
		{
			drive->drive(0, 0, -0.1);
		}
	}
	drive->drive(0, 0, 0);
}

int HematologistAutonomous::encoderAverage()
{
	int distance;
	distance = (drive->getEncoder(true, true)->Get() + drive->getEncoder(true, false)->Get() + drive->getEncoder(false, true)->Get() + drive->getEncoder(false, false)->Get()) / 4;
	return distance;
}

void HematologistAutonomous::secondHemanAuto()
{
	drive->getEncoder(true, true)->Reset(); 
	drive->getEncoder(true, false)->Reset(); 
	drive->getEncoder(false, true)->Reset(); 
	drive->getEncoder(false, false)->Reset();


	while(encoderAverage() < 1090) //exact value is 1089.05
	{
	//initial drive
		if(encoderAverage() < 700) 
		{
			drive->drive(-0.3, 0 , 0);
		}
		if(encoderAverage() > 360 && encoderAverage() < 380) 
		{
			//manip->openForkLift(false);
		}
		if(encoderAverage() > 380 && encoderAverage() < 390)
		{
			//manip->moveLift(0.7); // first parameter means to move up, second go down, third the motor speed.
		}
		if(encoderAverage() > 390 && encoderAverage() < 400)
		{
			//manip->openForkLift(true);
		}
		if(encoderAverage() > 400 && encoderAverage() < 405)
		{	
			//manip->openSecondTier(false);
		}	
		if(encoderAverage() < 405 && encoderAverage() < 425)
		{	
			//manip->moveLift(-0.7);
		}
		if(encoderAverage() < 427)
		{
			//manip->moveLift(0);
		}
		if(encoderAverage() >700 )
		{
			drive->drive(0, 0.1, 0);
		}
// stop everything?
	}	
	//second tote
	drive->getEncoder(true, true)->Reset(); 
	drive->getEncoder(true, false)->Reset(); 
	drive->getEncoder(false, true)->Reset(); 
	drive->getEncoder(false, false)->Reset();
	while(encoderAverage() < 540)
	{
		if(encoderAverage() <520)
		{
			drive->drive(0.05, 0, 0);
		}	
		if(encoderAverage() < 250 && encoderAverage() > 260)
		{
			//manip->openForkLift(false);
		}		
		if(encoderAverage() > 520)
		{
			drive->drive(0, 0.01, 0);
		}
	}
	//drop off
	drive->getEncoder(true, true)->Reset(); 
	drive->getEncoder(true, false)->Reset(); 
	drive->getEncoder(false, true)->Reset(); 
	drive->getEncoder(false, false)->Reset();
	while(encoderAverage() < 1840) //exact value is 1836.54
	{
		if(encoderAverage() < 670)
		{
			drive->drive(-0.05, 0, 0);
		}	
		if(encoderAverage() > 400 && encoderAverage() > 450)
		{
			//manip->moveLift(0.7);
		}	
		if(encoderAverage() > 450 && encoderAverage() < 460)
		{
			//manip->openForkLift(true);
		}	
		if(encoderAverage() > 465 && encoderAverage() < 470)
		{
			//manip->openSecondTier(false);
		}	
		if(encoderAverage() > 470 && encoderAverage() < 490)
		{
			//manip->moveLift(-0.7);
		}					
		if(encoderAverage() > 510 && encoderAverage() < 530)
		{
			//manip->moveLift(0.7);	
		}	
		if(encoderAverage() > 530 && encoderAverage() < 540)
		{
			//manip->openSeocndTier(true);
		}
		if(encoderAverage() > 670 && encoderAverage() < 690)
		{
			//manip->moveLift(-0.7);	
		}
		if(encoderAverage() > 690)
		{
			//manip->moveLift(false, false, 0);	
		}
		if(encoderAverage() < 690)
		{
			drive->drive(-0.1, 0, 0);
		}
		if(encoderAverage() > 719)
		{
			drive->drive(0, 0, 0);
		}
	}	
}
/*
void HematologistAutonomous::thirdHemanAuto()
{
	// all encoders are drive encoders
	//manip->openForkLift(true);
	//manip->openScondTier(true);

	//first tote
	frontRightEnc->Reset();

	while(he->getEncoder()->getRate() < 1090)
	{
		//initial drive
		if(he->getEncoder()->getRate() < 700)
		{
			drive->drive(0.05, 0 , 0);
		}
		if(he->getEncoder()->getRate() > 360 && he->getEncoder()->getRate() < 380) 
		{
			//manip->openForkLift(false);
		}	
		if(he->getEncoder()->getRate() > 380 && he->getEncoder()->getRate() < 390)
		{
			//manip->moveLift(0.7); // first parameter means to move up, second go down, third the motor speed.
		}
		if(he->getEncoder()->getRate() > 390 && he->getEncoder()->getRate() < 400)
		{
			//manip->openForkLift(true);
		}
		if(he->getEncoder()->getRate() > 400 && he->getEncoder()->getRate() < 405)
		{	
			//manip->openSecondTier(false);
		}	
		if(he->getEncoder()->getRate() < 405 && he->getEncoder()->getRate() < 425)
		{	
			//manip->moveLift(-0.7);
		}
		if(he->getEncoder()->getRate() < 427)
		{
			//manip->moveLift(false, false, 0);
		}
		if(he->getEncoder()->getRate() >700 )
		{
			drive->drive(0, 0.1, 0);
		}
	}	
	//second tote
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 1482) // original value is 1480.74
	{
		if(he->getEncoder()->getRate() < 700)
		{
			drive->drive(0.05, 0 , 0);
		}
		if(he->getEncoder()->getRate() > 360 && he->getEncoder()->getRate() < 380) 
		{
			//manip->openForkLift(false);
		}	
		if(he->getEncoder()->getRate() > 380 && he->getEncoder()->getRate() < 390)
		{
			//manip->moveLift(0.7); // first parameter means to move up, second go down, third the motor speed.
		}
		if(he->getEncoder()->getRate() > 390 && he->getEncoder()->getRate() < 400)
		{
			//manip->openForkLift(true);
		}
		if(he->getEncoder()->getRate() > 400 && he->getEncoder()->getRate() < 405)
		{	
			//manip->openSecondTier(false);
		}	
		if(he->getEncoder()->getRate() < 405 && he->getEncoder()->getRate() < 425)
		{	
			//manip->moveLift(-0.7);
		}
		if(he->getEncoder()->getRate() < 427)
		{
			//manip->moveLift(false, false, 0);
		}
		if(he->getEncoder()->getRate() >700 )
		{
			drive->drive(0, 0.1, 0);
		}
	}
	//third tote; the turn would be to the left since it will drive backward
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 970) // original value is 968.80
	{
		if(he->getEncoder()->getRate() <520)
		{
			drive->drive(0.05, 0, 0);
		}	
		if(he->getEncoder()->getRate() < 250 && he->getEncoder()->getRate() > 260)
		{
			//manip->openForkLift(false);
		}		
		if(he->getEncoder()->getRate() > 520)
		{
			drive->drive(0, -0.01, 0);
		}
	}
	//drop off
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 1838) // original value is 1836.54
	{
		if(he->getEncoder()->getRate() < 670)
		{
			drive->drive(-0.05, 0, 0);
		}	
		if(he->getEncoder()->getRate() > 400 && he->getEncoder()->getRate() > 450)
		{
			//manip->moveLift(0.7);
		}	
		if(he->getEncoder()->getRate() > 450 && he->getEncoder()->getRate() < 460)
		{
			//manip->openForkLift(true);
		}	
		if(he->getEncoder()->getRate() > 465 && he->getEncoder()->getRate() < 470)
		{
			//manip->openSecondTier(false);
		}	
		if(he->getEncoder()->getRate() > 470 && he->getEncoder()->getRate() < 490)
		{
			//manip->moveLift(-0.7);
		}					
		if(he->getEncoder()->getRate() > 510 && he->getEncoder()->getRate() < 530)
		{
			//manip->moveLift(0.7);	
		}	
		if(he->getEncoder()->getRate() > 530 && he->getEncoder()->getRate() < 540)
		{
			//manip->openSeocndTier(true);
		}
		if(he->getEncoder()->getRate() > 670 && he->getEncoder()->getRate() < 690)
		{
			//manip->moveLift(-0.7);	
		}
		if(he->getEncoder()->getRate() > 690)
		{
			//manip->moveLift(0);	
		}
		if(he->getEncoder()->getRate() < 690)
		{
			drive->drive(-0.1, 0, 0);
		}
		if(he->getEncoder()->getRate() > 719)
		{
			drive->drive(0, 0, 0);
		}
	}	
}
//was third autonomous
//manip->openSeocndTier(true); // true opens the grabber
//manip->openForkLift(true); // true opens the grabber
while(/*encoder value is less than certain value tbd) 
{
	drive->drive(0.05, 0 , 0);
	if(/*encoder value is greater than value tbd & encoder value is less than value tbd) 
	{
		//manip->openForkLift(false);
		//manip->moveLift(true, false, 0.7); // first parameter means to move up, seoncd go down, third the motor speed.
	}
	else
	{
		//manip->openForkLift(true);
		//manip->openSecondTier(false);
		//manip->moveLift(false, true, 0.7);
	}
}
//got first tote
while(/*encoder value is less than certain value tbd)
{
	//manip->moveLift(false, false, 0);
	drive->drive(0, 0, 0.1);
}
//first turn 
while(/*encoder value is less than certain value tbd)
{
	drive->drive(0.05, 0, 0);
	if(/*encoder value is greater than value tbd & encoder value is less than value tbd)
	{
		//manip->openForkLift(false);
		//manip->moveLift(true, false, 0.7);
		//manip->openSeocndTier(true);
	}
	else
	{
		//manip->openForkLift(true);
		//manip->openSecondTier(false);
		//manip->moveLift(false, true, 0.7);
	}
}
//picked up second tote
while(/*encoder value is less than certain value tbd)
{
	//manip->moveLift(false, false, 0);
	drive->drive(0, 0, -0.1);
}
//second turn
while(/*encoder value is less than certain value tbd)
{
	drive->drive(0.05, 0, 0);
	if(/*encoder value is greater than value tbd & encoder value is less than value tbd)
	{
		//manip->openForkLift(false);
		//manip->moveLift(true, false, 0.7);
	}
	else
	{
		//manip->openForkLift(true);
		//manip->openSecondTier(false);
		//manip->moveLift(false, true, 0.7);
	}
}
//picked up third tote
while(/*encoder value is less than certain value tbd)
{
	//manip->moveLift(false, false, 0);
	drive->drive(0, 0, -0.01);
}
//third turn(last turn) turning left and go bakcward
while(/*encoder value is less than certain value tbd)
{
	drive->drive(-0.05, 0, 0);
	drive->drive(0, 0, 0);
	//manip->moveLift(true, false, 0.7);
	//manip->openSeocndTier(true);
	//manip->moveLift(false, true, 0.7);
	//manip->moveLift(false, false, 0);
	drive->drive(-0.1, 0, 0);
}
//drive backward
while(/*encoder value is less than certain value tbd)
{
	drive->drive(0, 0, 0);
	while(/*encoder value is less than certain value tbd)
	{
		//manip->moveLift(true, false, 0.7);
	}
	
	//manip->openSeocndTier(true);

	while(/*encoder value is less than certain value tbd)
	{
		//manip->moveLift(false, true, 0.7);
	}

	if(/*encoder value is less than certain value tbd)
	{
		//manip->moveLift(false, false, 0);
		drive->drive(-0.1, 0, 0);
	}
}
drive->drive(0, 0, 0);	
*/

void HematologistAutonomous::strafeRight()
{
	drive->drive(0, 0, .4);
	Wait(.3);
	drive->drive(0, 0, 0);
}

void HematologistAutonomous::getTwoTotes()
{
	drive->getEncoder(true, true)->Reset();
	drive->getEncoder(true, false)->Reset();
	drive->getEncoder(false, true)->Reset();
	drive->getEncoder(false, false)->Reset();

	/*
	 * move forward up to bin
	 * close forklift
	 * start moving forward
	 * raise forklift
	 * close second tier at appropriate time
	 * hit poit where you are to turn
	 * reset encoders
	 * turn as necessary using encoders
	 * put forklift down all the way down to hit limit switch - move forward when done turning
	 * Be at the second tote
	 * repeat process
	 *
	 */
}

void HematologistAutonomous::getThreeTotes()
{
	getTwoTotes();
	/*
	 * continue logic of the previous totes.
	 * */
}


