#ifndef HEMATOLOGISTAUTONOMOUS_H_
#define HEMATOLOGISTAUTONOMOUS_H_

class HematologistAutonomous
{
private:
	HematologistDrive* drive;
	HematologistManipulator* manip;
	Encoder* encFrontLeft;
	Encoder* encFrontRight;
	Encoder* encBackLeft;
	Encoder* encBackRight;
	Encoder* encLift;

public:
	HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip);
	~virtual HematologistAutonomous();

};
#endif
