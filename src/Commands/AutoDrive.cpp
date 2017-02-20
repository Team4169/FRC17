#include "AutoDrive.h"
#include "../Robot.h"


static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

AutoDrive::AutoDrive(float speed, float angle) : Command("AutoDrive"), speed(speed), angle(angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain().get());

	current_x = getDriveTrain()->getAHRS()->GetDisplacementX();
	current_y = getDriveTrain()->getAHRS()->GetDisplacementY();

	drive_distance = getDriveTrain()->getAutoDistance() - 2 * getDriveTrain()->getAutoAccelerationDistance();

	goal_x = current_x + drive_distance * cos(angle);
	goal_y = current_y + drive_distance * sin(angle);
}

// Called just before this Command runs the first time
void AutoDrive::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
	getDriveTrain()->DriveInputPolar(speed, angle, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrive::IsFinished() {
	current_x = getDriveTrain()->getAHRS()->GetDisplacementX();
	current_y = getDriveTrain()->getAHRS()->GetDisplacementY();
	if (fabs(goal_x - current_x < 1 && fabs(goal_y - current_y)) < 1){
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void AutoDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {
	End();
}
