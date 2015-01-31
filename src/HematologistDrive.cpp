#include "HematologistDrive.h"

 HematologistDrive::HematologistDrive()
{

     frontLeftMotor = new Talon(2);
	 backLeftMotor = new Talon(3);
	 frontRightMotor = new Talon(0);
	 backRightMotor = new Talon(1);

	 gyro = new Gyro(1);
     gyro_ref = 0;

     forward = 0;
     spin = 0;
     side = 0;

	 oi = new HematologistOperatorInterface;

	 timer = new Timer();
	 timer->Start();
	 initTime = 0;
}

 HematologistDrive::~HematologistDrive()
{
	 delete frontLeftMotor;
	 delete backLeftMotor;
	 delete frontRightMotor;
	 delete backRightMotor;
     delete timer;
	 delete gyro;

	 frontLeftMotor = NULL;
	 backLeftMotor = NULL;
	 frontRightMotor = NULL;
	 backRightMotor = NULL;
     timer = NULL;
	 gyro = NULL;
}

void HematologistDrive::setLinearDrive()
{
	 if(oi->rightJoystick->GetY() > DEADZONE || oi->rightJoystick->GetY() < -DEADZONE)
	 {
		 forward = -(oi->rightJoystick->GetY());
	 }
	 else
	 {
		 forward = 0;
	 }
}


void HematologistDrive::setTurn()
{
	 if (oi->rightJoystick->GetX() > DEADZONE || oi->rightJoystick->GetX() < -DEADZONE)
	 {
		 spin = oi->rightJoystick->GetX();
		 gyro_ref = gyro->GetAngle();
	 }
	 else
	 {
		 spin = Kp * (gyro_ref-(gyro->GetAngle()));
	 }
}

void HematologistDrive::setStrafe()
{
	 if (oi->leftJoystick->GetX() > DEADZONE || oi->leftJoystick->GetX() < -DEADZONE)
	 {
		 side = oi->leftJoystick->GetX();
	 }
	 else
	 {
		 side = 0;
	 }
}

void HematologistDrive::setStrafe(float speed)
{
	side = speed;
}


void HematologistDrive::drive()
{
	 setLinearDrive();
	 setTurn();
	 setStrafe();
	 frontLeftMotor->Set(forward - side + spin);
	 frontRightMotor->Set(-forward - side + spin);
	 backLeftMotor->Set(forward + side + spin);
	 backRightMotor->Set(-forward + side + spin);
}




//for performing gyro testing, will be removed when test is successful
void HematologistDrive::testDrive()
{   //speed: .24
    if(oi->rightJoystick->GetRawButton(3)){
    	gyro_ref = gyro->GetAngle();
    	initTime = timer->Get();
    }

    if(timer->Get() > 0 + initTime && timer->Get() < 3 + initTime){
    	spin = Kp * (gyro_ref - (gyro->GetAngle()));
    	frontLeftMotor->Set(.24 + spin);
    	frontRightMotor->Set(-.24 + spin);
    	backLeftMotor->Set(.24 + spin);
    	backRightMotor->Set(-.24 + spin);
    } else {
    	frontLeftMotor->Set(0);
    	frontRightMotor->Set(0);
    	backLeftMotor->Set(0);
    	backRightMotor->Set(0);
    }
}
