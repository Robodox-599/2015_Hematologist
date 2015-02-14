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

	void RobotInit(){
		oi = new HematologistOperatorInterface();
		manip = new HematologistManipulator(oi->getJoystick('M'));
		drive = new HematologistDrive(oi);

	}

	void AutonomousInit(){

	}

	void AutonomousPeriodic(){

	}

	void TeleopInit(){}

	void TeleopPeriodic(){
		//drive->drive(oi->getJoystick('L')->GetY(), oi->getJoystick('L')->GetX(), oi->getJoystick('R')->GetX());
		manip->moveLift(oi->getJoystick('M')->GetY());
		//manip->toggleCompressor(oi->getJoystick('M')->GetRawButton(6), oi->getJoystick('M')->GetRawButton(7));
		oi->getDashboard()->PutNumber("Left Drive Y:", oi->getJoystick('L')->GetY());
		oi->getDashboard()->PutNumber("Right Drive Y:", oi->getJoystick('R')->GetY());
		oi->getDashboard()->PutNumber("Manip Drive Y:", oi->getJoystick('M')->GetY());
		oi->getDashboard()->PutNumber("Left Lift:", manip->leftLiftMotor->GetRaw());
		oi->getDashboard()->PutNumber("Right Lift:", manip->rightLiftMotor->GetRaw());
		oi->getDashboard()->PutBoolean("LimitSwitch:", manip->getLimitSwitch()->limitSwitchIsPressed());
	}

	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
