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

		manip->moveLift(oi->getJoystick('M')->GetY());
		manip->turnOffCompressor(oi->getJoystick('M')->GetRawButton(STOP_COMPRESSOR_BUTTON));
		manip->turnOnCompressor(oi->getJoystick('M')->GetRawButton(START_COMPRESSOR_BUTTON));

		manip->openPiston(false, oi->getJoystick('M')->GetRawButton(SECOND_TIER_OPEN_BUTTON));	//open second tier
		manip->closePiston(false, oi->getJoystick('M')->GetRawButton(SECOND_TIER_CLOSE_BUTTON));	//close second tier

		manip->openPiston(true, oi->getJoystick('M')->GetRawButton(FORKLIFT_OPEN_BUTTON));		//open forklift
		manip->closePiston(true, oi->getJoystick('M')->GetRawButton(FORKLIFT_CLOSE_BUTTON));	//close forklift

		manip->automaticallyActivate(oi->getJoystick('M')->GetRawButton(AUTOMATIC_LIFT_BUTTON));

#if 0
		manip->openBinHugger(oi->getJoystick('M')->GetRawButton(BIN_HUGGER_OPEN_BUTTON));
		manip->closeBinHugger(oi->getJoystick('M')->GetRawButton(BIN_HUGGER_OPEN_BUTTON));
#endif

#if 0
		manip->longArmOpenStep1(oi->getJoystick('L')->GetRawButton(LONG_ARM_OPEN_ENABLE_BUTTON));
		manip->longArmOpenStep2(oi->getJoystick('R')->GetRawButton(LONG_ARM_OPEN_ENABLE_BUTTON));
		manip->longArmOpenStep3(oi->getJoystick('L')->GetRawButton(LONG_ARM_TRIGGER_BUTTON) || oi->getJoystick('R')->GetRawButton(LONG_ARM_TRIGGER_BUTTON));

		manip->longArmCloseStep1(oi->getJoystick('L')->GetRawButton(LONG_ARM_CLOSE_ENABLE_BUTTON));
		manip->longArmCloseStep2(oi->getJoystick('R')->GetRawButton(LONG_ARM_CLOSE_ENABLE_BUTTON));
		manip->longArmCloseStep3(oi->getJoystick('L')->GetRawButton(LONG_ARM_TRIGGER_BUTTON) || oi->getJoystick('R')->GetRawButton(LONG_ARM_TRIGGER_BUTTON));

		manip->longArmMoveIn();	//close
		manip->longArmMoveOut();	//open
#endif
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
