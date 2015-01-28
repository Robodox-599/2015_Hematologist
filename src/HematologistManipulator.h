#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

class HematologistManipulator
{
private:
	DoubleSolenoid* solenoid;

	Joystick* manipJoystick;


public:
	HematologistManipulator();
	~virtual HematologistManipulator();
	void toggleBinHugger();





};



#endif