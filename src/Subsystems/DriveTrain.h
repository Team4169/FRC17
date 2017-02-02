#ifndef DriveTrain_H
#define DriveTrain_H

#include <Commands/Subsystem.h>
#include "CANTalon.h"
#include "RobotMap.h"
#include "XboxController.h"
#include "WPILib.h"

class DriveTrain : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon* left_front_motor; // = new CANTalon(LEFT_FRONT_MOTOR);
	CANTalon* left_back_motor; // = new CANTalon(LEFT_BACK_MOTOR);
	CANTalon* right_front_motor; // = new CANTalon(RIGHT_FRONT_MOTOR);
	CANTalon* right_back_motor; // = new CANTalon(RIGHT_BACK_MOTOR);

	double x, y;
	double rotation;

	RobotDrive* robotdrive;
public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(XboxController* joy);
};

#endif  // DriveTrain_H
