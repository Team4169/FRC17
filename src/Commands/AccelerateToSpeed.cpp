#include "AccelerateToSpeed.h"

#include "../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

AccelerateToSpeed::AccelerateToSpeed(float speed, float angle, float acceleration_rate) : Command("AccelerateToSpeed Regualar"),
		goal_speed(speed),  current_speed(0), angle(angle), acceleration_rate(acceleration_rate), isShort(false) {
	Requires(getDriveTrain().get());
}

AccelerateToSpeed::AccelerateToSpeed(float angle, float acceleration_rate) : Command("AccelerateToSpeed Short"), goal_speed(0),
		current_speed(0), angle(angle), acceleration_rate(acceleration_rate), isShort(true) {
	Requires(getDriveTrain().get());
}

// Called just before this Command runs the first time
void AccelerateToSpeed::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void AccelerateToSpeed::Execute() {
	current_speed += acceleration_rate;
	getDriveTrain()->DriveInputPolar(current_speed, angle, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool AccelerateToSpeed::IsFinished() {
	if (isShort) {
		return hypot(getDriveTrain()->getAHRS()->GetDisplacementX(), getDriveTrain()->getAHRS()->GetDisplacementY()) >= getDriveTrain()->getAutoDistance();
	} else {
		return goal_speed <= current_speed;
	}
}

// Called once after isFinished returns true
void AccelerateToSpeed::End() {
	getDriveTrain()->setAutoAccelerationDistance(hypot(getDriveTrain()->getAHRS()->GetDisplacementX(),
			getDriveTrain()->getAHRS()->GetDisplacementY()));
	if (isShort) {
		getDriveTrain()->setAutoAccelCurrentSpeed(current_speed);
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AccelerateToSpeed::Interrupted() {
	End();
}
