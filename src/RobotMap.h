#ifndef ROBOTMAP_H
#define ROBOTMAP_H

constexpr int RIGHT_FRONT_MOTOR = 1; //a (right front motor)
constexpr int LEFT_BACK_MOTOR = 2; //b (correct)
constexpr int RIGHT_BACK_MOTOR = 3; //x (right back motor)
constexpr int LEFT_FRONT_MOTOR = 4; //y (left front motor)

constexpr int CLIMBER_MOTOR = 5;

constexpr int A_Button = 1;
constexpr int B_Button = 2;
constexpr int X_Button = 3;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int LEFTMOTOR = 1;
// constexpr int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;

#endif  // ROBOTMAP_H
