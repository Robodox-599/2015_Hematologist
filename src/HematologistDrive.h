#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H

#include "HematologistMacros.h"

class HematologistDrive
{
public:
	HematologistDrive();
	~HematologistDrive();

	void setForward(float forward);
	void setTurn(float turn);
	void setStrafe(float strafe);

	float getForward();
	float getTurn();
	float getStrafe();

	float linearizeDrive(float input);

	void drive(float forward, float turn, float strafe);

	float getForwardAverage();
	float getStrafeAverage();
	float getTurnAverage();

private:
	Talon* frontLeftMotor;
	Talon* frontRightMotor; 	//reversed
	Talon* backLeftMotor;
	Talon* backRightMotor;		//reversed

	Encoder* frontLeftEncoder;
	Encoder* frontRightEncoder;
	Encoder* backLeftEncoder;
	Encoder* backRightEncoder;

	float forward;
	float turn;
	float strafe;
};

#endif
