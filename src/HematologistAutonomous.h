#ifndef HEMATOLOGIST_AUTONOMOUS_H_
#define HEMATOLOGIST_AUTONOMOUS_H_

#include "HematologistMacros.h"
#include "HematologistManipulator.h"
#include "HematologistDrive.h"

class HematologistAutonomous
{
private:
	HematologistManipulator *manip;
	HematologistDrive* drive;

	bool step1;
	bool step2;
	bool step3;
	bool step4;
	bool step5;
	bool step6;
	bool step7;
	bool step8;
	bool step9; 
	bool step10; 
	bool step11; 
	bool step12; 
	bool step13; 
	bool step14; 
	bool step15; 
	bool step16; 
	bool step17; 
	bool step18;

public:
	HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip);
	~HematologistAutonomous();
	/*
	void firstHemanAuto();

	void secondHemanAuto();
	void thirdHemanAuto(); // gets 3 totes and stack it

	int encoderAverage();
	*/

	void strafeRight();
	void getTwoTotes();
	void getThreeTotes();

	int getStrafeAverage();
	int getTurnAverage();
	int getForwardAverage();
};

#endif
