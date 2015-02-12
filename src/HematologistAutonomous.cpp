#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip){}

HematologistAutonomous::~HematologistAutonomous(){}

void HematologistAutonomous::firstHemanAuto()
{
	while(he->getEncoder()->getRate() < 360)
	{
		if(he->getEncoder()->getRate() < 300)
		{
			drive(0, 0, 0.1);
		}
		else
		{
			drive(0, 0, -0.1);
		}
	}
	drive(0, 0, 0);
}

void HematologistAutonomous::secondHemanAuto()
{
	manip->openForkLift(true);
	manip->openScondTier(true);

	frontRightEnc->Reset();
	rearRightEnc->Reset();
	frontLeftEnc->Reset();
	rearLeftEnc->Reset();

	while(he->getEncoder()->getRate() < 720)
	{
	//initial drive
		if(he->getEncoder()->getRate() < 700) 
		{
			drive->drive(0.05, 0 , 0);
		}
		if(he->getEncoder()->getRate() > 360 && he->getEncoder()->getRate() < 380) 
		{
			manip->openForkLift(false);
		}
		if(he->getEncoder()->getRate() > 380 && he->getEncoder()->getRate() < 390)
		{
			manip->moveLift(0.7); // first parameter means to move up, second go down, third the motor speed.
		}
		if(he->getEncoder()->getRate() > 390 && he->getEncoder()->getRate() < 400)
		{
			manip->openForkLift(true);
		}
		if(he->getEncoder()->getRate() > 400 && he->getEncoder()->getRate() < 405)
		{	
			manip->openSecondTier(false);
		}	
		if(he->getEncoder()->getRate() < 405 && he->getEncoder()->getRate() < 425)
		{	
			manip->moveLift(-0.7);
		}
		if(he->getEncoder()->getRate() < 427)
		{
			manip->moveLift(0);
		}
		if(he->getEncoder()->getRate() >700 )
		{
			drive->drive(0, 0.1, 0);
		}
// stop everything?
	}	
	//second tote
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 540)
	{
		if(he->getEncoder()->getRate() <520)
		{
			drive->drive(0.05, 0, 0);
		}	
		if(he->getEncoder()->getRate() < 250 && he->getEncoder()->getRate() > 260)
		{
			manip->openForkLift(false);
		}		
		if(he->getEncoder()->getRate() > 520)
		{
			drive->drive(0, 0.01, 0);
		}
	}
	//drop off
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 720)
	{
		if(he->getEncoder()->getRate() < 670)
		{
			drive->drive(-0.05, 0, 0);
		}	
		if(he->getEncoder()->getRate() > 400 && he->getEncoder()->getRate() > 450)
		{
			manip->moveLift(0.7);
		}	
		if(he->getEncoder()->getRate() > 450 && he->getEncoder()->getRate() < 460)
		{
			manip->openForkLift(true);
		}	
		if(he->getEncoder()->getRate() > 465 && he->getEncoder()->getRate() < 470)
		{
			manip->openSecondTier(false);
		}	
		if(he->getEncoder()->getRate() > 470 && he->getEncoder()->getRate() < 490)
		{
			manip->moveLift(-0.7);
		}					
		if(he->getEncoder()->getRate() > 510 && he->getEncoder()->getRate() < 530)
		{
			manip->moveLift(0.7);	
		}	
		if(he->getEncoder()->getRate() > 530 && he->getEncoder()->getRate() < 540)
		{
			manip->openSeocndTier(true);
		}
		if(he->getEncoder()->getRate() > 670 && he->getEncoder()->getRate() < 690)
		{
			manip->moveLift(-0.7);	
		}
		if(he->getEncoder()->getRate() > 690)
		{
			manip->moveLift(false, false, 0);	
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

void HematologistAutonomous::thirdHemanAuto()
{
	// all encoders are drive encoders
	manip->openForkLift(true);
	manip->openScondTier(true);

	//first tote
	frontRightEnc->Reset();

	while(he->getEncoder()->getRate() < 720)
	{
		//initial drive
		if(he->getEncoder()->getRate() < 700)
		{
			drive->drive(0.05, 0 , 0);
		}
		if(he->getEncoder()->getRate() > 360 && he->getEncoder()->getRate() < 380) 
		{
			manip->openForkLift(false);
		}	
		if(he->getEncoder()->getRate() > 380 && he->getEncoder()->getRate() < 390)
		{
			manip->moveLift(0.7); // first parameter means to move up, second go down, third the motor speed.
		}
		if(he->getEncoder()->getRate() > 390 && he->getEncoder()->getRate() < 400)
		{
			manip->openForkLift(true);
		}
		if(he->getEncoder()->getRate() > 400 && he->getEncoder()->getRate() < 405)
		{	
			manip->openSecondTier(false);
		}	
		if(he->getEncoder()->getRate() < 405 && he->getEncoder()->getRate() < 425)
		{	
			manip->moveLift(-0.7);
		}
		if(he->getEncoder()->getRate() < 427)
		{
			manip->moveLift(false, false, 0);
		}
		if(he->getEncoder()->getRate() >700 )
		{
			drive->drive(0, 0.1, 0);
		}
	}	
	//second tote
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 540)
	{
		if(he->getEncoder()->getRate() <520)
		{
			drive->drive(0.05, 0, 0);
		}	
		if(he->getEncoder()->getRate() < 250 && he->getEncoder()->getRate() > 260)
		{
			manip->openForkLift(false);
		}		
		if(he->getEncoder()->getRate() > 520)
		{
			drive->drive(0, 0.01, 0);
		}
	}
	//third tote; the turn would be to the left since it will drive backward
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 540)
	{
		if(he->getEncoder()->getRate() <520)
		{
			drive->drive(0.05, 0, 0);
		}	
		if(he->getEncoder()->getRate() < 250 && he->getEncoder()->getRate() > 260)
		{
			manip->openForkLift(false);
		}		
		if(he->getEncoder()->getRate() > 520)
		{
			drive->drive(0, -0.01, 0);
		}
	}
	//drop off
	frontRightEnc->Reset();
	while(he->getEncoder()->getRate() < 720)
	{
		if(he->getEncoder()->getRate() < 670)
		{
			drive->drive(-0.05, 0, 0);
		}	
		if(he->getEncoder()->getRate() > 400 && he->getEncoder()->getRate() > 450)
		{
			manip->moveLift(0.7);
		}	
		if(he->getEncoder()->getRate() > 450 && he->getEncoder()->getRate() < 460)
		{
			manip->openForkLift(true);
		}	
		if(he->getEncoder()->getRate() > 465 && he->getEncoder()->getRate() < 470)
		{
			manip->openSecondTier(false);
		}	
		if(he->getEncoder()->getRate() > 470 && he->getEncoder()->getRate() < 490)
		{
			manip->moveLift(-0.7);
		}					
		if(he->getEncoder()->getRate() > 510 && he->getEncoder()->getRate() < 530)
		{
			manip->moveLift(0.7);	
		}	
		if(he->getEncoder()->getRate() > 530 && he->getEncoder()->getRate() < 540)
		{
			manip->openSeocndTier(true);
		}
		if(he->getEncoder()->getRate() > 670 && he->getEncoder()->getRate() < 690)
		{
			manip->moveLift(-0.7);	
		}
		if(he->getEncoder()->getRate() > 690)
		{
			manip->moveLift(0);	
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
/*manip->openSeocndTier(true); // true opens the grabber
manip->openForkLift(true); // true opens the grabber
while(/*encoder value is less than certain value tbd) 
{
	drive->drive(0.05, 0 , 0);
	if(/*encoder value is greater than value tbd & encoder value is less than value tbd) 
	{
		manip->openForkLift(false);
		manip->moveLift(true, false, 0.7); // first parameter means to move up, seoncd go down, third the motor speed.
	}
	else
	{
		manip->openForkLift(true);
		manip->openSecondTier(false);
		manip->moveLift(false, true, 0.7);
	}
}
//got first tote
while(/*encoder value is less than certain value tbd)
{
	manip->moveLift(false, false, 0);
	drive->drive(0, 0, 0.1);
}
//first turn 
while(/*encoder value is less than certain value tbd)
{
	drive->drive(0.05, 0, 0);
	if(/*encoder value is greater than value tbd & encoder value is less than value tbd)
	{
		manip->openForkLift(false);
		manip->moveLift(true, false, 0.7);
		manip->openSeocndTier(true);
	}
	else
	{
		manip->openForkLift(true);
		manip->openSecondTier(false);
		manip->moveLift(false, true, 0.7);
	}
}
//picked up second tote
while(/*encoder value is less than certain value tbd)
{
	manip->moveLift(false, false, 0);
	drive->drive(0, 0, -0.1);
}
//second turn
while(/*encoder value is less than certain value tbd)
{
	drive->drive(0.05, 0, 0);
	if(/*encoder value is greater than value tbd & encoder value is less than value tbd)
	{
		manip->openForkLift(false);
		manip->moveLift(true, false, 0.7);
	}
	else
	{
		manip->openForkLift(true);
		manip->openSecondTier(false);
		manip->moveLift(false, true, 0.7);
	}
}
//picked up third tote
while(/*encoder value is less than certain value tbd)
{
	manip->moveLift(false, false, 0);
	drive->drive(0, 0, -0.01);
}
//third turn(last turn) turning left and go bakcward
while(/*encoder value is less than certain value tbd)
{
	drive->drive(-0.05, 0, 0);
	drive->drive(0, 0, 0);
	manip->moveLift(true, false, 0.7);
	manip->openSeocndTier(true);
	manip->moveLift(false, true, 0.7);
	manip->moveLift(false, false, 0);
	drive->drive(-0.1, 0, 0);
}
//drive backward
while(/*encoder value is less than certain value tbd)
{
	drive->drive(0, 0, 0);
	while(/*encoder value is less than certain value tbd)
	{
		manip->moveLift(true, false, 0.7);
	}
	
	manip->openSeocndTier(true);

	while(/*encoder value is less than certain value tbd)
	{
		manip->moveLift(false, true, 0.7);
	}

	if(/*encoder value is less than certain value tbd)
	{
		manip->moveLift(false, false, 0);
		drive->drive(-0.1, 0, 0);
	}
}
drive->drive(0, 0, 0);	
*/
