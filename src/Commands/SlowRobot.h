#ifndef SlowRobot_H
#define SlowRobot_H

#include <Commands/Command.h>

class SlowRobot : public frc::Command {
public:
	SlowRobot();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SlowRobot_H
