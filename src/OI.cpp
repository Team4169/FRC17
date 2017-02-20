#include "OI.h"
#include "Commands/UpRope.h"
#include "Commands/DownRope.h"
#include "Commands/AlignRobot.h"
#include "RobotMap.h"

OI::OI() : controller(std::make_shared<XboxController>(0)) {
	a = std::make_shared<JoystickButton>(controller.get(), A_Button);
	b = std::make_shared<JoystickButton>(controller.get(), B_Button);
	x = std::make_shared<JoystickButton>(controller.get(), X_Button);

	a->WhenPressed(new UpRope());
	b->WhenPressed(new DownRope());
	x->WhenPressed(new AlignRobot());
}

std::shared_ptr<XboxController> OI::getController(){
	return controller;
}
