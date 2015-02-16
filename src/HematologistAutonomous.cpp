#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip)
{
	this->drive = drive;
	this->manip = manip;
}

HematologistAutonomous::~HematologistAutonomous(){
	delete drive;
	delete manip;

	drive = NULL;
	manip = NULL;
}

void HematologistAutonomous::strafeRight()
{
	drive->drive(0, 0, .4);
	Wait(.3);
	drive->drive(0, 0, 0);
}

void HematologistAutonomous::getTwoTotes()
{
	drive->getEncoder(true, true)->Reset();
	drive->getEncoder(true, false)->Reset();
	drive->getEncoder(false, true)->Reset();
	drive->getEncoder(false, false)->Reset();


	/*
	 * move forward up to bin
	 * close forklift
	 * start moving forward
	 * raise forklift
	 * close second tier at appropriate time
	 * hit poit where you are to turn
	 * reset encoders
	 * turn as necessary using encoders
	 * put forklift down all the way down to hit limit switch - move forward when done turning
	 * Be at the second tote
	 * repeat process
	 *
	 */
}

void HematologistAutonomous::getThreeTotes()
{
	getTwoTotes();
	/*
	 * continue logic of the previous totes.
	 * */
}



int HematologistAutonomous::getStrafeAverage()
{
	return abs(drive->getEncoder(true, true)->Get() + drive->getEncoder(false, false)->Get() - drive->getEncoder(true, false)->Get() - drive->getEncoder(false, true)->Get())/4;
	
}
int HematologistAutonomous::getTurnAverage()
{
	return abs(drive->getEncoder(true, true)->Get() + drive->getEncoder(false, true)->Get() - drive->getEncoder(true, false)->Get() - drive->getEncoder(false, false)->Get())/4;
}
int HematologistAutonomous::getForwardAverage()
{
	return (drive->getEncoder(true, true)->Get() + drive->getEncoder(false, true)->Get() - drive->getEncoder(true, false)->Get() - drive->getEncoder(false, false)->Get())/4;
}
