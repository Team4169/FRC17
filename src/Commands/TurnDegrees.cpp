#include "TurnDegrees.h"

#include "../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}

TurnDegrees::TurnDegrees(double angle): Command("TurnDegrees"), desiredAngle(getDriveTrain()->getCurrentAngle() + angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(getDriveTrain().get());
}

// Called just before this Command runs the first time
void TurnDegrees::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TurnDegrees::Execute() {
	getDriveTrain()->TurnToDegree(desiredAngle);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnDegrees::IsFinished() {
	if (fabs(getDriveTrain()->getCurrentAngle() - desiredAngle) < getDriveTrain()->kToleranceDegrees){
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void TurnDegrees::End() {
	getDriveTrain()->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnDegrees::Interrupted() {
	End();
}
