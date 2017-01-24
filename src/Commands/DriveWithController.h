#ifndef DriveWithController_H
#define DriveWithController_H

#include "../CommandBase.h"
#include "XboxController.h"

class DriveWithController : public CommandBase {
public:
	DriveWithController();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveWithController_H
