#ifndef UpRope_H
#define UpRope_H

#include <Commands/Command.h>


class UpRope : public frc::Command {
public:
	UpRope();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // UpRope_H
