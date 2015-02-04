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
	 void testDrive();

	 Gyro* gyro;
	/* Encoder *encFrontLeft;
	 Encoder *encBackLeft;
	 Encoder *encFrontRight;
	 Encoder *encBackRight;*/

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

	/*double countFrontLeft;
	double countFrontRight;
	double countBackLeft;
	double countBackRight;*/

	double gyro_ref;
};
#endif
