#ifndef HEMATOLOGISTAUTONOMOUS_H
#define HEMATOLOGISTAUTONOMOUS_H
#include "HematologistDrive.h"
#include "HematologistManipulator.h"

class HematologistAutonomous
{
public:
HematologistAutonomous(HematologistManipulator* manip);
~HematologistAutonomous();
void AutonomousThree();

private:
HematologistManipulator* manipulator;
int step;
};
#endif




