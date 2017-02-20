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

    constexpr static double kP = 0.03f,
			kI = 0.00f,
			kD = 0.00f,
			kF = 0.00f,
    float auto_accel_distance,
		auto_distance,
		auto_accel_end_speed;

public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(std::shared_ptr<XboxController> joy);
	void DriveInputCartesian(double x, double y, double rotation);
	void DriveInputPolar(double speed, double angle, double rotation);
	void Reset();
	void TurnToDegree(double angle);
	void PIDWrite(double output);
	void motorDrive(int port);
	AHRS* getAHRS();
	double getCurrentAngle();
	void setAutoAccelerationDistance(float dist);
	float getAutoAccelerationDistance();
	void setAutoDistance(float dist);
	float getAutoDistance();
	void setAutoAccelCurrentSpeed(float speed);
	float getAutoAccelCurrentSpeed();

	constexpr static double kToleranceDegrees = 5.00f;
};

#endif  // DriveTrain_H
