#include "AlignRobot.h"
#include "../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

AlignRobot::AlignRobot() : Command("AlignRobot") {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain().get());
	table = NetworkTable::GetTable("Vision_Info");
	direction = table->GetString("DirectionString", "");
	if (direction == "Left"){
		x = -0.2;
	} else if (direction == "Right"){
		x = 0.2;
	} else {
		End();
	}
}

// Called just before this Command runs the first time
void AlignRobot::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AlignRobot::Execute() {
	getDriveTrain()->DriveInputCartesian(x, 0, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool AlignRobot::IsFinished() {
	return direction != table->GetString("DirectionString", "");
}

// Called once after isFinished returns true
void AlignRobot::End() {
	getDriveTrain()->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AlignRobot::Interrupted() {
	End();
}
