#ifndef DriveWithController_H
#define DriveWithController_H

#include "Subsystems/DriveTrain.h"
#include "../CommandBase.h"

class DriveWithController : public CommandBase {
public:
	DriveWithController();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	Joystick* stick;
};

#endif  // DriveWithController_H
