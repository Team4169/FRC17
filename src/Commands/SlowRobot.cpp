#include "SlowRobot.h"
#include "Robot.h"
#include "../Subsystems/DriveTrain.h"

SlowRobot::SlowRobot() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	//Requires(Robot::GetInstance()->getDriveTrain().get());
}

// Called just before this Command runs the first time
void SlowRobot::Initialize() {
	Robot::GetInstance()->getDriveTrain()->setSpeedModifier(0.25);
}

// Called repeatedly when this Command is scheduled to run
void SlowRobot::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SlowRobot::IsFinished() {
	if(Robot::GetInstance()->getOI()->getController()->GetYButton()){
			return false;
		} else{
			return true;
		}
}

// Called once after isFinished returns true
void SlowRobot::End() {
	Robot::GetInstance()->getDriveTrain()->setSpeedModifier(1.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SlowRobot::Interrupted() {

}
