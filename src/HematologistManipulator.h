#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

class HematologistManipulator
{
private:
	DoubleSolenoid* solenoid;

	Joystick* manipJoystick;

	Talon* rightForkliftMotor;
	Talon* leftForkliftMotor; 


public:
	HematologistManipulator();
	~virtual HematologistManipulator();
	void toggleBinHugger();
	void moveForklift();





};



#endif