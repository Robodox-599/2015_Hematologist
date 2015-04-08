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

	float linearizeDrive(float driveInput);
	void drive(float forward, float turn, float strafe);

	Talon* getDriveTalon(bool front, bool right);

	Encoder* getEncoder(bool front, bool right);

	void resetEncoders(bool reset);

	void turnOnGyro(bool turnOn);
	void turnOffGyro(bool turnOff);

private:
	float forward;
	float turn;
	float strafe;

	float kP;

	bool gyroOn;
    double gyro_ref;


	HematologistOperatorInterface* oi;

	Gyro* gyro;

	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

	Encoder* frontLeftEncoder;
	Encoder* backLeftEncoder;
	Encoder* frontRightEncoder;
	Encoder* backRightEncoder;
};

#endif
