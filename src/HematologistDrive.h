#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H
#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"

class HematologistDrive
{
public:
	HematologistDrive();
	~HematologistDrive();

     void setLinearDrive(float linearValue);
     void setTurn(float turnValue);
     void setStrafe(float sideValue);
	 void drive(float linearValue, float turnValue, float sideValue);
	 float linearizeDrive(float driveInput);
	 void testDrive();

	 Gyro* gyro;

	 float forward;
	 float spin;
	 float side;

	 double initTime;
	 float Kp = .1;
	 float Kd = .01;

	 Timer* timer;

private:
	HematologistOperatorInterface* oi;

	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

	double gyro_ref;
};
#endif
