
class Robot: public IterativeRobot
{
private:
	OI* oi;
	HM* hm;
	void RobotInit()
	{
		oi = new OI();
		hm = new HM(oi);		
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
