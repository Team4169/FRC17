#include "DriveWithController.h"
#include "../Robot.h"

static DriveTrain* getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain().get();
}

DriveWithController::DriveWithController() : Command("DriveWithController") {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain());
}

// Called just before this Command runs the first time
void DriveWithController::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void DriveWithController::Execute() {
	getDriveTrain()->Drive(Robot::GetInstance()->getOI().get()->getController());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithController::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithController::End() {
	getDriveTrain()->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithController::Interrupted() {
	End();
}
