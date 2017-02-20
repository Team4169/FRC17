#include "DriveTrain.h"
#include "../Commands/DriveWithController.h"
#include "../RobotMap.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	x = 0;
	y = 0;
	rotation = 0;
	autoAlignEnabled = false;
	speedModifier = 1;

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
	turnController = new PIDController(kP, kI, kD, kF, ahrs, this);

	rotateToAngleRate = 0;
	currentAngle = 0;

    turnController->Enable();
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

	double adjustment = ((y>0)? 0.02 : 0);

	rotation = joy->GetTriggerAxis(GenericHID::kRightHand) - joy->GetTriggerAxis(GenericHID::kLeftHand) - adjustment;

	robotdrive->MecanumDrive_Cartesian(x*speedModifier, y*speedModifier, rotation);
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

void DriveTrain::DriveInput(double x, double y, double rotation) {

	robotdrive->MecanumDrive_Cartesian(x*speedModifier, y*speedModifier, rotation);

}

void DriveTrain::setSpeedModifier(double mod){
	speedModifier = mod;
}

void DriveTrain::Reset(){
	robotdrive->MecanumDrive_Cartesian(0, 0 , 0);
}

void DriveTrain::TurnToDegree(double angle) {
	turnController->SetSetpoint(angle);
	//Turns the robot to the angle given. Angle 0 is the angle during which the robot was initialized in,
	//not the direction the robot is facing
    robotdrive->MecanumDrive_Polar(0, angle, rotateToAngleRate);

    currentAngle = ahrs->GetAngle();
}

void DriveTrain::PIDWrite(double output) {
	rotateToAngleRate = output;
}

double DriveTrain::getCurrentAngle() {
	return currentAngle;
}

AHRS* DriveTrain::getAHRS(){
	return ahrs;
}

bool DriveTrain::getAutoAlignMode(){
	return autoAlignEnabled;
}

void DriveTrain::setAutoAlignMode(bool on){
	autoAlignEnabled = on;
}

