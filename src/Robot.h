#ifndef ROBOT_H
#define ROBOT_H

#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/RopeClimber.h"

class Robot: public frc::IterativeRobot {
public:
	Robot();
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	std::unique_ptr<frc::Command> autonomousCommand;
	std::shared_ptr<frc::Subsystem> getExampleSubsystem();
	std::shared_ptr<frc::Subsystem> getDriveTrain();
	std::shared_ptr<frc::Subsystem> getRopeClimber();
	std::shared_ptr<OI> getOI();
	static Robot *GetInstance();

private:
	std::shared_ptr <frc::Subsystem> exampleSubsystem;
	std::shared_ptr <frc::Subsystem> driveTrain;
	std::shared_ptr <frc::Subsystem> ropeClimber;
	std::shared_ptr<OI> oi;
	frc::SendableChooser<frc::Command*> chooser;
};


#endif
