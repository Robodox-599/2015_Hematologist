#include "HematologistDrive.h"
#include "HematologistOperatorInterface.h"

bool autonInit = true;
double autonInitTime = 0;
float angle = 0;

class Hematologist: public IterativeRobot
{
	HematologistDrive *drive;
	HematologistOperatorInterface *oi;
	Timer *timer;

public:
	Hematologist()
	{
		oi = new HematologistOperatorInterface();
		drive = new HematologistDrive();
		timer = new Timer();
		oi->dashboard->init();
	}

	void RobotInit()
	{
		drive->gyro->Reset();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
      if(autonInit)
      {
    	autonInitTime = timer->Get();
    	autonInit = false;
      }
      if(timer->Get() > 0 + autonInitTime)
      {
    	  angle = drive->gyro->GetAngle();
    	  //drive->drive(-1.0, 1.0, 1.0);
    	  Wait(0.004);
      }
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		drive->RobotDrive->MecanumDrive_Cartesian(oi->rightJoystick->GetX(), oi->rightJoystick->GetY(), oi->leftJoystick->GetX(), drive->gyro->GetAngle());
		oi->dashboard->PutNumber("Gyro Angle: ", drive->gyro->GetAngle());
		oi->dashboard->PutNumber("Gyro Rate: ", drive->gyro->GetRate());
	}

	void TestPeriodic()
	{
	}
};

START_ROBOT_CLASS(Hematologist);
