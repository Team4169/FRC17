#ifndef ROBOT_H
#define ROBOT_H

#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <AHRS.h>
#include <NetworkTables/NetworkTable.h>


#include "OI.h"
#include "Subsystems/DriveTrain.h"
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
	std::shared_ptr<DriveTrain> getDriveTrain();
	std::shared_ptr<RopeClimber> getRopeClimber();
	std::shared_ptr<OI> getOI();
	static Robot *GetInstance();

	const static int CAMERA_IMG_WIDTH = 320;
	const static int CAMERA_IMG_HEIGHT = 240;

private:
	std::shared_ptr<DriveTrain> driveTrain;
	std::shared_ptr<RopeClimber> ropeClimber;
	std::shared_ptr<OI> oi;
	frc::SendableChooser<frc::Command*> chooser;
	std::shared_ptr<NetworkTable> table;
	static void VisionThread();
	std::unique_ptr<frc::Command> autonomousCommand;
};


#endif
