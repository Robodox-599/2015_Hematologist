
class Robot: public IterativeRobot
{
private:
	

	void RobotInit()
	{
		
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		solenoid->Set(DoubleSolenoid::kReverse);
		solenoid->Set(DoubleSolenoid::kForward);
		solenoid->Set(DoubleSolenoid::kOff);
	}

	void TestPeriodic()
	{
		

	}
};

START_ROBOT_CLASS(Robot);
