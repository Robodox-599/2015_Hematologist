/*
 * HematologistAutonomous.cpp
 *
 *  Created on: Jan 29, 2015
 *      Author: Jasmine
 */


HematologistAutonomous::HematologistAutonomous()
{

}

virtual HematologistAutonomous::~HematologistAutonomous()
{

}

void HematologistAutonomousz::autonStrafeRight()
{
	drive->SetStrafe(1);
	drive->drive();
	sleep(2300);
}

