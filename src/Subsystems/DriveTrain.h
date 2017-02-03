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

class DriveTrain : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> left_front_motor,
		left_back_motor,
		right_front_motor,
		right_back_motor;
	std::shared_ptr<RobotDrive> robotdrive;

	constexpr static double kP = 0.03f,
			kI = 0.00f,
			kD = 0.00f,
			kF = 0.00f,
			kToleranceDegrees = 2.00f;

	double x, y;
	double rotation;

public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(std::shared_ptr<XboxController> joy);
	void Reset();
};

#endif  // DriveTrain_H
