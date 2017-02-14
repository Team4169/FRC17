#include "RopeClimber.h"
#include "../RobotMap.h"

RopeClimber::RopeClimber() : Subsystem("RopeClimber") {
	motor = std::make_shared<CANTalon>(CLIMBER_MOTOR);
}

void RopeClimber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void RopeClimber::Up(){
	motor->Set(0.5);
}

void RopeClimber::Down(){
	motor->Set(-0.5);

}

void RopeClimber::Stop(){
	motor->Set(0);

}
