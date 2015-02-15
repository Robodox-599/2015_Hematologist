#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"
#include "HematologistDrive.h"
#include "HematologistManipulator.h"

class Hematologist: public IterativeRobot
{
private:
	HematologistOperatorInterface* oi;
	HematologistManipulator* manip;
	HematologistDrive* drive;
	CameraServer* camera = CameraServer::GetInstance();

	void RobotInit(){
		oi = new HematologistOperatorInterface();
		manip = new HematologistManipulator(oi->getJoystick('M'));
		drive = new HematologistDrive(oi);
		camera->SetQuality(50);
		camera->StartAutomaticCapture("cam0");
	}

	void AutonomousInit(){

	}

	void AutonomousPeriodic(){

	}

	void TeleopInit(){}

	void TeleopPeriodic(){
		drive->drive(-oi->getJoystick('L')->GetY(), oi->getJoystick('L')->GetX(), oi->getJoystick('R')->GetX());
		manip->activateForklift(oi->getJoystick('M')->GetRawButton(3));
		manip->activateSecondTier(oi->getJoystick('M')->GetRawButton(2));
		//manip->moveLift(-oi->getJoystick('M')->GetY());
		//manip->controlCompressor(oi->getJoystick('M')->GetRawButton(6))
		//manip->toggleCompressor(oi->getJoystick('M')->GetRawButton(6), oi->getJoystick('M')->GetRawButton(7));
		oi->getDashboard()->PutNumber("Left Drive Y:", oi->getJoystick('L')->GetY());
		oi->getDashboard()->PutNumber("Right Drive Y:", oi->getJoystick('R')->GetY());
		oi->getDashboard()->PutNumber("Manip Drive Y:", oi->getJoystick('M')->GetY());
		oi->getDashboard()->PutNumber("FrontRight Encoder:", drive->getEncoder(true, true)->Get());
		oi->getDashboard()->PutNumber("FrontLeft Encoder:", drive->getEncoder(true, false)->Get());
		oi->getDashboard()->PutNumber("BackRight Encoder:", drive->getEncoder(false, true)->Get());
		oi->getDashboard()->PutNumber("BackLeft Encoder:", drive->getEncoder(false, false)->Get());
		oi->getDashboard()->PutNumber("Forward:", drive->setForward(-oi->getJoystick('L')->GetY()));
		oi->getDashboard()->PutNumber("Turn:", drive->setForward(-oi->getJoystick('L')->GetX()));
		oi->getDashboard()->PutNumber("Strafe:", drive->setForward(oi->getJoystick('R')->GetX()));
		oi->getDashboard()->PutBoolean("forklift state:", manip->getForkliftState());
		oi->getDashboard()->PutBoolean("second tier staet:", manip->getSecondTierState());
		//oi->getDashboard()->PutNumber("Left Lift:", manip->getManipTalon(true)->GetRaw());
		//oi->getDashboard()->PutNumber("Right Lift:", manip->getManipTalon(false)->GetRaw());
		//oi->getDashboard()->PutBoolean("LimitSwitch:", manip->getLimitSwitch()->limitSwitchIsPressed());
		//oi->getDashboard()->PutBoolean("Comopressor On:", manip->getCompressorOn());
	}

	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
