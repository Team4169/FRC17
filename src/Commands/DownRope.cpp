#include "DownRope.h"
#include "../Robot.h"

static std::shared_ptr<RopeClimber> getRopeClimber() {
	return Robot::GetInstance()->getRopeClimber();
}

DownRope::DownRope() : Command("DownRope"){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getRopeClimber().get());
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
