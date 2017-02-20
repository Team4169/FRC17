#ifndef DriveForDistance_H
#define DriveForDistance_H

#include <Commands/CommandGroup.h>
#include <Commands/Command.h>

class DriveForDistance : public CommandGroup {
public:
	DriveForDistance(float dist, float angle);
private:
	constexpr static float kSpeed = 0.5,
		kAccelerationRate = 0.01,
		kMinDistance = 5;
};

#endif  // DriveForDistance_H
