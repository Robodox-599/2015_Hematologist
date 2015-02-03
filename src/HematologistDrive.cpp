#include "HematologistDrive.h"

 HematologistDrive::HematologistDrive()
{
     frontLeftMotor = new Talon(FRONT_LEFT_MOTOR_CHANNEL);
	 backLeftMotor = new Talon(BACK_LEFT_MOTOR_CHANNEL);
	 frontRightMotor = new Talon(FRONT_RIGHT_MOTOR_CHANNEL);
	 backRightMotor = new Talon(BACK_RIGHT_MOTOR_CHANNEL);

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

void HematologistDrive::setLinearDrive(float linearValue)
{
	 if(linearValue > DEADZONE || linearValue < -DEADZONE)
	 {
		 forward = -(linearValue);
	 }
	 else
	 {
		 forward = 0;
	 }
}


void HematologistDrive::setTurn(float turnValue)
{
	 if (turnValue > DEADZONE || turnValue < -DEADZONE)
	 {
		 spin = turnValue;
		 gyro_ref = gyro->GetAngle();
	 }
	 else
	 {
		 spin = Kp * (gyro_ref-(gyro->GetAngle()));
	 }
}

void HematologistDrive::setStrafe(float sideValue)
{
	 if (sideValue > DEADZONE || sideValue < -DEADZONE)
	 {
		 side = sideValue;
	 }
	 else
	 {
		 side = 0;
	 }
}

void HematologistDrive::drive(float linearValue, float turnValue, float sideValue)
{
	 setLinearDrive(linearValue);
	 setTurn(turnValue);
	 setStrafe(sideValue);
	 frontLeftMotor->Set(linearizeDrive(forward + side + spin));
	 frontRightMotor->Set(linearizeDrive(-forward + side + spin));
	 backLeftMotor->Set(linearizeDrive(forward - side + spin));
	 backRightMotor->Set(linearizeDrive(-forward - side + spin));
}

float HematologistDrive::linearizeDrive(float driveInput)
{
	return ((driveInput * SLOPE_ADJUSTMENT) - SLOPE_ADJUSTMENT);
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
    }

    else {
    	frontLeftMotor->Set(0);
    	frontRightMotor->Set(0);
    	backLeftMotor->Set(0);
    	backRightMotor->Set(0);
    }
}
