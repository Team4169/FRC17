#ifndef TurnDegrees_H
#define TurnDegrees_H

#include <Commands/Command.h>


class TurnDegrees : public frc::Command {
private:
	double desiredAngle;
public:
	TurnDegrees(double angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TurnDegrees_H
