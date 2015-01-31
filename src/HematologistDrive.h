#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H
#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"

class HematologistDrive
{
public:
	HematologistDrive();
	~HematologistDrive();

     void setLinearDrive();
     void setTurn();
     void setStrafe();
     void setStrafe(float speed);
	 void drive();
	 void testDrive();
	 void hematologistStrafeDrive();
	 void setAutonStrafeRight();
	 void setAutonSpeed

	 Gyro* gyro;

	 float forward;
	 float spin;
	 float side;
	 float autonSide;
	 double initTime;
	 float Kp = .06;

	 Timer* timer;

private:
	HematologistOperatorInterface* oi;

	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

	double gyro_ref;
};





