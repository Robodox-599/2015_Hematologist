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

void HematologistAutonomous::secondHemanAuto()
{
	while(/*encoder value is less than certain value tbd*/)
	{
		manip->
		drive->drive(0.05, 0 , 0);
		if(/*encoder value is less than certain value tbd*/)
		{
			manip->moveForkLift(true, false, 0.5);
		}
	}

	while(/*encoder value is less than certain value tbd*/)
	{
		drive->drive(0, 0, 0.1);
	}
	
	while(/*encoder value is less than certain value tbd*/)
	{
		drive->drive(0.1, 0, 0);
	}
	
	while(/*encoder value is less than certain value tbd*/)
	{
		drive->drive(0, 0, 0.1);
	}

	while(/*encoder value is less than certain value tbd*/)
	{
		drive->drive(0.1, 0, 0);
	}

	while(/*encoder value is less than certain value tbd*/)
	{
		drive->drive(0, 0, 0);
		manip->secondTierClosed();
		if(/*encoder value is less than certain value tbd*/)
		{
			drive->drive(-0.1, 0, 0);
		}
	}
	drive->drive(0, 0, 0);	
}

