#ifndef TestMotors_H
#define TestMotors_H

#include <Commands/Command.h>

class TestMotors : public frc::Command {
private:
	int port;
public:
	TestMotors(int port);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TestMotors_H
