#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

class HematologistManipulator
{
private:
	DoubleSolenoid* solenoid;

	Talon* rightForkliftMotor;
	Talon* leftForkliftMotor; 

public:
	HematologistManipulator();
	~virtual HematologistManipulator();
	void toggleBinHugger();
	void moveForklift(float power);

};
#endif