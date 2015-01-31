#include "HematologistDrive.h"
#include "HematologistOperatorInterface.h"

bool autonInit = true;
double autonInitTime = 0;
float angle = 0;

class Hematologist: public IterativeRobot
{
	HematologistDrive *drive;
	HematologistOperatorInterface *oi;
	LiveWindow *lw;

	double distance;

public:
	Hematologist()
	{
		oi = new HematologistOperatorInterface();
		drive = new HematologistDrive();
		lw = LiveWindow::GetInstance();
		oi->dashboard->init();
		encLift = new Encoder(0,1,false, Encoder::EncodingType::k4X);
		encFrontLeft = new Encoder(0,1,false, Encoder::EncodingType::k4X);
		encBackLeft = new Encoder(0,1,false, Encoder::EncodingType::k4X);
		encFrontRight = new Encoder(0,1,false, Encoder::EncodingType::k4X);
		encBackRight = new Encoder(0,1,false, Encoder::EncodingType::k4X);
	    distance = encFrontLeft->GetDistance();
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
		if(distance == 7)
		{
			drive->setLinearDrive() = 0;
			drive->setTurn() = -.5;
			drive->setStrafe() = 0;
			if(drive->gyro->GetAngle() == -10){
				drive->setTurn() = 0;
				drive->gyro->Reset();
			}
			if(drive->drive()==0)
			{
				encFrontLeft->Reset();
			   drive->setLinearDrive() = 1 + drive->setTurn();
			}
		}

	}

	void TeleopInit()
	{
	}

	void TeleopPeriodic()
	{
		if(oi->rightJoystick->GetTrigger())
		{
			drive->drive(oi->rightJoystick->GetY(), oi->rightJoystick->GetX(), oi->leftJoystick->GetX());
		}
		else
		{
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
		drive->drive(oi->rightJoystick->GetY(), oi->rightJoystick->GetX(), oi->leftJoystick->GetX());
	}
};

START_ROBOT_CLASS(Hematologist);
