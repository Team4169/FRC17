#include "DriveTrain.h"
#include "../Commands/DriveWithController.h"
#include "../RobotMap.h"
#include "../AHRSAccelerationSource.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	x = 0;
	y = 0;
	rotation = 0;
	currentAngle = 0;

	left_front_motor = std::make_shared<CANTalon>(LEFT_FRONT_MOTOR);
	left_back_motor = std::make_shared<CANTalon>(LEFT_BACK_MOTOR);
	right_front_motor = std::make_shared<CANTalon>(RIGHT_FRONT_MOTOR);
	right_back_motor = std::make_shared<CANTalon>(RIGHT_BACK_MOTOR);

	robotdrive = std::make_shared<RobotDrive>(left_front_motor, left_back_motor, right_front_motor, right_back_motor);
	robotdrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	robotdrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

	try{
	ahrs = new AHRS(SerialPort::Port::kUSB);
	}catch(std::exception e){
		std::string err_string = "Error: ";
		err_string += e.what();
		DriverStation::ReportError(err_string);
	}
	accelController = new PIDController(kPaccel, kIaccel, kDaccel, kFaccel, new AHRSAccelerationSource(ahrs), this);
	turnController = new PIDController(kPturning, kIturning, kDturning, kFturning, ahrs, this);

	rotateToAngleRate = 0;
	auto_rate = 0;
    currentAngle = 0;

    turnController->Disable();

	accelController->Disable();

	auto_accel_time = 0;
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithController());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveTrain::Drive(std::shared_ptr<XboxController> joy){
	x = joy->GetX(GenericHID::kLeftHand);
	y = joy->GetY(GenericHID::kLeftHand);
	double adjustment = 0;
	rotation = joy->GetTriggerAxis(GenericHID::kRightHand) - joy->GetTriggerAxis(GenericHID::kLeftHand) - adjustment;

	if(fabs(x) < 0.2){
		x = 0;
	}

	if(fabs(y) < 0.2){
		y = 0;
	}
	if(fabs(rotation) < 0.1){
		rotation = 0;
	}

	SmartDashboard::PutNumber("JoyX", x);
	SmartDashboard::PutNumber("JoyY", y);

	if (joy->GetYButton()){
		x /= 4;
		y /= 4;
		rotation /= 4;
	}

	robotdrive->MecanumDrive_Cartesian(x, y, rotation);
}

void DriveTrain::DriveInputCartesian(double x, double y, double rotation) {
	robotdrive->MecanumDrive_Cartesian(x, y, rotation);
}

void DriveTrain::DriveInputPolar(double speed, double angle, double rotation) {
	robotdrive->MecanumDrive_Polar(speed, angle, rotation);

}

void DriveTrain::Reset(){
	robotdrive->MecanumDrive_Cartesian(0, 0, 0);
}

void DriveTrain::TurnToDegree(double angle) {
	accelController->Disable();
	turnController->Enable();
	turnController->SetSetpoint(angle);
	//Turns the robot to the angle given. Angle 0 is the angle during which the robot was initialized in,
	//not the direction the robot is facing
    robotdrive->MecanumDrive_Polar(0, 0, rotateToAngleRate);
}

void DriveTrain::AutoAccelerate(double rate) {
	turnController->Disable();
	accelController->Enable();

	accelController->SetSetpoint(rate);

	robotdrive->MecanumDrive_Cartesian(0, auto_rate, 0);
}

void DriveTrain::PIDWrite(double output) {
	if (accelController->IsEnabled()) {
		auto_rate = output;
	} else if (turnController->IsEnabled()){
		rotateToAngleRate = output;
	}
}

double DriveTrain::getCurrentAngle() {
	return ahrs->GetAngle();
}

AHRS* DriveTrain::getAHRS(){
	return ahrs;
}

double DriveTrain::getRotationRate() {
	return rotateToAngleRate;
}

double DriveTrain::getAutoAccelRate() {
	return auto_rate;
}

std::shared_ptr<Timer> DriveTrain::getAutoTimer() {
	return auto_timer;
}
