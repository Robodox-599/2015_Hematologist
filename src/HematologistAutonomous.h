#ifndef HEMATOLOGIST_AUTONOMOUS_H_
#define HEMATOLOGIST_AUTONOMOUS_H_

class HematologistAutonomous
{
private:
	HematologistManipulator *man;
	HematologistDrive* drive;
	Encoder* frontLeftEnc; //encoders for drive motor
	Encoder* frontRightEnc;
	Encoder* backLeftEnc;
	Encoder* backRightEnc;

	double averageEncVal; //all four Enc Value divided by four

public:
	HematologistAutonomous();
	~HematologistAutonomous();

	void secondHemanAuto(); // gets 2-3 totes and stack it
	void setAverageEncVal();
};
