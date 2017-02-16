#ifndef DriveTrain_H
#define DriveTrain_H

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <CANTalon.h>
#include <XboxController.h>
#include <AHRS.h>
#include <math.h>


class DriveTrain : public Subsystem, PIDOutput{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	double x, y;
	double rotation;
	bool autoAlignEnabled;

	std::shared_ptr<AnalogGyro> gyro;
	AHRS *ahrs;
    PIDController *turnController;      // PID Controller

    double rotateToAngleRate;           // Current rotation rate

	std::shared_ptr<CANTalon> left_front_motor,
		left_back_motor,
		right_front_motor,
		right_back_motor;
	std::shared_ptr<RobotDrive> robotdrive;

    double currentAngle;

    double speedModifier;

    constexpr static double kP = 0.03f,
			kI = 0.00f,
			kD = 0.00f,
			kF = 0.00f,
			kToleranceDegrees = 2.00f;

public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(std::shared_ptr<XboxController> joy);
	void DriveInput(double x, double y, double rotation);
	void Reset();
	void setSpeedModifier(double mod);
	void TurnToDegree(double angle);
	void PIDWrite(double output);
	void motorDrive(int port);
	AHRS* getAHRS();
	double getCurrentAngle();
	bool getAutoAlignMode();
	void setAutoAlignMode(bool on);
};

#endif  // DriveTrain_H
