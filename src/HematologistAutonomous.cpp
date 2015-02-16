#include "HematologistAutonomous.h" // all values for the autonomous is not set. Thus need accurate calculation to replace

HematologistAutonomous::HematologistAutonomous(HematologistDrive* drive, HematologistManipulator* manip)
{
	this->drive = drive;
	this->manip = manip;
	step1 = true;	
	step2 = false;	//this step will not start, must be told when to
	step3 = false;	//this step will not start, must be told when to
	step4 = false;	//this step will not start, must be told when to
	step5 = false;	//this step will not start, must be told when to
	step6 = false;	//this step will not start, must be told when to
	step7 = false;	//this step will not start, must be told when to
	step8 = false;	//this step will not start, must be told when to
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



	//step1 = going up to bin
	//step2 = is moving forward up to a point
	//step3 = is rasing the forklift until second tier is to close
	//step4 = is turning correctly
	//step5 = moving the forklift down until the limit switch is pressed
	//step6 = is moving the robot up to the second tote

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
