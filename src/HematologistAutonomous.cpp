#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip)
{
	frontLeftEnc = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	frontRightEnc = new Encoder(3, 4, true, Encoder::EncodingType::k4X);
	backLeftEnc = new Encoder(5, 6, false, Encoder::EncodingType::k4X);
	backRightEnc = new Encoder(7, 8, true, Encoder::EncodingType::k4X);

	frontLeftEnc->SetMaxPeriod(1);
	frontLeftEnc->SetMinRate(10);
	frontLeftEnc->SetDistancePerPulse(5);
	frontLeftEnc->SetSamplesToAverage(7);

	frontRightEnc->SetMaxPeriod(1);
	frontRightEnc->SetMinRate(10);
	frontRightEnc->SetDistancePerPulse(5);
	frontRightEnc->SetSamplesToAverage(7);

	backLeftEnc->SetMaxPeriod(1);
	backLeftEnc->SetMinRate(10);
	backLeftEnc->SetDistancePerPulse(5);
	backLeftEnc->SetSamplesToAverage(7);

	backRightEnc->SetMaxPeriod(1);
	backRightEnc->SetMinRate(10);
	backRightEnc->SetDistancePerPulse(5);
	backRightEnc->SetSamplesToAverage(7);
}

HematologistAutonomous::~HematologistAutonomous()
{
	delete frontLeftEnc;
	delete frontRightEnc;
	delete backLeftEnc;
	delete backRightEnc;

	frontLeftEnc = NULL;
	frontRightEnc = NULL;
	backLeftEnc = NULL;
	backRightEnc = NULL;
}

void HematologistAutonomous::thirdHemanAuto()
{
	// all encoders are drive encoders

	//first tote
	frontRightEnc->Reset();
	while()
	{
		//initial drive
		if(encoder value is less than certain value tbd)
		{
			drive->drive(0.05, 0 , 0);
		}
		if(encoder value is between certain value tbd) 
		{
			manip->openForklLift(false);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(true, false, 0.7); // first parameter means to move up, second go down, third the motor speed.
		}
		if(encoder value is between certain value tbd)
		{
			manip->openForklLift(true);
		}
		if(encoder value is between certain value tbd)
		{	
			manip->openSecondTier(false);
		}	
		if(encoder value is between certain value tbd)
		{	
			manip->moveLift(false, true, 0.7);
		}
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(false, false, 0);
		}
		if(encoder value is between certain value tbd)
		{
			drive->drive(0, 0, 0.1);
		}
	}	
	//second tote
	frontRightEnc->Reset();
	while()
	{
		if(encoder value is between certain value tbd)
		{
			drive->drive(0.05, 0, 0);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->openForklLift(false);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(true, false, 0.7);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->openForklLift(true);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->openSecondTier(false);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(false, true, 0.7);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(false, false, 0);
		}	
		if(encoder value is between certain value tbd)
		{
			drive->drive(0, 0, -0.01);
		}
	}	
	//third tote; the turn would be to the left since it will drive backward
	frontRightEnc->Reset();
	while()
	{	
		if(encoder value is between certain value tbd)
		{
			drive->drive(0.05, 0, 0);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->openForklLift(false);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(true, false, 0.7);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->openForklLift(true);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->openSecondTier(false);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(false, true, 0.7);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(false, false, 0);
		}	
		if(encoder value is between certain value tbd)
		{
			drive->drive(0, 0, -0.01);
		}
	}
	//drop off
	frontRightEnc->Reset();
	while()
	{				
		if(encoder value is between certain value tbd)
		{
			drive->drive(-0.05, 0, 0);
		}	
		if(encoder value is between certain value tbd)
		{
			drive->drive(0, 0, 0);
		}	
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(true, false, 0.7);	
		}	
		if(encoder value is between certain value tbd)
		{
			manip->openSeocndTier(true);
		}
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(false, true, 0.7);	
		}
		if(encoder value is between certain value tbd)
		{
			manip->moveLift(false, false, 0);	
		}
		if(encoder value is between certain value tbd)
		{
			drive->drive(-0.1, 0, 0);
		}	
	}
}
//was third autonomous
/*manip->openSeocndTier(true); // true opens the grabber
manip->openForklLift(true); // true opens the grabber
while(/*encoder value is less than certain value tbd) 
{
	drive->drive(0.05, 0 , 0);
	if(/*encoder value is greater than value tbd & encoder value is less than value tbd) 
	{
		manip->openForklLift(false);
		manip->moveLift(true, false, 0.7); // first parameter means to move up, seoncd go down, third the motor speed.
	}
	else
	{
		manip->openForklLift(true);
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
		manip->openForklLift(false);
		manip->moveLift(true, false, 0.7);
		manip->openSeocndTier(true);
	}
	else
	{
		manip->openForklLift(true);
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
		manip->openForklLift(false);
		manip->moveLift(true, false, 0.7);
	}
	else
	{
		manip->openForklLift(true);
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