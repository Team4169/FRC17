#ifndef TurnDegrees_H
#define TurnDegrees_H

#include <Commands/Command.h>



class TurnDegrees : public Command {
public:
	TurnDegrees(double angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double desiredAngle;
};

#endif  // TurnDegrees_H
