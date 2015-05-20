#include "HematologistMacros.h"
#include "HematologistAutonomous.h"
#include "HematologistManipulator.h"
#include "HematologistOperatorInterface.h"
#include "HematologistDrive.h"

class Hematologist: public IterativeRobot
{

	HematologistAutonomous* auton;
	HematologistManipulator* manip;
	HematologistOperatorInterface* oi;
	HematologistDrive* drive;

	//Necessary Objects for Vision
	//Unfortunately, this and every code relating to the camera was just copied from Intermediate Vision sample project
	//So I can't explain what each line does, but it works so...
	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;
private:
	void RobotInit(){
		oi = new HematologistOperatorInterface();
		drive = new HematologistDrive();
		manip = new HematologistManipulator(oi);
		auton = new HematologistAutonomous(oi, manip, drive);

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
		//auton->strafe(true);
		//auton->strafe(false);
		auton->longArmAuto();
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
		drive->drive(-oi->getJoystick('R')->GetY(), -oi->getJoystick('R')->GetX(), -oi->getJoystick('L')->GetX());

		drive->resetEncoders(oi->getJoystick('L')->GetRawButton(ENCODER_RESET_BUTTON));

		//the second variable is not actually used because the idea of a sequence, albeit useful, did not work in the field
		manip->controlLift(-oi->getJoystick('M')->GetY(), oi->getJoystick('M')->GetRawButton(START_SEQUENCE_BUTTON), oi->getJoystick('M')->GetRawButton(START_BIN_SEQUENCE_BUTTON));

		manip->turnOffCompressor(oi->getJoystick('M')->GetRawButton(TURN_COMPRESSOR_OFF_BUTTON));
		manip->turnOnCompressor(oi->getJoystick('M')->GetRawButton(TURN_COMPRESSOR_ON_BUTTON));

		manip->openForklift(oi->getJoystick('M')->GetRawButton(OPEN_FORKLIFT_BUTTON));
		manip->closeForklift(oi->getJoystick('M')->GetRawButton(CLOSE_FORKLIFT_BUTTON));

		manip->openSecondTier(oi->getJoystick('M')->GetRawButton(OPEN_SECOND_TIER_BUTTON));
		manip->closeSecondTier(oi->getJoystick('M')->GetRawButton(CLOSE_SECOND_TIER_BUTTON));

		manip->openBinHugger(oi->getJoystick('M')->GetRawButton(OPEN_BIN_HUGGER_BUTTON));
		manip->closeBinHugger(oi->getJoystick('M')->GetRawButton(CLOSE_BIN_HUGGER_BUTTON));

		//these functions take about 2 seconds for it to happen b/c of how slow the pistons are that control the thing
		/*
			What I pass as a parameter into these long arm functions is a boolean
			oi->getJoystick('L')->GetRawButton(EXTEND_LONG_ARM_BUTTON) returns a boolean to check if if that button is pressed
			oi->getJoystick('L')->GetRawButton(CONFIRM_BUTTON) returns a boolean to check if the trigger is button
			instead of passing the two separately, i pass it as boolean && boolean so that i'm only sending one bool 
			so that i'm only checking one variable in the code for the function insetad of two
		*/
		manip->extendLongArm(oi->getJoystick('L')->GetRawButton(EXTEND_LONG_ARM_BUTTON) && oi->getJoystick('L')->GetRawButton(CONFIRM_BUTTON));
		manip->retractLongArm(oi->getJoystick('L')->GetRawButton(RETRACT_LONG_ARM_BUTTON) && oi->getJoystick('L')->GetRawButton(CONFIRM_BUTTON));

		manip->openFlaps(oi->getJoystick('L')->GetRawButton(OPEN_FLAPS_BUTTON) && oi->getJoystick('L')->GetRawButton(CONFIRM_BUTTON));
		manip->closeFlaps(oi->getJoystick('L')->GetRawButton(CLOSE_FLAPS_BUTTON) && oi->getJoystick('L')->GetRawButton(CONFIRM_BUTTON));

		manip->intakeWithRoller(oi->getJoystick('M')->GetRawButton(INTAKE_ROLLER_BUTTON));


		printSmartDashboard();
	}

	//prints important information to the dashboard
	void printSmartDashboard()
	{
		oi->getDashboard()->PutBoolean("Top Limit Switch", manip->getTopLimitSwitch()->isPressed());
		oi->getDashboard()->PutBoolean("Bottom Limit Switch", manip->getBottomLimitSwitch()->isPressed());
		oi->getDashboard()->PutNumber("Forward Average: ", drive->getForwardAverage());
		oi->getDashboard()->PutNumber("Turn Average: ", drive->getTurnAverage());
		oi->getDashboard()->PutNumber("Strafe Average: ", drive->getStrafeAverage());
		oi->getDashboard()->PutBoolean("Ready: ", manip->highEnough());
		oi->getDashboard()->PutNumber("Lift Encoder: ", manip->getEncoderValue());
	}

	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
