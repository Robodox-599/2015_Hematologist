#include "HematologistManipulator.h"

HematologistManipulator::HematologistManipulator()
{
	forkliftPiston 		= new DoubleSolenoid(FORKLIFT_PISTON_CHANNEL_A, FORKLIFT_PISTON_CHANNEL_B);
	secondTierPiston	= new DoubleSolenoid(SECOND_TIER_PISTON_CHANNEL_A, SECOND_TIER_PISTON_CHANNEL_B);
	binHuggerPiston		= new DoubleSolenoid(BIN_HUGGER_PISTON_CHANNEL_A, BIN_HUGGER_PISTON_CHANNEL_B);
	longArmPiston		= new DoubleSolenoid(LONG_ARM_PISTON_CHANNEL_A, LONG_ARM_PISTON_CHANNEL_B);

	flapOpenRelay		= new Relay(FLAP_OPEN_RELAY_CHANNEL, Relay::kForwardOnly);
	flapCloseRelay		= new Relay(FLAP_CLOSE_RELAY_CHANNEL, Relay::kForwardOnly);
}