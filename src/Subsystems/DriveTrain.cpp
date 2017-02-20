#include "DriveTrain.h"
#include "../Commands/DriveWithController.h"
#include "../RobotMap.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	x = 0;
	y = 0;
	rotation = 0;
	autoAlignEnabled = false;

	left_front_motor = std::make_shared<CANTalon>(LEFT_FRONT_MOTOR);
	left_back_motor = std::make_shared<CANTalon>(LEFT_BACK_MOTOR);
	right_front_motor = std::make_shared<CANTalon>(RIGHT_FRONT_MOTOR);
	right_back_motor = std::make_shared<CANTalon>(RIGHT_BACK_MOTOR);

	robotdrive = std::make_shared<RobotDrive>(left_front_motor, left_back_motor, right_front_motor, right_back_motor);
	robotdrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	robotdrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

	ahrs = new AHRS(SPI::Port::kMXP);
	turnController = new PIDController(kP, kI, kD, kF, ahrs, this);

	rotateToAngleRate = 0;

    turnController->Enable();

    auto_distance = 0;
    auto_accel_distance = 0;
    auto_accel_end_speed = 0;
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

	if(fabs(x) < 0.2){
		x = 0;
	}

	if(fabs(y) < 0.2){
		y = 0;
	}
	SmartDashboard::PutNumber("JoyX", x);
	SmartDashboard::PutNumber("JoyY", y);

	if (joy->GetYButton()){
		x /= 4;
		y /= 4;
	}

	rotation = joy->GetTriggerAxis(GenericHID::kRightHand) - joy->GetTriggerAxis(GenericHID::kLeftHand);

	robotdrive->MecanumDrive_Cartesian(x, y, rotation);
}

void DriveTrain::motorDrive(int port){
	switch(port){
	case 1:
		left_front_motor->Set(0.3);
		break;
	case 2:
		left_back_motor->Set(-0.3);
				break;
	case 3:
		right_front_motor->Set(0.3);
				break;
	case 4:
		right_back_motor->Set(-0.3);
	}
}

void DriveTrain::DriveInputCartesian(double x, double y, double rotation) {
	robotdrive->MecanumDrive_Cartesian(x, y, rotation);
}

void DriveTrain::DriveInputPolar(double speed, double angle, double rotation) {
	robotdrive->MecanumDrive_Polar(speed, angle, rotation);
}

void DriveTrain::Reset(){
	robotdrive->MecanumDrive_Cartesian(0, 0 , 0);
}

void DriveTrain::TurnToDegree(double angle) {
	turnController->SetSetpoint(angle);
	//Turns the robot to the angle given. Angle 0 is the angle during which the robot was initialized in,
	//not the direction the robot is facing
    robotdrive->MecanumDrive_Polar(0, 0, rotateToAngleRate);
}

void DriveTrain::PIDWrite(double output) {
	rotateToAngleRate = output;
}

void DriveTrain::setAutoAccelerationDistance(float dist){
	auto_accel_distance = dist;
}

float DriveTrain::getAutoAccelerationDistance(){
	return auto_accel_distance;
}

void DriveTrain::setAutoDistance(float dist) {
	auto_distance = dist;
}

float DriveTrain::getAutoDistance() {
	return auto_distance;
}

void DriveTrain::setAutoAccelCurrentSpeed(float speed){
	auto_accel_end_speed = speed;
}

float DriveTrain::getAutoAccelCurrentSpeed() {
	return auto_accel_end_speed;
}

double DriveTrain::getCurrentAngle() {
	return ahrs->GetAngle();
}

AHRS* DriveTrain::getAHRS(){
	return ahrs;
}

