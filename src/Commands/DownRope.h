#ifndef DownRope_H
#define DownRope_H

#include <Commands/Command.h>
#include "../Robot.h"

class DownRope : public frc::Command {
public:
	DownRope();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DownRope_H
