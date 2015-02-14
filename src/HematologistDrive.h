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

<<<<<<< HEAD
	Encoder* frontLeftEncoder;
	Encoder* backLeftEncoder;
	Encoder* frontRightEncoder;
	Encoder* backRightEncoder;

=======
  Encoder* getEncoder(bool front, bool right);

  Talon* getDriveTalon(bool front, bool right);
>>>>>>> 1f4d656223a8cde35ece4019f3a8ee1e32aebbe8

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

	Encoder* frontLeftEncoder;
	Encoder* backLeftEncoder;
	Encoder* frontRightEncoder;
	Encoder* backRightEncoder;


	double gyro_ref;

};

#endif
