#ifndef DriveForDistance_H
#define DriveForDistance_H

#include <Commands/CommandGroup.h>
#include <Commands/Command.h>
#include <Timer.h>

class DriveForDistance : public CommandGroup {
public:
	DriveForDistance(float dist);
private:
	constexpr static float kSpeed = 3,
		kAccelerationRate = 1;
};

#endif  // DriveForDistance_H
