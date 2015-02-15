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

		//manip->activateForklift(oi->getJoystick('M')->GetRawButton(3));
		//manip->activateSecondTier(oi->getJoystick('M')->GetRawButton(2));
		manip->moveLift(-oi->getJoystick('M')->GetY());
		manip->turnOffCompressor(oi->getJoystick('M')->GetRawButton(6));
		manip->turnOnCompressor(oi->getJoystick('M')->GetRawButton(7));

		manip->openPiston(true, oi->getJoystick('M')->GetRawButton(11));		//open forklift 2
		manip->closePiston(true, oi->getJoystick('M')->GetRawButton(10));	//close forklift	1

		manip->openPiston(false, oi->getJoystick('M')->GetRawButton(8));	//open second tier	2
		manip->closePiston(false, oi->getJoystick('M')->GetRawButton(9));	//close second tier	1

		manip->automaticallyActivate(oi->getJoystick('M')->GetRawButton(1));

		//joysticks
		oi->getDashboard()->PutNumber("Left Drive Y:", oi->getJoystick('L')->GetY());
		oi->getDashboard()->PutNumber("Right Drive Y:", oi->getJoystick('R')->GetY());
		oi->getDashboard()->PutNumber("Manip Drive Y:", oi->getJoystick('M')->GetY());
		oi->getDashboard()->PutNumber("Left Drive X:", oi->getJoystick('L')->GetX());

		//encoder values
		oi->getDashboard()->PutNumber("FrontRight Encoder:", drive->getEncoder(true, true)->Get());
		oi->getDashboard()->PutNumber("FrontLeft Encoder:", drive->getEncoder(true, false)->Get());
		oi->getDashboard()->PutNumber("BackRight Encoder:", drive->getEncoder(false, true)->Get());
		oi->getDashboard()->PutNumber("BackLeft Encoder:", drive->getEncoder(false, false)->Get());
		oi->getDashboard()->PutNumber("LiftEncoder", manip->getLiftEncoder()->Get());

		//values given to joysticks
		oi->getDashboard()->PutNumber("Forward:", drive->setForward(-oi->getJoystick('L')->GetY()));
		oi->getDashboard()->PutNumber("Turn:", drive->setForward(-oi->getJoystick('L')->GetX()));
		oi->getDashboard()->PutNumber("Strafe:", drive->setForward(oi->getJoystick('R')->GetX()));

		//forklift
		oi->getDashboard()->PutBoolean("forklift state:", manip->getForkliftState());
		oi->getDashboard()->PutNumber("forklift value:", manip->getForkliftPiston()->Get());

		//second tier
		oi->getDashboard()->PutBoolean("second tier state:", manip->getSecondTierState());
		oi->getDashboard()->PutNumber("second tier value:", manip->getSecondTierPiston()->Get());

		//constants
		oi->getDashboard()->PutNumber("kForward", DoubleSolenoid::kForward);
		oi->getDashboard()->PutNumber("kOff", DoubleSolenoid::kOff);
		oi->getDashboard()->PutNumber("kReverse", DoubleSolenoid::kReverse);

		//oi->getDashboard()->PutNumber("Left Lift:", manip->getManipTalon(true)->GetRaw());
		//oi->getDashboard()->PutNumber("Right Lift:", manip->getManipTalon(false)->GetRaw());
		//oi->getDashboard()->PutBoolean("LimitSwitch:", manip->getLimitSwitch()->limitSwitchIsPressed());
		//oi->getDashboard()->PutBoolean("Comopressor On:", manip->getCompressorOn());
	}

	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
