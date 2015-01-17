#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H
#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"

class HematologistDrive
{
public:
	HematologistDrive();
	~HematologistDrive();
	RobotDrive* RobotDrive;

	/*
     void setLinearDrive(float forward);
     void setTurn(float spin);
     void setStrafe(float side);
	 void drive(float spin, float side, float forward);*/

	 Gyro* gyro;
	 static const float Kp;

private:
/*
	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;
*/

	HematologistOperatorInterface* oi;
};
#endif
