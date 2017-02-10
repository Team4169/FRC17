#ifndef DRIVE_FOR_DISTANCE_H
#define DRIVE_FOR_DISTANCE_H

#include <Commands/Command.h>

class DriveForDistance: public frc::Command {
public:
	DriveForDistance(double a, double d);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double angle;
	double distance;
};

#endif  // EXAMPLE_COMMAND_H
