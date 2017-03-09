#include "SlowDown.h"

#include "../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

SlowDown::SlowDown(float acceleration_rate) : Command("SlowDown"), acceleration_rate(acceleration_rate) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain().get());
}

// Called just before this Command runs the first time
void SlowDown::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SlowDown::Execute() {
	getDriveTrain()->AutoAccelerate(-acceleration_rate);
}

// Make this return true when this Command no longer needs to run execute()
bool SlowDown::IsFinished() {
	return (getDriveTrain()->getAHRS()->GetWorldLinearAccelX() <= 0.1 && getDriveTrain()->getAHRS()->GetWorldLinearAccelY() <= 0.1);
}

// Called once after isFinished returns true
void SlowDown::End() {
	getDriveTrain()->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SlowDown::Interrupted() {
	End();
}
