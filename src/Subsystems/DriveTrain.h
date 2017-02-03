#ifndef DriveTrain_H
#define DriveTrain_H

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <CANTalon.h>
#include <XboxController.h>
#include <AHRS.h>
#include <math.h>

#include "../RobotMap.h"
#include "../Commands/DriveWithController.h"

class DriveTrain : public Subsystem, PIDOutput{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	double x, y;
	double rotation;

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

    constexpr static double kP = 0.03f,
			kI = 0.00f,
			kD = 0.00f,
			kF = 0.00f,
			kToleranceDegrees = 2.00f;

public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(std::shared_ptr<XboxController> joy);
	void Reset();
	void TurnToDegree(double angle);
	void PIDWrite(float output);
	double getCurrentAngle();
};

#endif  // DriveTrain_H
