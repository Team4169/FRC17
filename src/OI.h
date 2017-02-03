#include <XboxController.h>
#include <Buttons/JoystickButton.h>

#include "Commands/UpRope.h"
#include "Commands/DownRope.h"

#ifndef OI_H
#define OI_H

class OI {
public:
	OI();
	std::shared_ptr<XboxController> getController();
private:
	std::shared_ptr<XboxController> controller;
	std::shared_ptr<JoystickButton> a,
		b;
};

#endif  // OI_H
