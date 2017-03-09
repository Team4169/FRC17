#ifndef Autonomous_H
#define Autonomous_H

#include <Commands/Command.h>
#include <Commands/CommandGroup.h>

class Autonomous : public CommandGroup{
public:
	Autonomous(float drive_distance, float first_turn_angle, float second_turn_angle);
private:
	constexpr static float kPlaceGearDistance = 0.5;
};

#endif  // Autonomous_H
