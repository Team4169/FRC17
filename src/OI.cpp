#include "OI.h"

OI::OI() : controller(std::make_shared<XboxController>(0)){
	//Define controller to the one in port 0

	//Assign buttons to their correct numbers
	a = std::make_shared<JoystickButton>(controller.get(), A_Button);
	b = std::make_shared<JoystickButton>(controller.get(), B_Button);

	a->WhenPressed(new UpRope());
	b->WhenPressed(new DownRope());

}

std::shared_ptr<XboxController> OI::getController(){
	return controller;
}
