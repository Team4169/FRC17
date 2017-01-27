#include "DriveTrain.h"
#include "Robot.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain"){
	x = 0;
	y = 0;
	robotdrive = new RobotDrive(left_front_motor, left_back_motor, right_front_motor, right_back_motor);
	rotation = 0;
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithController());
}

void DriveTrain::Drive(XboxController* joy){
	x = joy->GetX(GenericHID::kLeftHand);
	y = joy->GetY(GenericHID::kLeftHand);

	if (x < 0.2){
		x = 0;
	}

	if (y < 0.2){
		y = 0;
	}

	rotation = joy->GetTriggerAxis(GenericHID::kRightHand) - joy->GetTriggerAxis(GenericHID::kLeftHand);

	robotdrive->MecanumDrive_Cartesian(x, y, rotation);

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
