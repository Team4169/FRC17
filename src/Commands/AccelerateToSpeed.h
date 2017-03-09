#ifndef AccelerateToSpeed_H
#define AccelerateToSpeed_H

#include <Commands/Command.h>

class AccelerateToSpeed : public Command {
public:
	AccelerateToSpeed(float speed, float acceleration_rate);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float goal_speed,
		acceleration_rate,
		end_time;
};

#endif  // AccelerateToSpeed_H
