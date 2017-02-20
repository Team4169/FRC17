#include "UpRope.h"
#include "../Robot.h"

static std::shared_ptr<RopeClimber> getRopeClimber() {
	return Robot::GetInstance()->getRopeClimber();
}

UpRope::UpRope() : Command("UpRope"){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getRopeClimber().get());
}

// Called just before this Command runs the first time
void UpRope::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void UpRope::Execute() {
	getRopeClimber()->Up();
}

// Make this return true when this Command no longer needs to run execute()
bool UpRope::IsFinished() {
	if(Robot::GetInstance()->getOI()->getController()->GetAButton()){
		return false;
	} else{
		return true;
	}
}

// Called once after isFinished returns true
void UpRope::End() {
	getRopeClimber()->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpRope::Interrupted() {
	End();
}
