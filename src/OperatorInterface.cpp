#include "OperatorInterface.h"

OperatorInterface::OperatorInterface()
{
	dashboard->init();
}

virtual OperatorInterface::~OperatorInterface()
{

}

OperatorInterface::printForkliftPower()
{
	dashboard->PutNumber("Forklift Power: ", leftForkliftMotor->Get());
}


