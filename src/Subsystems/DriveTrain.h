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

	std::shared_ptr<AnalogGyro> gyro;
	AHRS *ahrs;
    PIDController
			*turnController,
			*accelController;      // PID Controller

    double rotateToAngleRate; // Current rotation rate
    double auto_rate;

	std::shared_ptr<CANTalon> left_front_motor,
		left_back_motor,
		right_front_motor,
		right_back_motor;
	std::shared_ptr<RobotDrive> robotdrive;


    double currentAngle;

    constexpr static double
			kPturning = 0.2f,
			kIturning = 0.00f,
			kDturning = 0.00f,
			kFturning = 0.00f;
    constexpr static double
			kPaccel = 0.2f,
    		kIaccel = 0.00f,
			kDaccel = 0.00f,
			kFaccel = 0.00f;


	std::shared_ptr<Timer> auto_timer;

	double auto_accel_time;

public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(std::shared_ptr<XboxController> joy);
	void DriveInputCartesian(double x, double y, double rotation);
	void DriveInputPolar(double speed, double angle, double rotation);
	void Reset();
	void TurnToDegree(double angle);
	void AutoAccelerate(double rate);
	void PIDWrite(double output);
	AHRS* getAHRS();
	double getCurrentAngle();
	double getRotationRate();
	double getAutoAccelRate();
	std::shared_ptr<Timer> getAutoTimer();


	constexpr static double kToleranceDegrees = 5.00f;
};

#endif  // DriveTrain_H
