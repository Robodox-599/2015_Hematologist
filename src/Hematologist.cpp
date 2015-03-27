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

	void AutonomousPeriodic(){}

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
	}



	void TestPeriodic(){}
};

START_ROBOT_CLASS(Hematologist);
