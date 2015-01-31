#ifndef HEMATOLOGIST_AUTONOMOUS_H_
#define HEMATOLOGIST_AUTONOMOUS_H_

class HematologistAutonomous
{
private:
	HematologistManipulator *man;
	HematologistDrive* drive;

public:
	HematologistAutonomous();
	~HematologistAutonomous();

	void secondHemanAuto(); // gets 2-3 totes and stack it
};
