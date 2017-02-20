#ifndef AlignRobot_H
#define AlignRobot_H

#include <Commands/Command.h>
#include <NetworkTables/NetworkTable.h>

class AlignRobot : public Command {
public:
	AlignRobot();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	std::shared_ptr<NetworkTable> table;
	std::string direction;
	float x;
};

#endif  // AlignRobot_H
