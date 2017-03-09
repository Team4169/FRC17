#include "AccelerateToSpeed.h"

#include "../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

AccelerateToSpeed::AccelerateToSpeed(float speed, float acceleration_rate) : Command("AccelerateToSpeed"), goal_speed(speed),
		acceleration_rate(acceleration_rate) {
	Requires(getDriveTrain().get());
	end_time = goal_speed/acceleration_rate;
}

// Called just before this Command runs the first time
void AccelerateToSpeed::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AccelerateToSpeed::Execute() {
	getDriveTrain()->AutoAccelerate(acceleration_rate);
}

// Make this return true when this Command no longer needs to run execute()
bool AccelerateToSpeed::IsFinished() {
	return end_time <= getDriveTrain()->getAutoTimer()->GetFPGATimestamp();
}

// Called once after isFinished returns true
void AccelerateToSpeed::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AccelerateToSpeed::Interrupted() {
	End();
}
