#ifndef Drive_H
#define Drive_H

#include <Commands/Command.h>

class AutoDrive : public Command {
public:
	AutoDrive(float total_distance, float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float distance,
		speed,
		end_time;
};

#endif  // Drive_H
