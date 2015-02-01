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

}
