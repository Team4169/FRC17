#ifndef DriveTrain_H
#define DriveTrain_H

#include <Commands/Subsystem.h>
#include "CANTalon.h"
#include "RobotMap.h"
#include "XboxController.h"

class DriveTrain : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon* left_motor = new CANTalon(LEFTMOTOR);
	CANTalon* right_motor = new CANTalon(RIGHTMOTOR);
public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(XboxController* joy);
};

#endif  // DriveTrain_H
