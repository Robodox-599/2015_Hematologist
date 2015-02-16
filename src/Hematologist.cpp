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
		drive->drive(oi->getJoystick('L')->GetY(), oi->getJoystick('L')->GetX(), oi->getJoystick('R')->GetX());

		//manip->activateForklift(oi->getJoystick('M')->GetRawButton(3));
		//manip->activateSecondTier(oi->getJoystick('M')->GetRawButton(2));
		manip->moveLift(-oi->getJoystick('M')->GetY());
		manip->turnOffCompressor(oi->getJoystick('M')->GetRawButton(9));
		manip->turnOnCompressor(oi->getJoystick('M')->GetRawButton(8));

		manip->openPiston(false, oi->getJoystick('M')->GetRawButton(11));	//open second tier
		manip->closePiston(false, oi->getJoystick('M')->GetRawButton(10));	//close second tier

		manip->openPiston(true, oi->getJoystick('M')->GetRawButton(6));		//open forklift
		manip->closePiston(true, oi->getJoystick('M')->GetRawButton(7));	//close forklift

		manip->automaticallyActivate(oi->getJoystick('M')->GetRawButton(1));

#if 0
		manip->openBinHugger(oi->getJoystick('M')->GetRawButton(5));
		manip->closeBinHugger(oi->getJoystick('M')->GetRawButton(4));
#endif

#if 0
		manip->longArmOpenStep1(oi->getJoystick('L')->GetRawButton(4));
		manip->longArmOpenStep2(oi->getJoystick('R')->GetRawButton(4));
		manip->longArmOpenStep3(oi->getJoystick('L')->GetRawButton(1) || oi->getJoystick('R')->GetRawButton(1));

		manip->longArmCloseStep1(oi->getJoystick('L')->GetRawButton(2));
		manip->longArmCloseStep2(oi->getJoystick('R')->GetRawButton(2));
		manip->longArmCloseStep3(oi->getJoystick('L')->GetRawButton(1) || oi->getJoystick('R')->GetRawButton(1));

		manip->longArmMoveIn();	//close
		manip->longArmMoveOut();	//open
#endif
		//joysticks
		oi->getDashboard()->PutNumber("Left Drive Y:", oi->getJoystick('L')->GetY());
		oi->getDashboard()->PutNumber("Right Drive Y:", oi->getJoystick('R')->GetY());
		oi->getDashboard()->PutNumber("Manip Drive Y:", oi->getJoystick('M')->GetY());
		oi->getDashboard()->PutNumber("Left Drive X:", oi->getJoystick('L')->GetX());
		oi->getDashboard()->PutBoolean("joystick L button 3",oi->getJoystick('L')->GetRawButton(3));
		oi->getDashboard()->PutBoolean("joystick L button 2",oi->getJoystick('L')->GetRawButton(2));
		oi->getDashboard()->PutBoolean("joystick L button 1",oi->getJoystick('L')->GetRawButton(1));
		oi->getDashboard()->PutBoolean("joystick R button 3",oi->getJoystick('R')->GetRawButton(3));
		oi->getDashboard()->PutBoolean("joystick R button 2",oi->getJoystick('R')->GetRawButton(2));
		oi->getDashboard()->PutBoolean("joystick R button 1",oi->getJoystick('R')->GetRawButton(1));

		//encoder values
		oi->getDashboard()->PutNumber("FrontRight Encoder:", drive->getEncoder(true, true)->Get());
		oi->getDashboard()->PutNumber("FrontLeft Encoder:", drive->getEncoder(true, false)->Get());
		oi->getDashboard()->PutNumber("BackRight Encoder:", drive->getEncoder(false, true)->Get());
		oi->getDashboard()->PutNumber("BackLeft Encoder:", drive->getEncoder(false, false)->Get());
		oi->getDashboard()->PutNumber("LiftEncoder", manip->getLiftEncoder()->Get());

		//values given to motors
		oi->getDashboard()->PutNumber("Forward:", drive->setForward(-oi->getJoystick('L')->GetY()));
		oi->getDashboard()->PutNumber("Turn:", drive->setForward(-oi->getJoystick('L')->GetX()));
		oi->getDashboard()->PutNumber("Strafe:", drive->setForward(oi->getJoystick('R')->GetX()));

		//forklift
		oi->getDashboard()->PutBoolean("forklift state:", manip->getForkliftState());
		oi->getDashboard()->PutNumber("forklift value:", manip->getForkliftPiston()->Get());
		oi->getDashboard()->PutBoolean("forklift open:", manip->forkliftIsOpen());

		//second tier
		oi->getDashboard()->PutBoolean("second tier state:", manip->getSecondTierState());
		oi->getDashboard()->PutNumber("second tier value:", manip->getSecondTierPiston()->Get());
		oi->getDashboard()->PutBoolean("second tier is open", manip->secondTierIsOpen());

		//constants
		oi->getDashboard()->PutNumber("kForward", DoubleSolenoid::kForward);
		oi->getDashboard()->PutNumber("kOff", DoubleSolenoid::kOff);
		oi->getDashboard()->PutNumber("kReverse", DoubleSolenoid::kReverse);

		//switches
		oi->getDashboard()->PutBoolean("Top Limit Switch:", manip->getLimitSwitch(true)->limitSwitchIsPressed());
		oi->getDashboard()->PutBoolean("Bottom Limit Switch:", manip->getLimitSwitch(false)->limitSwitchIsPressed());

		//oi->getDashboard()->PutNumber("Left Lift:", manip->getManipTalon(true)->GetRaw());
		//oi->getDashboard()->PutNumber("Right Lift:", manip->getManipTalon(false)->GetRaw());
		//oi->getDashboard()->PutBoolean("LimitSwitch:", manip->getLimitSwitch()->limitSwitchIsPressed());
		//oi->getDashboard()->PutBoolean("Comopressor On:", manip->getCompressorOn());
	}

	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
