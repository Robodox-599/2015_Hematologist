#include "HematologistDrive.h"
#include "HematologistOperatorInterface.h"
#include "HematologistManipulator.h"

bool autonInit = true;
double autonInitTime = 0;
float angle = 0;

class Hematologist: public IterativeRobot
{
private:
	HematologistDrive *drive;
	HematologistOperatorInterface *oi;
	HematologistManipulator *man;
	LiveWindow *lw;


	void RobotInit()
	{
		drive->gyro->Reset();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
	}

	void TeleopPeriodic()
	{
		if(oi->rightJoystick->GetTrigger()){
			drive->drive();
		} else {
			drive->testDrive();
		}
		oi->dashboard->PutNumber("Gyro Angle: ", drive->gyro->GetAngle());
		oi->dashboard->PutNumber("Gyro Rate: ", drive->gyro->GetRate());
		oi->dashboard->PutNumber("Forward: ", drive->forward);
		oi->dashboard->PutNumber("Side", drive->side);
		oi->dashboard->PutNumber("Spin", drive->spin);
		oi->dashboard->PutNumber("Right Joystick X", oi->rightJoystick->GetX());
		oi->dashboard->PutNumber("Right Joystick Y", oi->rightJoystick->GetY());
		oi->dashboard->PutNumber("Left Joystick X", oi->leftJoystick->GetX());
		oi->dashboard->PutNumber("Left Joystick Y", oi->leftJoystick->GetY());
		oi->dashboard->PutNumber("Timer", drive->timer->Get());
	}

	void TestPeriodic()
	{
		drive->drive();
	}
};

START_ROBOT_CLASS(Hematologist);
