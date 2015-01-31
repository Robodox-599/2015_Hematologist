#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous()
{
	drive = new HematologistDrive();

	averageEncVal = 0;

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
	frontLeftEnc->Reset();
	frontRightEnc->Reset();
	backLeftEnc->Reset();
	backRightEnc->Reset();
	man->secondTierClawOpen();

	if(averageEncVal < 20)
	{
		drive->frontLeftMotor->Set(.5);
		drive->frontRightMotor->Set(-.5);
		drive->backLeftMotor->Set(.5);
		drive->backRightMotor->Set(-.5);
		//if pressure button is pressed, then activateSecondTier
	}
	else
	{
		if(averageEncVal < 25)
		{
			drive->frontLeftMotor->Set(.5);
			drive->frontRightMotor->Set(.5);
			drive->backLeftMotor->Set(.5);
			drive->backRightMotor->Set(.5);
		}
		else
		{
			if(averageEncVal < 30)
			{
				drive->frontLeftMotor->Set(.5);
				drive->frontRightMotor->Set(-.5);
				drive->backLeftMotor->Set(.5);
				drive->backRightMotor->Set(-.5);
				//if pressure button is pressed, then activateSecondTier
			}
			else
			{
				if(averageEncVal < 35)
				{
					drive->frontLeftMotor->Set(.5);
					drive->frontRightMotor->Set(.5);
					drive->backLeftMotor->Set(.5);
					drive->backRightMotor->Set(.5);
				}
				else
				{
					if(averageEncVal < 50)
					{
						drive->frontLeftMotor->Set(.5);
						drive->frontRightMotor->Set(-.5);
						drive->backLeftMotor->Set(.5);
						drive->backRightMotor->Set(-.5);
					}
					else
					{
						drive->frontLeftMotor->Set(0);
						drive->frontRightMotor->Set(0);
						drive->backLeftMotor->Set(0);
						drive->backRightMotor->Set(0);

						frontLeftEnc->Reset();
						frontRightEnc->Reset();
						backLeftEnc->Reset();
						backRightEnc->Reset();
					}
				}
			}
		}
	}
}

void HematologistAutonomous::setAverageEncVal()
{
	(frontLeftEnc-> Get() + frontRightEnc-> Get() + backLeftEnc-> Get() + backRightEnc-> Get()) / 4 = averageEncVal;
}
