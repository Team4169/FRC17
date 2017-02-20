#ifndef Drive_H
#define Drive_H

#include <Commands/Command.h>

class AutoDrive : public Command {
public:
	AutoDrive(float speed, float angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float speed,
		angle,
		drive_distance;

	float current_x,
		current_y,
		goal_x,
		goal_y;

};

#endif  // Drive_H
