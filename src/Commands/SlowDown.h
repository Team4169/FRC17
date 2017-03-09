#ifndef SlowDown_H
#define SlowDown_H

#include <Commands/Command.h>

class SlowDown : public Command {
public:
	SlowDown(float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float acceleration_rate;
};

#endif  // SlowDown_H
