#ifndef Autonomous_H
#define Autonomous_H

#include <Commands/Command.h>
#include <Commands/CommandGroup.h>

class Autonomous : public CommandGroup{
public:
	Autonomous(float drive_distance, float drive_angle, float turn_angle);
private:
	constexpr static float kPlaceGearDistance = 0.5;
};

#endif  // Autonomous_H
