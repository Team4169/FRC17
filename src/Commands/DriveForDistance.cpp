#include "DriveForDistance.h"
#include "../Robot.h"
#include <math.h>

static DriveTrain* getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain().get();
}

DriveForDistance::DriveForDistance(double a, double d) : angle(a), distance(d) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain());
}

// Called just before this Command runs the first time
void DriveForDistance::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveForDistance::Execute() {
	getDriveTrain()->DriveInput(sin(angle)*distance, cos(angle)*distance, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForDistance::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveForDistance::End() {
	getDriveTrain()->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForDistance::Interrupted() {
	End();
}
