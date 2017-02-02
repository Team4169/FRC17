#include "DriveTrain.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain"){
	x = 0;
	y = 0;
	rotation = 0;

	left_front_motor = new CANTalon(LEFT_FRONT_MOTOR);
	left_back_motor = new CANTalon(LEFT_BACK_MOTOR);
	right_front_motor = new CANTalon(RIGHT_FRONT_MOTOR);
	right_back_motor = new CANTalon(LEFT_BACK_MOTOR);

	robotdrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	robotdrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	robotdrive = new RobotDrive(left_front_motor, left_back_motor, right_front_motor, right_back_motor);

	gyro = new AnalogGyro(ANALOG_GYRO);
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithController);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveTrain::Drive(std::shared_ptr<XboxController> joy){
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

void DriveTrain::Reset(){
	robotdrive->MecanumDrive_Cartesian(0,0,0);
}


