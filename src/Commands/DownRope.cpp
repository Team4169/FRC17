#include "DownRope.h"

static RopeClimber *getRopeClimber() {
	Robot *robot = Robot::GetInstance();
	std::shared_ptr<frc::Subsystem> sub = robot->getRopeClimber();
	return static_cast<RopeClimber *>(sub.get());
}

DownRope::DownRope() : Command("DownRope"){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getRopeClimber());
}

// Called just before this Command runs the first time
void DownRope::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DownRope::Execute() {
	getRopeClimber()->Down();
}

// Make this return true when this Command no longer needs to run execute()
bool DownRope::IsFinished() {
	if(Robot::GetInstance()->getOI()->getController()->GetBButton()){
		return false;
	} else{
		return true;
	}
}

// Called once after isFinished returns true
void DownRope::End() {
	getRopeClimber()->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DownRope::Interrupted() {
	End();
}
