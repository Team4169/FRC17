#include "TestMotors.h"
#include "Robot.h"

TestMotors::TestMotors(int port): port(port) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::GetInstance()->getDriveTrain().get());
}

// Called just before this Command runs the first time
void TestMotors::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TestMotors::Execute() {
	if(port!=5)
	Robot::GetInstance()->getDriveTrain()->motorDrive(port);
	else if(port==5)
		Robot::GetInstance()->getRopeClimber()->Up();
	else if(port==6)
		Robot::GetInstance()->getRopeClimber()->Down();
}

// Make this return true when this Command no longer needs to run execute()
bool TestMotors::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestMotors::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestMotors::Interrupted() {

}
