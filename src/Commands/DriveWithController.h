#ifndef DriveWithController_H
#define DriveWithController_H

#include <Commands/Command.h>


class DriveWithController : public frc::Command {
public:
	DriveWithController();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveWithController_H
