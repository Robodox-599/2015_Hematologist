#ifndef DRIVE_H
#define DRIVE_H

#include "../HematologistMacros.h"

class Drive
{
public:
	Drive();
	~Drive();

	void setForward(float forward);    //sets class varaibles of forward
	void setTurn(float turn);          //sets class varaibles of turn 
	void setStrafe(float strafe);      //sets class varaibles of strafe

	float getForward();                //returns the values of forward        
	float getTurn();                   //returns the values of turn
	float getStrafe();                 //returns the values of strafe

	float linearizeDrive(float input); //returns a shifted value of the input to take into account the deadzone

  //input in joystick values of X, Y, and then another joystick's X or Y
  //merely moves the motors appropriately by taking the joysticks and deadzone into account
	void drive(float forward, float turn, float strafe); 

  //these averages are used when finding how far the robot has moved forward/back, strafed right/left, turned how much
  //because of how the encoders are, if we simply added up the encoder values and taken the average, we would have a big problem
  //for example, for the turnAverage, if I added all the values, I would get a sum of zero 
  //(because one side is negative and the other positive) and so my average would be zero...
  //instead, I make one side negative of itself (so that both sides are postiive) and now when I add, I either get a 
  //positive number (indicating I've turned right) or a negative numbe (indicating I turned left)
	float getForwardAverage();         //returns the average value of the encoder when having moved forward/back
	float getStrafeAverage();          //returns the average value of the encoder when having strafed
	float getTurnAverage();            //returns the average value of the encoder when having turned

	void resetEncoders();              //reset encoder values. It is recommended that this is done after each use of the avareage
	//input a GetRawButton(buttonNum) to manually reset the encoders (for testing purposes)
  void resetEncoders(bool reset);    

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
