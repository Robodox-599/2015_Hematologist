#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H

#include "HematologistMacros.h"
#include "HematologistOperatorInterface.h"

class HematologistDrive
{
public:
	HematologistDrive(HematologistOperatorInterface* oi);
	~HematologistDrive();

	float setForward(float forward);
	float setTurn(float turn);
	float setStrafe(float strafe);

	void drive(float forward, float turn, float strafe);
	float linearizeDrive(float driveInput);
	

private:

	Gyro* gyro;

	float forward;
	float turn;
	float strafe;

	float kP;
	
	bool gyroButton;

	HematologistOperatorInterface* oi;

	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

	float gyro_ref;

};

#endif
