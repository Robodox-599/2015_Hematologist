#include "HematologistAutonomous.h"

HematologistAutonomous::HematologistAutonomous()
{
	man = new HematologistManipulator();
	drive = new HematologistDrive();
}

HematologistAutonomous::~HematologistAutonomous()
{

}

void HematologistAutonomous::secondHemanAuto()
{
	man->liftEncoder->Encoder::Reset();
	man->secondTierClawOpen();

	if(man->liftEncoder->Get() < 20)
	{
		drive->frontLeftMotor->Set(.5);
		drive->frontRightMotor->Set(-.5);
		drive->backLeftMotor->Set(.5);
		drive->backRightMotor->Set(-.5);
		//if pressure button is pressed, then activateSecondTier
	}
	else
	{
		if(man->liftEncoder->Get() < 25)
		{
			drive->frontLeftMotor->Set(.5);
			drive->frontRightMotor->Set(.5);
			drive->backLeftMotor->Set(.5);
			drive->backRightMotor->Set(.5);
		}
	}
}
