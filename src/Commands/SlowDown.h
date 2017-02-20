#ifndef SlowDown_H
#define SlowDown_H

#include <Commands/Command.h>

class SlowDown : public Command {
public:
	SlowDown(float current_speed, float angle, float acceleration_rate);
	SlowDown(float angle, float acceleration_rate);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float current_speed,
		angle,
		accel_rate;
};

#endif  // SlowDown_H
