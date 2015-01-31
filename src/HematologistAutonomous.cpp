#include "HematologistAutonomous.h"

HematologistAutonomous::HematologistAutonomous()
{
	man = new HematologistManipulator();
	drive = new HematologistDrive();

	averageEncVal = 0;

	frontLeftEnc = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	frontRightEnc = new Encoder(3, 4, true, Encoder::EncodingType::k4X);
	backLeftEnc = new Encoder(5, 6, false, Encoder::EncodingType::k4X);
	backRightEnc = new Encoder(7, 8, true, Encoder::EncodingType::k4X);

	frontLeftEnc->Encoder::SetMaxPeriod(1);
	frontLeftEnc->Encoder::SetMinRate(10);
	frontLeftEnc->Encoder::SetDistancePerPulse(5);
	frontLeftEnc->Encoder::SetReverseDirection(true);
	frontLeftEnc->Encoder::SetSamplesToAverage(7);

	frontRightEnc->Encoder::SetMaxPeriod(1);
	frontRightEnc->Encoder::SetMinRate(10);
	frontRightEnc->Encoder::SetDistancePerPulse(5);
	frontRightEnc->Encoder::SetReverseDirection(true);
	frontRightEnc->Encoder::SetSamplesToAverage(7);

	backLeftEnc->Encoder::SetMaxPeriod(1);
	backLeftEnc->Encoder::SetMinRate(10);
	backLeftEnc->Encoder::SetDistancePerPulse(5);
	backLeftEnc->Encoder::SetReverseDirection(true);
	backLeftEnc->Encoder::SetSamplesToAverage(7);

	backRightEnc->Encoder::SetMaxPeriod(1);
	backRightEnc->Encoder::SetMinRate(10);
	backRightEnc->Encoder::SetDistancePerPulse(5);
	backRightEnc->Encoder::SetReverseDirection(true);
	backRightEnc->Encoder::SetSamplesToAverage(7);
}

HematologistAutonomous::~HematologistAutonomous()
{

}

void HematologistAutonomous::secondHemanAuto()
{
	frontLeftEnc->Encoder::Reset();
	frontRightEnc->Encoder::Reset();
	backLeftEnc->Encoder::Reset();
	backRightEnc->Encoder::Reset();
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
	}
}

void HematologistAutonomous::setAverageEncVal()
{
	(frontLeftEnc-> Get() + frontRightEnc-> Get() + backLeftEnc-> Get() + backRightEnc-> Get()) / 4 = averageEncVal;
}
