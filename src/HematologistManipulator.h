#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

class HematologistManipulator
{
private:
	DoubleSolenoid* solenoid;

	ManipJoystick* joystick;


public:
	HematologistManipulator();
	~virtual HematologistManipulator();
	bool buttonIsPressed(int buttonNum);





};



#endif