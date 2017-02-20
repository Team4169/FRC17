#ifndef AccelerateToSpeed_H
#define AccelerateToSpeed_H

#include <Commands/Command.h>

class AccelerateToSpeed : public Command {
public:
	AccelerateToSpeed(float speed, float angle, float acceleration_rate);
	AccelerateToSpeed(float angle, float acceleration_rate);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float goal_speed,
		current_speed,
		angle,
		acceleration_rate;

	bool isShort;
};

#endif  // AccelerateToSpeed_H
