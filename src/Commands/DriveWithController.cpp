#include "DriveWithController.h"

DriveWithController::DriveWithController() : CommandBase::CommandBase("DriveWithController") {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(CommandBase::drive_train.get());
}

// Called just before this Command runs the first time
void DriveWithController::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void DriveWithController::Execute() {
	CommandBase::drive_train.get()->Drive(oi->controller);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithController::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithController::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithController::Interrupted() {

}
