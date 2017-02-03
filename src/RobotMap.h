#ifndef ROBOTMAP_H
#define ROBOTMAP_H

constexpr int LEFT_FRONT_MOTOR = 0;
constexpr int LEFT_BACK_MOTOR = 0;
constexpr int RIGHT_FRONT_MOTOR = 0;
constexpr int RIGHT_BACK_MOTOR = 0;

constexpr int LEFT_CLIMBER_MOTOR = 0;
constexpr int RIGHT_CLIMBER_MOTOR = 0;

constexpr int ANALOG_GYRO = 0;
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
