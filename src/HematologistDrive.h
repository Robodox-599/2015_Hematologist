#ifndef HEMATOLOGIST_DRIVE_H
#define HEMATOLOGIST_DRIVE_H

class HematologistDrive
{
public:
	HematologistDrive();
	~HematologistDrive();

	float setForward(float forward);
	float setTurn(float turn);
	float setStrafe(float strafe);

	void drive(float forward, float turn, float strafe);


private:

	Gyro* gyro;

	float forward;
	float turn;
	float strafe;

	float kP;
	float kD;

	HematologistOperatorInterface* oi;

	Talon* frontLeftMotor;
	Talon* backLeftMotor;
	Talon* frontRightMotor;
	Talon* backRightMotor;

}