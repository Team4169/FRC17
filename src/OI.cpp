#include "OI.h"
#include "Commands/UpRope.h"
#include "Commands/DownRope.h"
#include "Commands/TestMotors.h"
#include "RobotMap.h"

OI::OI() : controller(std::make_shared<XboxController>(0)){
	//Define controller to the one in port 0

	//Assign buttons to their correct numbers
	a = std::make_shared<JoystickButton>(controller.get(), A_Button);
	b = std::make_shared<JoystickButton>(controller.get(), B_Button);
	x = std::make_shared<JoystickButton>(controller.get(), X_Button);
	y = std::make_shared<JoystickButton>(controller.get(), Y_Button);

	a->WhenPressed(new UpRope());
	b->WhenPressed(new DownRope());
	y->WhenPressed(new SlowRobot());

}

std::shared_ptr<XboxController> OI::getController(){
	return controller;
}
