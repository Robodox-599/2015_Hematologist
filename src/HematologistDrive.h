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
	 void drive();
	 void testDrive();

	 Gyro* gyro;

	 float forward;
	 float spin;
	 float side;
	 double initTime;

private:
	HematologistOperatorInterface* oi;

	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

	Timer* timer;
	double gyro_ref;

    static constexpr float Kp = .03;
};
#endif
