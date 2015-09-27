#include "HematologistMacros.h"
#include "Autonomous/Autonomous.h"
#include "Drive/Drive.h"
#include "Manipulator/Manipulator.h"
#include "HematologistOperatorInterface.h"

class Hematologist: public IterativeRobot
{
	Autonomous* auton;
	Manipulator* manip;
	HematologistOperatorInterface* oi;
	Drive* drive;

	//Necessary Objects for Vision
	//Unfortunately, this and every code relating to the camera was just copied from Intermediate Vision sample project
	//So I can't explain what each line does, but it works so...
	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;

private:
	void RobotInit(){
		oi = new HematologistOperatorInterface();
		drive = new Drive();
		manip = new Manipulator();
		auton = new Autonomous(oi, manip, drive);

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

	void AutonomousInit(){}

	void AutonomousPeriodic(){
		//auton->strafeRight();
		//auton->strafeLeft();
		//auton->longArmAuto();
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
		}else{
			//imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
			CameraServer::GetInstance()->SetImage(frame);
		}

		//negative value as joysticks are reversed so moving up on a joystick gives you a negative value
		//as such, negative joystick is the positive value (so instead of -1, I put in -(-1))

		//---------------- GET JOYSTICK DRIVE VALUES ----------------
		drive->drive(-oi->getJoystick('R')->GetY(), -oi->getJoystick('R')->GetX(), -oi->getJoystick('L')->GetX());

		drive->resetEncoders(oi->getJoystick('L')->GetRawButton(ENCODER_RESET_BUTTON));

		//---------------- GET MANIPULATOR BUTTON VALUES ----------------
		// 1. Compressors
		manip->turnOffCompressor(oi->getJoystick('M')->GetRawButton(TURN_COMPRESSOR_OFF_BUTTON));
		manip->turnOnCompressor(oi->getJoystick('M')->GetRawButton(TURN_COMPRESSOR_ON_BUTTON));
		// 2. Forklift
		manip->openForklift(oi->getJoystick('M')->GetRawButton(OPEN_FORKLIFT_BUTTON));
		manip->closeForklift(oi->getJoystick('M')->GetRawButton(CLOSE_FORKLIFT_BUTTON));
		// 3. Second tier
		manip->openSecondTier(oi->getJoystick('M')->GetRawButton(OPEN_SECOND_TIER_BUTTON));
		manip->closeSecondTier(oi->getJoystick('M')->GetRawButton(CLOSE_SECOND_TIER_BUTTON));
		// 4. Bin hugger
		manip->openBinHugger(oi->getJoystick('M')->GetRawButton(OPEN_BIN_HUGGER_BUTTON));
		manip->closeBinHugger(oi->getJoystick('M')->GetRawButton(CLOSE_BIN_HUGGER_BUTTON));
		// 5. Long arms
		manip->extendLongArm(oi->getJoystick('L')->GetRawButton(EXTEND_LONG_ARM_BUTTON) && oi->getJoystick('L')->GetRawButton(CONFIRM_BUTTON));
		manip->retractLongArm(oi->getJoystick('L')->GetRawButton(RETRACT_LONG_ARM_BUTTON) && oi->getJoystick('L')->GetRawButton(CONFIRM_BUTTON));
		// 6. Flaps
		manip->openFlaps(oi->getJoystick('M')->GetRawButton(OPEN_FLAPS_BUTTON));
		manip->closeFlaps(oi->getJoystick('M')->GetRawButton(CLOSE_FLAPS_BUTTON));
		// 7. Intake
		manip->intakeWithRoller(oi->getJoystick('M')->GetRawButton(INTAKE_ROLLER_BUTTON));
		// 8. Move lift
		manip->moveLift(oi->getJoystick('L')->GetY());

		printSmartDashboard();
	}

	void printSmartDashboard()
	{
		oi->getDashboard()->PutBoolean("Top Limit Switch ", manip->getTopLimitSwitch()->isPressed());
		oi->getDashboard()->PutBoolean("Bottom Limit Switch", manip->getBottomLimitSwitch()->isPressed());
		oi->getDashboard()->PutNumber("Forward Average: ", drive->getForwardAverage());
		oi->getDashboard()->PutNumber("Turn Average: ", drive->getTurnAverage());
		oi->getDashboard()->PutNumber("Strafe Average: ", drive->getStrafeAverage());
		oi->getDashboard()->PutNumber("Lift Encoder: ", manip->getEncoderValue());
		oi->getDashboard()->PutNumber("Lift value: ", oi->getJoystick('M')->GetY());
	}

	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
