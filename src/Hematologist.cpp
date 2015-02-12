#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"
#include "HematologistDrive.h"
#include "HematologistManipulator.h"
#include "HematologistAutonomous.h"

class Hematologist: public IterativeRobot
{
private:
	HematologistOperatorInterface* oi;
	HematologistManipulator* manip;
	HematologistDrive* drive;
	HematologistAutonomous* auton;


	void RobotInit(){
		oi = new HematologistOperatorInterface();
		manip = new HematologistManipulator(oi->getJoystick('M'));
		drive = new HematologistDrive(oi);
		auton = new HematologistAutonomous(drive, manip);

	}

	void AutonomousInit(){}

	void AutonomousPeriodic(){
		auton->secondHemanAuto();
		oi->getDashboard()->PutNumber("FrontRightEncoder", drive->frontRightEncoder->Get());
		oi->getDashboard()->PutNumber("frontLeftEncoder", drive->frontLeftEncoder->Get());
		oi->getDashboard()->PutNumber("backRightEncoder", drive->backRightEncoder->Get());
		oi->getDashboard()->PutNumber("backLeftEncoder", drive->backLeftEncoder->Get());


	}

	void TeleopInit(){}

	void TeleopPeriodic(){
		drive->drive(oi->getJoystick('L')->GetY(), oi->getJoystick('L')->GetX(), -oi->getJoystick('R')->GetX());
		manip->moveLift(oi->getJoystick('R')->GetY());
		oi->getDashboard()->PutNumber("Joystick Left Y:", oi->getJoystick('L')->GetY());
		oi->getDashboard()->PutNumber("Joystick Left X:", oi->getJoystick('L')->GetX());
		oi->getDashboard()->PutNumber("Joystick Right Y:", oi->getJoystick('R')->GetY());
		oi->getDashboard()->PutNumber("Joystick Right X:", oi->getJoystick('R')->GetX());
		oi->getDashboard()->PutNumber("Joystick Manip Y:", oi->getJoystick('M')->GetX());
		oi->getDashboard()->PutNumber("Joystick Manip Y:", oi->getJoystick('M')->GetY());
		oi->getDashboard()->PutNumber("FrontRightEncoder", drive->frontRightEncoder->Get());
		oi->getDashboard()->PutNumber("frontLeftEncoder", drive->frontLeftEncoder->Get());
		oi->getDashboard()->PutNumber("backRightEncoder", drive->backRightEncoder->Get());
		oi->getDashboard()->PutNumber("backLeftEncoder", drive->backLeftEncoder->Get());
	}

	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
