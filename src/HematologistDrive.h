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

private:
	Talon* frontLeftMotor;
	Talon* frontRightMotor;
	Talon* backLeftMotor;
	Talon* backRightMotor;

	Encoder* frontLeftEncoder;
	Encoder* frontRightEncoder;
	Encoder* backLeftEncoder;
	Encoder* backRightEncoder;

	float forward;
	float turn;
	float strafe;
};

#endif
