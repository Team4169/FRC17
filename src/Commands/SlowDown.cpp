#include "SlowDown.h"

#include "../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

SlowDown::SlowDown(float current_speed, float angle, float acceleration_rate) : Command("SlowDown Regular"), current_speed(current_speed),
		angle(angle), accel_rate(acceleration_rate) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain().get());
}

SlowDown::SlowDown(float angle, float acceleration_rate) : Command("SlowDown Short"),
		current_speed(getDriveTrain()->getAutoAccelCurrentSpeed()), angle(angle), accel_rate(acceleration_rate) {
	Requires(getDriveTrain().get());
}

// Called just before this Command runs the first time
void SlowDown::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SlowDown::Execute() {
	current_speed -= accel_rate;
	getDriveTrain()->DriveInputPolar(current_speed, angle, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool SlowDown::IsFinished() {
	if (getDriveTrain()->getAHRS()->GetRawAccelX() <= 0.1 && getDriveTrain()->getAHRS()->GetRawAccelY() <= 0.1){
		return true;
	} else {
		return false;
	}
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
