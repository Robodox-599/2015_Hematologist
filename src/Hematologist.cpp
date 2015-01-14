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
		drive = new HematologistDrive(oi);
		oi = new HematologistOperatorInterface();
		timer = new Timer();
	}

	void RobotInit()
	{

	}

	void AutonomousInit()
	{
		drive->gyro->Reset();
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
    	  drive->HematologistDrive(-1.0, -angle * drive->Kp);
    	  Wait(0.004);
      }
	}

	void TeleopInit()
	{
		drive->gyro->Reset();
	}

	void TeleopPeriodic()
	{
		drive->drive(float spin, float side, float forward);
	}

	void TestPeriodic()
	{
	}
};

START_ROBOT_CLASS(Hematologist);
