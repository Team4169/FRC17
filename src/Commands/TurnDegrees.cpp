#include "TurnDegrees.h"

static DriveTrain *getDriveTrain() {
	Robot *robot = Robot::GetInstance();
	std::shared_ptr<frc::Subsystem> sub = robot->getDriveTrain();
	return static_cast<DriveTrain *>(sub.get());
}

TurnDegrees::TurnDegrees(double angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	desiredAngle = angle;
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
	if(getDriveTrain()->getCurrentAngle() == desiredAngle){
		return true;
	}
	else return false;
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
