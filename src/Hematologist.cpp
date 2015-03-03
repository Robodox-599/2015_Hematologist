#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"
#include "HematologistDrive.h"
#include "HematologistManipulator.h"
#include "HematologistAutonomous.h"

class Hematologist: public IterativeRobot
{
private:
	//Object initializations
	HematologistOperatorInterface* oi;
	HematologistManipulator* manip;
	HematologistDrive* drive;
	HematologistAutonomous* auton;
	//CameraServer* camera = CameraServer::GetInstance();
	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;

	void RobotInit(){
		//Object declarations
		oi = new HematologistOperatorInterface();
		manip = new HematologistManipulator(oi->getJoystick('M'));
		drive = new HematologistDrive(oi);
		auton = new HematologistAutonomous(drive, manip, oi);

		// below is code Milee found online
		//camera->SetQuality(50);
		//camera->StartAutomaticCapture("cam0");

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
		//auton->strafeRight();
		//printSmartDashboard();
		auton->getTwoTotes();
	}

	void TeleopInit(){}

	void TeleopPeriodic()
	{
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
		drive->resetEncoders(oi->getJoystick('L')->GetRawButton(RESET_ENCODER_BUTTON));

		manip->moveLift(oi->getJoystick('M')->GetY());
		manip->turnOffCompressor(oi->getJoystick('M')->GetRawButton(STOP_COMPRESSOR_BUTTON));
		manip->turnOnCompressor(oi->getJoystick('M')->GetRawButton(START_COMPRESSOR_BUTTON));

		manip->openPiston(false, oi->getJoystick('M')->GetRawButton(SECOND_TIER_OPEN_BUTTON));	//open second tier
		manip->closePiston(false, oi->getJoystick('M')->GetRawButton(SECOND_TIER_CLOSE_BUTTON));	//close second tier

		manip->openPiston(true, oi->getJoystick('M')->GetRawButton(FORKLIFT_OPEN_BUTTON));		//open forklift
		manip->closePiston(true, oi->getJoystick('M')->GetRawButton(FORKLIFT_CLOSE_BUTTON));	//close forklift

		manip->openBinHugger(oi->getJoystick('M')->GetRawButton(BIN_HUGGER_OPEN_BUTTON));
		manip->closeBinHugger(oi->getJoystick('M')->GetRawButton(BIN_HUGGER_CLOSE_BUTTON));

		manip->longArmOpenStep1(oi->getJoystick('L')->GetRawButton(LONG_ARM_OPEN_ENABLE_BUTTON));
		manip->longArmOpenStep2(oi->getJoystick('R')->GetRawButton(LONG_ARM_OPEN_ENABLE_BUTTON));
		manip->longArmOpenStep3(oi->getJoystick('L')->GetRawButton(LONG_ARM_TRIGGER_BUTTON) || oi->getJoystick('R')->GetRawButton(LONG_ARM_TRIGGER_BUTTON));

		manip->longArmCloseStep1(oi->getJoystick('L')->GetRawButton(LONG_ARM_CLOSE_ENABLE_BUTTON));
		manip->longArmCloseStep2(oi->getJoystick('R')->GetRawButton(LONG_ARM_CLOSE_ENABLE_BUTTON));
		manip->longArmCloseStep3(oi->getJoystick('L')->GetRawButton(LONG_ARM_TRIGGER_BUTTON) || oi->getJoystick('R')->GetRawButton(LONG_ARM_TRIGGER_BUTTON));

		manip->longArmMoveIn();		//close
		manip->longArmMoveOut();	//open

/*gyro stuff*/
		drive->turnOnGyro(oi->getJoystick('L')->GetRawButton(GYRO_ON_BUTTON));
		drive->turnOffGyro(oi->getJoystick('L')->GetRawButton(GYRO_OFF_BUTTON));
		printSmartDashboard();
	}


	void TestPeriodic(){}

	void printSmartDashboard()
	{

		oi->getDashboard()->PutBoolean("Top Limit Switch:", manip->getLimitSwitch(true)->limitSwitchIsPressed());
		oi->getDashboard()->PutBoolean("Bottom Limit Switch:", manip->getLimitSwitch(false)->limitSwitchIsPressed());

		oi->getDashboard()->PutNumber("Encoder Forward Average:", auton->getForwardAverage());
		oi->getDashboard()->PutNumber("Encoder Turn Average:", auton->getTurnAverage());
		oi->getDashboard()->PutNumber("Encoder Strafe Average:", auton->getStrafeAverage());

		oi->getDashboard()->PutBoolean("Gyro On", drive->gyroIsOn());
		oi->getDashboard()->PutNumber("Gyro Angle:", drive->getGyro()->GetAngle());

		//encoder values
		oi->getDashboard()->PutNumber("FrontRight Encoder:", drive->getEncoder(true, true)->Get());
		oi->getDashboard()->PutNumber("FrontLeft Encoder:", drive->getEncoder(true, false)->Get());
		oi->getDashboard()->PutNumber("BackRight Encoder:", drive->getEncoder(false, true)->Get());
		oi->getDashboard()->PutNumber("BackLeft Encoder:", drive->getEncoder(false, false)->Get());

		oi->getDashboard()->PutNumber("LiftEncoder", manip->getLiftEncoder()->Get());

	}
};

START_ROBOT_CLASS(Hematologist);
