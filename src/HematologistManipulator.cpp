#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
{
	forkliftPiston 		= new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A, FORKLIFT_PISTON_CHANNEL_B);
	secondTierPiston	= new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A, SECOND_TIER_PISTON_CHANNEL_B);
	binHuggerPiston		= new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A, BIN_HUGGER_PISTON_CHANNEL_B);
	longArmPiston		= new DoubleSolenoid(LONG_ARM_PISTON_CHANNEL_A, LONG_ARM_PISTON_CHANNEL_B);

	flapOpenRelay		= new Relay(FLAP_OPEN_RELAY_CHANNEL, Relay::kForwardOnly);
	flapCloseRelay		= new Relay(FLAP_CLOSE_RELAY_CHANNEL, Relay::kForwardOnly);

	liftEncoder 		= new Encoder(LIFT_ENCODER_CHANNEL_A, LIFT_ENCODER_CHANNEL_B);

	leftLiftMotor		= new Talon(LEFT_LIFT_MOTOR_CHANNEL);
	rightLiftMotor		= new Talon(RIGHT_LIFT_MOTOR_CHANNEL);

	leftRollerMotor		= new Talon(LEFT_ROLLER_MOTOR_CHANNEL);
	rightRollerMotor	= new Talon(RIGHT_ROLLER_MOTOR_CHANNEL);

	compressor 			= new Compressor(COMPRESSOR_CHANNEL);
	compressor->SetClosedLoopControl(true);

	topLimitSwitch 		= new HematologistLimitSwitch(TOP_LIMIT_SWITCH_CHANNEL);
	bottomLimitSwitch 	= new HematologistLimitSwitch(BOTTOM_LIMIT_SWITCH_CHANNEL);
}

HematologistManipulator::~HematologistManipulator()
{
	delete forkliftPiston;
	delete secondTierPiston;
	delete binHuggerPiston;
	delete longArmPiston;
	delete flapOpenRelay;
	delete flapCloseRelay;
	delete liftEncoder;
	delete leftLiftMotor;
	delete rightLiftMotor;
	delete leftRollerMotor;
	delete rightRollerMotor;
	delete compressor;
	delete topLimitSwitch;
	delete bottomLimitSwitch;

	forkliftPiston= NULL;
	secondTierPiston= NULL;
	binHuggerPiston= NULL;
	longArmPiston= NULL;
	flapOpenRelay= NULL;
	flapCloseRelay= NULL;
	liftEncoder= NULL;
	leftLiftMotor= NULL;
	rightLiftMotor= NULL;
	leftRollerMotor= NULL;
	rightRollerMotor= NULL;
	compressor= NULL;
	topLimitSwitch= NULL;
	bottomLimitSwitch= NULL;
}