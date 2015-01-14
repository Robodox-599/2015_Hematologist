#include "HematologistDrive.h"

 HematologistDrive::HematologistDrive(HematologistOperatorInterface *opInt)
 {
     if(opInt) oi = opInt;
     Kp = .03;

     frontLeftMotor = new Talon(0);
	 backLeftMotor = new Talon(1);
	 frontRightMotor = new Talon(2);
	 backRightMotor = new Talon(3);

	 gyro = new Gyro(1);

 }

 HematologistDrive::~HematologistDrive()
 {
	 delete frontLeftMotor;
	 delete backLeftMotor;
	 delete frontRightMotor;
	 delete backRightMotor;
	 delete gyro;

	 frontLeftMotor = NULL;
	 backLeftMotor = NULL;
	 frontRightMotor = NULL;
	 backRightMotor = NULL;
	 gyro = NULL;
 }

void HematologistDrive::setLinearDrive(float forward)
{
	 if(oi->leftJoystick->GetY() > DEADZONE || oi->leftJoystick->GetY() < -DEADZONE)
	 {
		 forward = oi->leftJoystick->GetY();
	 }
	 else
	 {
		 forward = 0;
	 }
}

void HematologistDrive::setTurn(float spin)
{
	 if (oi->leftJoystick->GetX() > DEADZONE || oi->leftJoystick->GetX() < -DEADZONE)
	 {
		 spin = oi->leftJoystick->GetX();
	 }
	 else
	 {
		 spin = 0;
	 }
}

void HematologistDrive::setStrafe(float side)
{
	 if (oi->rightJoystick->GetX() > DEADZONE || oi->rightJoystick->GetX() < -DEADZONE)
	 {
		 side = oi->rightJoystick->GetX();
	 }
	 else
	 {
		 side = 0;
	 }
}

 void HematologistDrive::drive(float spin, float side, float forward)
 {
	 backRightMotor->Set(forward - side + spin);
	 backLeftMotor->Set(-(forward + side - spin));
	 frontLeftMotor->Set(-(forward - side - spin));
	 frontRightMotor->Set(forward + side + spin);
 }
