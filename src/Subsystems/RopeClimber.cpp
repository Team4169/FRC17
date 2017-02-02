#include "RopeClimber.h"


RopeClimber::RopeClimber() : Subsystem("RopeClimber") {
	left_motor = new CANTalon(LEFT_CLIMBER_MOTOR);
	right_motor = new CANTalon(RIGHT_CLIMBER_MOTOR);
}

void RopeClimber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void RopeClimber::Up(){
	left_motor->Set(1);
	right_motor->Set(-1);
}

void RopeClimber::Down(){
	left_motor->Set(-1);
	right_motor->Set(1);
}

void RopeClimber::Stop(){
	left_motor->Set(0);
	right_motor->Set(0);
}
