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
	//instead of jumping to Joystick drive cmd out of deadzone this linearizes input
	float linearizeDrive(float driveInput);

	//gets drive encoder
	//For example: If front and right encoder, call getEncoder(true,true)
	Encoder* getEncoder(bool front, bool right);

	//gets drive Talon
	//For example: If front and right encoder, call getTalon(true,true)
	Talon* getDriveTalon(bool front, bool right);

	void turnOnGyro(bool turnOn);
	void turnOffGyro(bool turnOff);
	bool gyroIsOn();

	void resetEncoders(bool reset);

	Gyro* getGyro();
private:

	Gyro* gyro;

	float forward;
	float turn;
	float strafe;

	float kP;
	
	bool gyroOn;

	HematologistOperatorInterface* oi;

	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

	Encoder* frontLeftEncoder;
	Encoder* backLeftEncoder;
	Encoder* frontRightEncoder;
	Encoder* backRightEncoder;

	double gyro_ref;
};

#endif
