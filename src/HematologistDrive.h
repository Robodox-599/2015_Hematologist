#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H
#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"

class HematologistDrive
{
public:
	HematologistDrive(HematologistOperatorInterface *opInt = NULL);
	~HematologistDrive();
     void setLinearDrive(float forward);
     void setTurn(float spin);
     void setStrafe(float side);
	 void drive(float spin, float side, float forward);

private:
	Gyro* gyro;
	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

	static const float Kp;

	HematologistOperatorInterface *oi;

};
#endif
