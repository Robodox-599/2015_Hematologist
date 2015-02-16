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
	HematologistAutonomous* auton;
	//CameraServer* camera = CameraServer::GetInstance();
	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;

	void RobotInit(){
		oi = new HematologistOperatorInterface();
		manip = new HematologistManipulator(oi->getJoystick('M'));
		drive = new HematologistDrive(oi);
		auton = HematologistAutonomous(drive, oi);
#if 1
		//camera->SetQuality(50);
		//camera->StartAutomaticCapture("cam0");
#endif
		frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
		//the camera name (ex "cam0") can be found through the roborio web interface
		imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
		}
		imaqError = IMAQdxConfigureGrab(session);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
		}
	}

	void AutonomousInit(){

	}

	void AutonomousPeriodic(){

	}

	void TeleopInit(){}

	void TeleopPeriodic(){
		// acquire images
		IMAQdxStartAcquisition(session);
	        // grab an image, draw the circle, and provide it for the camera server which will
       // in turn send it to the dashboard.
		IMAQdxGrab(session, frame, true, NULL);
		if(imaqError != IMAQdxErrorSuccess) 
		{
			DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
		}else
		{
			imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
			CameraServer::GetInstance()->SetImage(frame);
		}
		drive->drive(oi->getJoystick('L')->GetY(), oi->getJoystick('L')->GetX(), oi->getJoystick('R')->GetX());

		manip->moveLift(oi->getJoystick('M')->GetY());
		manip->turnOffCompressor(oi->getJoystick('M')->GetRawButton(STOP_COMPRESSOR_BUTTON));
		manip->turnOnCompressor(oi->getJoystick('M')->GetRawButton(START_COMPRESSOR_BUTTON));

		manip->openPiston(false, oi->getJoystick('M')->GetRawButton(SECOND_TIER_OPEN_BUTTON));	//open second tier
		manip->closePiston(false, oi->getJoystick('M')->GetRawButton(SECOND_TIER_CLOSE_BUTTON));	//close second tier

		manip->openPiston(true, oi->getJoystick('M')->GetRawButton(FORKLIFT_OPEN_BUTTON));		//open forklift
		manip->closePiston(true, oi->getJoystick('M')->GetRawButton(FORKLIFT_CLOSE_BUTTON));	//close forklift

		manip->automaticallyActivate(oi->getJoystick('M')->GetRawButton(AUTOMATIC_LIFT_BUTTON));

#if 1
		manip->openBinHugger(oi->getJoystick('M')->GetRawButton(BIN_HUGGER_OPEN_BUTTON));
		manip->closeBinHugger(oi->getJoystick('M')->GetRawButton(BIN_HUGGER_CLOSE_BUTTON));
#endif

#if 0
		manip->longArmOpenStep1(oi->getJoystick('L')->GetRawButton(LONG_ARM_OPEN_ENABLE_BUTTON));
		manip->longArmOpenStep2(oi->getJoystick('R')->GetRawButton(LONG_ARM_OPEN_ENABLE_BUTTON));
		manip->longArmOpenStep3(oi->getJoystick('L')->GetRawButton(LONG_ARM_TRIGGER_BUTTON) || oi->getJoystick('R')->GetRawButton(LONG_ARM_TRIGGER_BUTTON));

		manip->longArmCloseStep1(oi->getJoystick('L')->GetRawButton(LONG_ARM_CLOSE_ENABLE_BUTTON));
		manip->longArmCloseStep2(oi->getJoystick('R')->GetRawButton(LONG_ARM_CLOSE_ENABLE_BUTTON));
		manip->longArmCloseStep3(oi->getJoystick('L')->GetRawButton(LONG_ARM_TRIGGER_BUTTON) || oi->getJoystick('R')->GetRawButton(LONG_ARM_TRIGGER_BUTTON));

		manip->longArmMoveIn();		//close
		manip->longArmMoveOut();	//open
#endif

/*gyro stuff*/
#if 1
		drive->turnOnGyro(oi->getJoystick('L')->GetRawButton(GYRO_OFF_BUTTON));
		drive->turnOffGyro(oi->getJoystick('L')->GetRawButton(GYRO_ON_BUTTON));
#endif
#if 0
		//joysticks
		oi->getDashboard()->PutNumber("Left Drive Y:", oi->getJoystick('L')->GetY());
		oi->getDashboard()->PutNumber("Right Drive Y:", oi->getJoystick('R')->GetY());
		oi->getDashboard()->PutNumber("Manip Drive Y:", oi->getJoystick('M')->GetY());
		oi->getDashboard()->PutNumber("Left Drive X:", oi->getJoystick('L')->GetX());
#endif
#if 1
		//encoder values
		oi->getDashboard()->PutNumber("FrontRight Encoder:", drive->getEncoder(true, true)->Get());
		oi->getDashboard()->PutNumber("FrontLeft Encoder:", drive->getEncoder(true, false)->Get());
		oi->getDashboard()->PutNumber("BackRight Encoder:", drive->getEncoder(false, true)->Get());
		oi->getDashboard()->PutNumber("BackLeft Encoder:", drive->getEncoder(false, false)->Get());
		oi->getDashboard()->PutNumber("LiftEncoder", manip->getLiftEncoder()->Get());
#endif
#if 0
		//values given to motors
		oi->getDashboard()->PutNumber("Forward:", drive->setForward(-oi->getJoystick('L')->GetY()));
		oi->getDashboard()->PutNumber("Turn:", drive->setForward(-oi->getJoystick('L')->GetX()));
		oi->getDashboard()->PutNumber("Strafe:", drive->setForward(oi->getJoystick('R')->GetX()));
#endif
#if 0
		//forklift
		oi->getDashboard()->PutBoolean("forklift state:", manip->getForkliftState());
		oi->getDashboard()->PutNumber("forklift value:", manip->getForkliftPiston()->Get());
		oi->getDashboard()->PutBoolean("forklift open:", manip->forkliftIsOpen());
#endif
#if 0
		//second tier
		oi->getDashboard()->PutBoolean("second tier state:", manip->getSecondTierState());
		oi->getDashboard()->PutNumber("second tier value:", manip->getSecondTierPiston()->Get());
		oi->getDashboard()->PutBoolean("second tier is open", manip->secondTierIsOpen());
#endif
#if 0
		//constants
		oi->getDashboard()->PutNumber("kForward", DoubleSolenoid::kForward);
		oi->getDashboard()->PutNumber("kOff", DoubleSolenoid::kOff);
		oi->getDashboard()->PutNumber("kReverse", DoubleSolenoid::kReverse);
#endif
		//switches
		oi->getDashboard()->PutBoolean("Top Limit Switch:", manip->getLimitSwitch(true)->limitSwitchIsPressed());
		oi->getDashboard()->PutBoolean("Bottom Limit Switch:", manip->getLimitSwitch(false)->limitSwitchIsPressed());

		oi->getDashboard()->PutBoolean("Gyro On", drive->gyroIsOn());
		oi->getDashboard()->PutNumber("Encoder Forward Average:", auton->getForwardAverage());
		oi->getDashboard()->PutNumber("Encoder Turn Average:", auton->getTurnAverage());
		oi->getDashboard()->PutNumber("Encoder Strafe Average:", auton->getStrafeAverage());
	}


	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
