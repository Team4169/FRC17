#include "AutoDrive.h"
#include "../Robot.h"


static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

AutoDrive::AutoDrive(float distance, float speed) : Command("AutoDrive"), distance(distance), speed(speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain().get());
	end_time = distance/speed;
}

// Called just before this Command runs the first time
void AutoDrive::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
	getDriveTrain()->AutoAccelerate(0);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrive::IsFinished() {
	return end_time <= getDriveTrain()->getAutoTimer()->GetFPGATimestamp();
}

// Called once after isFinished returns true
void AutoDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {
	End();
}
