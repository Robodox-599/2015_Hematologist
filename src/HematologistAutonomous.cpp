#include "HematologistAutonomous.h"

HematologistAutonomous::HematologistAutonomous(HematologistManipulator* manip)
{
	manipulator = manip;
	step = 0;

}

HematologistAutonomous::~HematologistAutonomous()
{
	delete manipulator;

	manipulator = NULL;
}
void HematologistAutonomous::AutonomousThree()
{
	while(step >= 0 && step <= 5)
		{
		 if(step = 0)
		 {
			 drive->gyro->Reset();
			 if(drive->gyro->GetAngle()<45)
			 {
			     drive->drive(0, .5, 0);
			 }
			 else{
				 drive->gyro->Reset();
			     drive->drive();
			     step++;
			 }
		 }
		 if(step = 1)
		 {
			 drive->drive(.5, 0, 0);
		 }
		}
}
