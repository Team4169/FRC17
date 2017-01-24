#include "DriveTrain.h"
#include "../RobotMap.h"
#include "Robot.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {

}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithController());
}

void DriveTrain::Drive(XboxController* joy){
	left_motor->Set(-1*joy->GetY(GenericHID::kLeftHand));
	right_motor->Set(-1*joy->GetY(GenericHID::kRightHand));
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
