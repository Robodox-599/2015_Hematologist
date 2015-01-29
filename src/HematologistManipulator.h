#ifndef HEMATOLOGIST_MANIPULATOR_H_
#define HEMATOLOGIST_MANIPULATOR_H_

class HematologistManipulator
{
private:
	DoubleSolenoid* solenoid;

	Talon* rightForkliftMotor;
	Talon* leftForkliftMotor; 

	OperatorInterface* oi;
	
public:
	HematologistManipulator();
	HematologistManipulator(OperatorInterface* oi);
	~virtual HematologistManipulator();
	void toggleBinHugger();
	void moveForklift(float power);


};
#endif